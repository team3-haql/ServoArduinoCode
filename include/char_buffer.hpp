#pragma once

#include <time.h>

#include "util.hpp"
#include "constants.hpp"

namespace boden {

typedef signed char BufferSize;
// Makes sure Buffer Iterator is large enough to not overflow
static_assert(MAX_TYPE_SIZE(BufferSize) >= BUFFER_SIZE-1, "BufferIterator is too small!");

/**
 * @brief Whether or not serial is empty
 * 
 * @return true 
 * @return false 
 */
bool serialEmpty() {
    return Serial.available() == 0;
}

// Allows input to be + or -
#define FIRST_LETTER  '\1'
// Allows input to be e or E
#define COUNTAINS_E   '\2'
// Allows for .
#define COUNTAINS_DOT '\4'

/**
 * @brief Reads from Serial port 
 * 
 * @param buffer char*
 * 
 * @param BufferSize
 */
BufferSize read(char* buffer) {
    BufferSize i = 0;
    char bufferState = FIRST_LETTER;
    for (; i < BUFFER_SIZE-1; i++) {
        while(serialEmpty()) { // Wait until more data is available
            delay(1);
        }
        char character = Serial.read();
        if (character == '\n') { // Exit
            break;
        }
        // Makes sure input matches float format. Example:
        // 1e-6
        // +0.25
        // -5E6
        if (!isdigit(character)) {
            if (bufferState & FIRST_LETTER && (character == '-' || character == '+')) {
                bufferState &= ~FIRST_LETTER; // Unset first letter
            }
            else if (!(bufferState & COUNTAINS_E) && (character == 'e' || character == 'E')) {
                bufferState |= COUNTAINS_E; // Set countains e
                bufferState |= FIRST_LETTER; // Set first letter
            }
            else if (!(bufferState & COUNTAINS_DOT) && (character == '.')) {
                bufferState |= COUNTAINS_DOT;
            }
            else {
                // Error
                LOGLN("\n\'%c\' is an invalid character!" COMMA character);
                return -1;
            }
        }
        else {
            bufferState &= ~FIRST_LETTER; // Unset first letter
        }
        LOG(character);
        buffer[i] = character;
    } 
    buffer[i] = '\0';
    LOGLN();
    return i; // Return size
}

#undef FIRST_LETTER
#undef COUNTAINS_E

} // namespace boden end
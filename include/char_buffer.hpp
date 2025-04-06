#pragma once

#include <time.h>

#include "util.hpp"
#include "constants.hpp"

namespace ralphee {

typedef int8_t BufferSize;
// Makes sure Buffer Iterator is large enough to not overflow
static_assert(MAX_TYPE_SIZE(BufferSize) >= BUFFER_SIZE-1, "BufferIterator is too small!");
static_assert(static_cast<BufferSize>(-1) < 0);

// Allows input to be + or -
#define FIRST_LETTER '\1'
// Allows input to be e or E
#define CONTAINS_E   '\2'
// Allows for .
#define CONTAINS_DOT '\4'

/**
 * @brief Reads from Serial port 
 * 
 * @param buffer char*
 * 
 * @param BufferSize
 */
BufferSize read(char* buffer) {
    BufferSize i = 0;
    uint8_t bufferState = FIRST_LETTER;
    for (; i < BUFFER_SIZE-1; i++) {
        while(Serial.available() == 0) { // Wait until more data is available
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
            else if (!(bufferState & CONTAINS_E) && (character == 'e' || character == 'E')) {
                bufferState |= CONTAINS_E; // Set countains e
                bufferState |= FIRST_LETTER; // Set first letter
            }
            else if (!(bufferState & CONTAINS_DOT) && (character == '.')) {
                bufferState |= CONTAINS_DOT;
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
#undef CONTAINS_E
#undef CONTAINS_DOT

} // namespace boden end
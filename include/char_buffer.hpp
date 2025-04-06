#pragma once

#include <time.h>

#include "util.hpp"
#include "constants.hpp"

namespace ralphee {

typedef int8_t BufferSize;
// Makes sure Buffer Iterator is large enough to not overflow
static_assert(MAX_TYPE_SIZE(BufferSize) >= BUFFER_SIZE-1, "BufferIterator is too small!");
// Makes sure BufferSize can return negative values
static_assert(static_cast<BufferSize>(-1) < 0, "BufferSize returns -1 in read for errors!");

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
        // Makes sure input matches double format. Example:
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
                LOG("\n\'%c\' is an invalid character!\n" COMMA character);
                return -1;
            }
        }
        else { // is digit
            bufferState &= ~FIRST_LETTER; // Unset first letter
        }
        LOG("%c" COMMA character);
        buffer[i] = character;
    } 
    buffer[i] = '\0'; // Terminates strings
    LOG("\n");
    return i; // Return size
}

// Undefines constants that wont be used later.
#undef FIRST_LETTER
#undef CONTAINS_E
#undef CONTAINS_DOT

} // namespace boden end
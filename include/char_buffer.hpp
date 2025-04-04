#pragma once

#include "util.hpp"
#include "constants.hpp"

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

/**
 * @brief Reads from Serial port 
 * 
 * @param buffer 
 * 
 * @param BufferSize
 */
BufferSize read(char* buffer) {
    bool done = false;
    BufferSize i = 0;
    for (; i < BUFFER_SIZE-1; i++) {
        while(serialEmpty()) { // Wait until more data is available
            delay(1);
        }
        char character = Serial.read();
        if (character == '\n') { // Exit
            done = true;
            break;
        }
        buffer[i] = character;
    } 
    buffer[i] = '\0';
    return i;
}
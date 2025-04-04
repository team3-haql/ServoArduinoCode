#pragma once

#include "util.hpp"
#include "constants.hpp"

typedef unsigned char BufferSize;
// Makes sure Buffer Iterator is large enough to not overflow
static_assert(MAX_TYPE_SIZE(BufferSize) >= BUFFER_SIZE-1, "BufferIterator is too small!");

/**
 * @brief Reads from Serial port 
 * 
 * @param buffer 
 */
void read(char* buffer) {
    // Precompute size of for loop for better performance
    // Assumes Serial.available() does not change while for loop is running.
    const BufferSize size = MIN(BUFFER_SIZE-1, Serial.available());
    BufferSize i = 0;
    for (; i < size; i++) {
        char character = Serial.read();
        if (!isdigit(character)) {
            continue;
        }
        buffer[i] = character;
    } 
    buffer[i] = '\0';
}
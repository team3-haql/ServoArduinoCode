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
    BufferSize i = 0;
    for (; i < BUFFER_SIZE-1 && Serial.available() > 0; i++) {
        char character = Serial.read();
        if (character == '\n') {
            break;
        }
        buffer[i] = character;
    } 
    buffer[i] = '\0';
}
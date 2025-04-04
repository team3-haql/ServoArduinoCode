#pragma once

#include "util.hpp"

#define BUFFER_SIZE 32
typedef unsigned char BufferIterator;
// Makes sure Buffer Iterator is large enough to not overflow
static_assert(MAX_TYPE_SIZE(BufferIterator) >= BUFFER_SIZE-1, "BufferIterator is too small!");

/**
 * @brief Reads from Serial port 
 * 
 * @param buffer 
 */
void read(char* buffer) {
    // Prevents atof from potentially failing
    buffer[BUFFER_SIZE-1] = '\0';
    // Precompute size of for loop for better performance
    // Assumes Serial.available() does not change while for loop is running.
    const BufferIterator size = MIN(BUFFER_SIZE-1, Serial.available());
    for (BufferIterator i = 0; i < size; i++) {
        buffer[i] = Serial.read();
        if (buffer[i] == '\n') { // '\n' indicates end of transmission.
            buffer[i] = '\0'; // Set 'i' to be end of string
            break;
        }
    } 
}
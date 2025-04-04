#include <time.h>

#include "util.hpp"
#include "ackerman.hpp"
#include "char_buffer.hpp"
#include "servo.hpp"
#include "constants.hpp"

// Enables logging
#define LOGGING

void setup() {
	Serial.begin(9600);  // Start serial communication
	initServos();        // Initializes servos
	LOGLN("Enter an angle [-1,1]:");
}

void loop() {
    if (Serial.available() >= MIN_CHARS_IN_MESSAGE) {
		static char buffer[BUFFER_SIZE];

		// Read input
		delay(10);
		read(buffer);
        
		// Cast input
        float input = atof(buffer);  // 1 to -1

		LOG("Input: ");
		LOGLN(input);

		// Calculate theta inner and outer
		float angles[2];
		getThetaInnerAndOuter(input, angles);

		// Get direction is rover turning
		Direction direction = input >= 0 ? Direction::POSITIVE : Direction::NEGATIVE;
		// Write to servos
        writeToServos(angles[0], angles[1], direction);
    }   
}
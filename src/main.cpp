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
	boden::initServos();        // Initializes servos
	LOGLN("Enter an angle [-1,1]:");
}

void loop() {
    if (Serial.available() >= MIN_CHARS_IN_MESSAGE) {
		static char buffer[BUFFER_SIZE];
		if (boden::read(buffer) < 0) {
			return;
		}
        
		// Cast input
        float input = atof(buffer);

		LOGLN("Input: %.6f" COMMA input);

		// Calculate theta inner and outer
		float angles[2];
		if (boden::getThetaInnerAndOuter(input, angles) < 0) {
			return;
		}

		// Get direction is rover turning
		boden::Direction direction = input >= 0 ? boden::Direction::POSITIVE : boden::Direction::NEGATIVE;
		// Write to servos
        boden::writeToServos(angles[0], angles[1], direction);
    }   
}
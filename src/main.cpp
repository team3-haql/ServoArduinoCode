#include <time.h>

// Enables logging
#define LOGGING

#include "util.hpp"
#include "ackerman.hpp"
#include "char_buffer.hpp"
#include "servo.hpp"
#include "constants.hpp"

void setup() {
	Serial.begin(9600);  // Start serial communication
	ralphee::initServos();        // Initializes servos
	LOG("Enter an angle [-1,1]:\n");
}

void loop() {
    if (Serial.available() >= MIN_CHARS_IN_MESSAGE) {
		static char buffer[BUFFER_SIZE];
		if (ralphee::read(buffer) < 0) {
			return;
		}
        
		// Cast input
        double input = atof(buffer);

		LOG("Input: ");
		LOG(input);
		LOG("\n");

		// Calculate theta inner and outer
		double angles[2];
		if (ralphee::getThetaInnerAndOuter(input, angles) < 0) {
			return;
		}

		// Get direction is rover turning
		ralphee::Direction direction = input >= 0 ? ralphee::Direction::POSITIVE : ralphee::Direction::NEGATIVE;
		// Write to servos
        ralphee::writeToServos(
			static_cast<ralphee::IntAngle>(angles[0]), 
			static_cast<ralphee::IntAngle>(angles[1]), 
			direction);
    }   
}
#pragma once

#include <Servo.h>

#include "util.hpp"
#include "constants.hpp"

static constexpr int g_servoPins[] = {6, 9};
// Prevents accidental mismatch between servopin size and init list.
#define SERVO_COUNT (sizeof(g_servoPins)/sizeof(g_servoPins[0]))
typedef unsigned char ServoSize;
// Makes sure Servo Iterator is large enough to not overflow
static_assert(MAX_TYPE_SIZE(ServoSize) >= SERVO_COUNT-1, "ServoIterator is too small!");

static Servo g_servos[SERVO_COUNT];  // Create servos

/**
 * @brief Attaches pins to servos and writes start angle to them
 * 
 */
void initServos() {
	for (ServoSize i = 0; i < SERVO_COUNT; i++) { // Attach the servo to the defined pin
		g_servos[i].attach(g_servoPins[i]);
		g_servos[i].write(START_ANGLE);
	}
}

/**
 * @brief Writes new positions to servos based off ackerman steering equations. 
 * Graph of servo positions: https://www.desmos.com/calculator/98f1giuocx
 * 
 * @param valInner 
 * @param valOuter 
 * @param swap 
 */
void writeToServos(const int valInner, const int valOuter, Direction swap) {
	if (swap == Direction::POSITIVE) {
		g_servos[0].write(90+valInner);
		g_servos[1].write(90+valOuter);

		// g_servos[2].write(90-valInner);
		// g_servos[3].write(90-valOuter);
	}
	else {
		g_servos[0].write(90-valOuter);
		g_servos[1].write(90-valInner);

		// g_servos[2].write(90+valOuter);
		// g_servos[3].write(90+valInner);
	}
}
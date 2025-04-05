#pragma once

#include <Servo.h>

#include "util.hpp"
#include "constants.hpp"

namespace boden {

// Arduino pin numbers
static constexpr int g_servoPins[] = {6, 9};
// Prevents accidental mismatch between servopin size and init list.
constexpr size_t g_servoCount = sizeof(g_servoPins)/sizeof(g_servoPins[0]);
typedef signed char ServoSize;
// Makes sure Servo Iterator is large enough to not overflow
static_assert(MAX_TYPE_SIZE(ServoSize) >= g_servoCount-1, "ServoIterator is too small!");

static Servo g_servos[g_servoCount];  // Create servos

/**
 * @brief Attaches pins to servos and writes start angle to them
 * 
 */
void initServos() {
	for (ServoSize i = 0; i < static_cast<ServoSize>(g_servoCount); i++) { // Attach the servo to the defined pin
		g_servos[i].attach(g_servoPins[i]);
		g_servos[i].write(START_ANGLE);
	}
}

/**
 * @brief Clamps value between MIN_ANGLE and MAX_ANGLE
 * 
 * @param value 
 * @return int 
 */
inline int clampAngle(int angle) {
	// Either zero or one for both of these.
	bool greaterThanMin = angle >= static_cast<int>(MIN_ANGLE);
	bool lessThanMax = angle <= static_cast<int>(MAX_ANGLE);

	// Prevents branch
	int originalAngle = angle*(greaterThanMin && lessThanMax);
	int minAngle = static_cast<int>(MIN_ANGLE)*(!greaterThanMin); // Becomes min angle if it is greater than min
	int maxAngle = static_cast<int>(MAX_ANGLE)*(!lessThanMax); // Becomes max angle if it is less than max

	// Combine
	return originalAngle + minAngle + maxAngle;
}

/**
 * @brief Writes new positions to servos based off ackerman steering equations. 
 * Graph of servo positions: https://www.desmos.com/calculator/98f1giuocx
 * 
 * @param valInner int angle in degrees
 * @param valOuter int angle in degrees
 * @param swap Direction of inner
 */
void writeToServos(int valInner, int valOuter, Direction direction) {
	if (direction == Direction::POSITIVE) {
		if constexpr(g_servoCount >= 1) // Evaluated at compiletime
			g_servos[0].write(clampAngle(90+valInner));
		if constexpr(g_servoCount >= 2)
			g_servos[1].write(clampAngle(90+valOuter));
		if constexpr(g_servoCount >= 3)
			g_servos[2].write(clampAngle(90-valInner));
		if constexpr(g_servoCount >= 4)
			g_servos[3].write(clampAngle(90-valOuter));
		static_assert(g_servoCount <= 4, "Too many servos! writeToServos cant evaluate them.");
	}
	else {
		if constexpr(g_servoCount >= 1)
			g_servos[0].write(clampAngle(90-valOuter));
		if constexpr(g_servoCount >= 2)
			g_servos[1].write(clampAngle(90-valInner));
		if constexpr(g_servoCount >= 3)
		g_servos[2].write(clampAngle(90+valOuter));
		if constexpr(g_servoCount >= 4)
			g_servos[3].write(clampAngle(90+valInner));
		static_assert(g_servoCount <= 4, "Too many servos! writeToServos cant evaluate them.");
	}
}

} // namespace boden end
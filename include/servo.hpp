#pragma once

#include <Servo.h>

#include "util.hpp"
#include "constants.hpp"

namespace ralphee {

// Arduino pin numbers
static constexpr int32_t g_servoPins[] = {10};
static constexpr int32_t g_servoPins[] = {10};
// Prevents accidental mismatch between servopin size and init list.
static constexpr size_t g_servoCount = sizeof(g_servoPins)/sizeof(g_servoPins[0]);

typedef int8_t ServoSize;
// Makes sure ServoSizeis large enough to not overflow
static_assert(MAX_TYPE_SIZE(ServoSize) >= g_servoCount-1, "ServoIterator is too small!");

static Servo g_servos[g_servoCount];  // Create servos

typedef int16_t IntAngle;
// Makes sure IntAngle is small enough to not underflow
static_assert(MIN_TYPE_SIZE(IntAngle) <= static_cast<int>(MAX_ANGLE), "IntAngle isnt small enough!");
// Makes sure IntAngle is large enough to not overflow
static_assert(MAX_TYPE_SIZE(IntAngle) >= static_cast<int>(MAX_ANGLE), "IntAngle is too small!");
//
static_assert(static_cast<IntAngle>(-1) < 0, "IntAngle must be signed!");

/**
 * @brief Attaches pins to servos and writes start angle to them
 * 
 */
void initServos() {
	for (ServoSize i = 0; i < static_cast<ServoSize>(g_servoCount); i++) { // Attach the servo to the defined pin
		g_servos[i].attach(g_servoPins[i]);
		// Not initializing servo position for safety reasons
		// g_servos[i].write(START_ANGLE);
	}
}

/**
 * @brief Writes new positions to servos based off ackerman steering equations. 
 * Graph of servo positions: https://www.desmos.com/calculator/hd0uh45qs2
 * 
 * @param valInner int32_t angle in degrees
 * @param valOuter int32_t angle in degrees
 * @param direction Direction of inner
 * 
 * @return int8_t
 */
int8_t writeToServos(IntAngle valInner, IntAngle valOuter, Direction direction) {
	if (90 + valInner > MAX_ANGLE) {
		LOG("ERROR: 90 + "); LOG(valInner); LOG(" < "); LOGLN(MAX_ANGLE);
		return -1;
	}
	if (90 - valInner < MIN_ANGLE) {
		LOG("ERROR: 90 - "); LOG(valInner); LOG(" < "); LOGLN(MIN_ANGLE);
		return -2;
	}
	if (90 + valOuter > MAX_ANGLE) {
		LOG("ERROR: 90 + "); LOG(valOuter); LOG(" < "); LOGLN(MAX_ANGLE);
		return -3;
	}
	if (90 - valOuter < MIN_ANGLE) {
		LOG("ERROR: 90 - "); LOG(valOuter); LOG(" < "); LOGLN(MIN_ANGLE);
		return -4;
	}

	if (direction == Direction::POSITIVE) {
		if constexpr(g_servoCount >= 1) // Evaluated at compiletime
			g_servos[0].write(90+valInner);
		if constexpr(g_servoCount >= 2)
			g_servos[1].write(90+valOuter);
		if constexpr(g_servoCount >= 3)
			g_servos[2].write(90-valInner);
		if constexpr(g_servoCount >= 4)
			g_servos[3].write(90-valOuter);
		static_assert(g_servoCount <= 4, "Too many servos! writeToServos cant evaluate them.");
	}
	else {
		if constexpr(g_servoCount >= 1)
			g_servos[0].write(90-valOuter);
		if constexpr(g_servoCount >= 2)
			g_servos[1].write(90-valInner);
		if constexpr(g_servoCount >= 3)
		g_servos[2].write(90+valOuter);
		if constexpr(g_servoCount >= 4)
			g_servos[3].write(90+valInner);
		static_assert(g_servoCount <= 4, "Too many servos! writeToServos cant evaluate them.");
	}
	return 0;
}

} // namespace boden end
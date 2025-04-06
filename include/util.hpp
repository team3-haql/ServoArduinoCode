#pragma once

#include <Arduino.h>
#include <stdio.h>

// Used to add commas into macros, mostly for LOG and LOGLN
#define COMMA ,

#ifdef LOGGING
	// Prints message
    #define LOG(x) Serial.print(x)
	// Prints message with new line at end
    #define LOGLN(x) Serial.println(x)
#else
	// Prints message (disabled)
    #define LOG(x)
	// Prints message with new line at end (disabled)
    #define LOGLN(x)
#endif

// Gets min value
#define MIN(a, b) a*(b > a) + b*(b <= a)
// Gets max value
#define MAX(a, b) a*(b < a) + b*(b >= a)

// Casts bits directly to type, only works on 32 bit systems
#define BIT_CAST(type, bits) static_cast<type>((static_cast<type>(0) | (bits >> 8*(4 - sizeof(type)))))

// Gets min type size, only works on 32 bit systems
#define MIN_TYPE_SIZE(type) MIN(BIT_CAST(type, 0x00000000), BIT_CAST(type, 0x80000000))
// Gets max type size, only works on 32 bit systems
#define MAX_TYPE_SIZE(type) MAX(BIT_CAST(type, 0xffffffff), BIT_CAST(type, 0x7fffffff))

// Converts degrees to radians
#define DEG2RAD(angle) angle*(PI/180.0)
// Converts radians to degrees
#define RAD2DEG(angle) angle*(180.0/PI)

namespace ralphee {

/**
 * @brief Clamps value between 0 and 1
 * 
 * @param value 
 * @return float 
 */
inline float clamp01(float value) {
	bool lessThan1 = value <= 1.0;
	bool valid = value >= 0.0 && lessThan1;
	
	return (value*valid) + !lessThan1;
}

/**
 * @brief Direction that wheels are spun.
 * 
 */
enum class Direction : uint8_t {
	NEGATIVE = 0,
	POSITIVE = 1
};

} // namespace boden end
#pragma once

#include <Arduino.h>
#include <stdio.h>

#define COMMA ,

#ifdef LOGGING
    #define LOG(x) Serial.print(x)
    #define LOGLN(x) Serial.println(x)
#else
    #define LOG(x)
    #define LOGLN(x)
#endif

#define MIN(a, b) a*(b > a) + b*(b <= a)
#define MAX(a, b) a*(b < a) + b*(b >= a)

#define BIT_CAST(type, bits) static_cast<type>((static_cast<type>(0) | (bits >> 8*(4 - sizeof(type)))))

#define MIN_TYPE_SIZE(type) MIN(BIT_CAST(type, 0x00000000), BIT_CAST(type, 0x80000000))
#define MAX_TYPE_SIZE(type) MAX(BIT_CAST(type, 0xffffffff), BIT_CAST(type, 0x7fffffff))

#define DEG2RAD(angle) angle*(PI/180.0)
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
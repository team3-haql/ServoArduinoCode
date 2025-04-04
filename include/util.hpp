#pragma once

#include <Arduino.h>
#include <stdio.h>

#ifdef LOGGING
    #define LOG(x) Serial.print(x)
    #define LOGLN(x) Serial.println(x)
#else
    #define LOG(x)
    #define LOGLN(x)
#endif

#define BIT_CAST(type, bits) static_cast<type>((static_cast<type>(0) | (bits >> 8*(4 - sizeof(type)))))
#define MAX_TYPE_SIZE(type) \
    BIT_CAST(type, 0xffffffff)*(BIT_CAST(type, 0xffffffff) >= BIT_CAST(type, 0x7fffffff)) + \
    BIT_CAST(type, 0x7fffffff)*(BIT_CAST(type, 0xffffffff) < BIT_CAST(type, 0x7fffffff))

#define MIN(a, b) a*(b > a) + b*(b <= a)

#define DEG2RAD(angle) angle*(PI/180.0)
#define RAD2DEG(angle) angle*(180.0/PI)

inline float clamp01(float value) {
	bool lessThan1 = value <= 1;
	bool valid = value >= 0 && lessThan1;
	
	return (value*valid) + lessThan1;
}

enum class Direction {
	NEGATIVE = 0,
	POSITIVE = 1
};
#pragma once

#include "util.hpp"
#include "constants.hpp"

namespace ralphee {

/**
 * @brief t == -1 => MIN_ANGLE, t == 1 => MAX_ANGLE
 * 
 * @param t Value in [-1, 1]
 * @return double 
 */
inline double lerp(double t) {
	double normalizedT = (t + 1.0)/2;
	normalizedT = clamp01(normalizedT);
	return ((1.0 - normalizedT)*MIN_ANGLE + normalizedT*MAX_ANGLE);
}

/**
 * @brief Calculate Theta Inner and Theta Outer. 
 * Graph of equations: https://www.desmos.com/calculator/hd0uh45qs2
 * 
 * @param input double in [-1,1] (If it is not it will be clamped)
 * @param[out] outAnglesDeg Output array of 2 points
 * 
 * @return int8_t
 */
int8_t getThetaInnerAndOuter(double input, double* outAnglesDeg) {
	double thetaInner = DEG2RAD(abs((lerp(input) - 90.0)));

	LOG("Theta Inner: "); LOGLN(thetaInner);

	double denominator = (L/tan(thetaInner)) + W;

	if (denominator != denominator) {
		LOG("ERROR: Denominator is NAN\n");
		return -1;
	}

	LOG("Denominator: "); LOGLN(denominator);

	double thetaOuter = atan(L / denominator);

	if (thetaOuter != thetaOuter) {
		LOG("ERROR: thetaOuter is NAN\n");
		return -2;
	}

	LOG("Theta Outer: "); LOGLN(thetaOuter);

	outAnglesDeg[0] = RAD2DEG(thetaInner);
	outAnglesDeg[1] = RAD2DEG(thetaOuter);
	return 0;
}

} // namespace boden end
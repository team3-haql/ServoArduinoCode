#pragma once

#include "util.hpp"
#include "constants.hpp"

namespace boden {

/**
 * @brief t == -1 => MIN_ANGLE, t == 1 => MAX_ANGLE
 * 
 * @param t Value in [-1, 1]
 * @return float 
 */
inline float lerp(float t) {
	float normalizedT = (t + 1.0)/2;
	normalizedT = clamp01(normalizedT);
	return ((1.0 - normalizedT)*MIN_ANGLE + normalizedT*MAX_ANGLE);
}

/**
 * @brief Calculate Theta Inner and Theta Outer. 
 * Graph of equations: https://www.desmos.com/calculator/98f1giuocx
 * 
 * @param input Float in [-1,1] (If it is not it will be clamped)
 * @param[out] outAnglesDeg Output array of 2 points
 */
void getThetaInnerAndOuter(float input, float* outAnglesDeg) {
	float thetaInner = DEG2RAD(abs((lerp(input) - 90.0)));

	LOG("Theta Inner: ");
	LOGLN(thetaInner);

	float denominator = (L/tan(thetaInner)) + W;
	denominator += 1e-6f - 1e-6f*(denominator == 0.0);

	LOG("Denominator: ");
	LOGLN(denominator);

	float thetaOuter = atan(L / denominator);

	LOG("Theta Outer: ");
	LOGLN(thetaOuter);

	outAnglesDeg[0] = RAD2DEG(thetaInner);
	outAnglesDeg[1] = RAD2DEG(thetaOuter);
}

} // namespace boden end
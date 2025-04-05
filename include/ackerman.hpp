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
 * Graph of equations: https://www.desmos.com/calculator/hd0uh45qs2
 * 
 * @param input Float in [-1,1] (If it is not it will be clamped)
 * @param[out] outAnglesDeg Output array of 2 points
 */
void getThetaInnerAndOuter(float input, float* outAnglesDeg) {
	float thetaInner = DEG2RAD(abs((lerp(input) - 90.0)));

	LOGLN("Theta Inner: %.6f" COMMA thetaInner);

	float denominator = (L/tan(thetaInner)) + W;
	denominator += 1e-6f - 1e-6f*(denominator == 0.0);

	LOGLN("Denominator: %.6f" COMMA denominator);

	float thetaOuter = atan(L / denominator);

	LOGLN("Theta Outer: %.6f" COMMA thetaOuter);

	outAnglesDeg[0] = RAD2DEG(thetaInner);
	outAnglesDeg[1] = RAD2DEG(thetaOuter);
}

} // namespace boden end
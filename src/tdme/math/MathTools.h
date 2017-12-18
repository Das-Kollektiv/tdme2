#pragma once

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>

using tdme::math::Math;

/** 
 * Additional mathematical functions
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::MathTools final
{

public:
	static constexpr float EPSILON { 0.0000001f };
	static constexpr float DEG2RAD { 0.017453294f };
	static constexpr float g { 9.80665f };

	/**
	 * Clamps a float value to min or max value
	 * @param value
	 * @param min value
	 * @param max value
	 * @return clamped value
	 */
	inline static float clamp(float value, float min, float max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	/**
	 * Returns sign of value
	 * @param value
	 * @return -1 if value is negative or +1 if positive
	 */
	inline static float sign(float value) {
		return value / Math::abs(value);
	}

	/**
	 * Do the square product
	 * @param value
	 * @return
	 */
	inline static float square(float value) {
		return value * value;
	}

};


#pragma once

#include <cmath>
#include <cstdlib>

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

/** 
 * Math
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::Math final
{
public:
	static constexpr double E { 2.718281828459045 };
	static constexpr double PI { 3.141592653589793 };

	/**
	 * Returns absolute value
	 * @param value
	 * @return absolute value
	 */
	inline static int32_t abs(int32_t value) {
		return ::abs(value);
	}

	/**
	 * Returns absolute value
	 * @param value
	 * @return absolute value
	 */
	inline static float abs(float value) {
		return ::fabs(value);
	}

	/**
	 * Returns the arc cosine of a value
	 * @param value
	 * @return arc cosine
	 */
	inline static float acos(float value) {
		return ::acos(value);
	}

	/**
	 * Returns the arc sine of a value
	 * @param value
	 * @return arc sine
	 */
	inline static float asin(float value) {
		return ::asin(value);
	}

	/**
	 * Returns the arc tangent of a value
	 * @param value
	 * @return arc tangent
	 */
	inline static float atan(float value) {
		return ::atan(value);
	}

	/**
	 * Returns the angle from the conversion of rectangular coordinates to polar coordinates.
	 * @param y
	 * @param x
	 * @return angle
	 *
	 */
	inline static float atan2(float y, float x) {
		return ::atan2(y, x);
	}

	/**
	 * Returns the higher integer value of given value
	 * @param value
	 * @return higher integer
	 */
	inline static float ceil(float value) {
		return ::ceil(value);
	}

	/**
	 * Returns the cosine of an angle
	 * @param value
	 * @return cosine
	 */
	inline static float cos(float value) {
		return ::cos(value);
	}

	/**
	 * Returns the lower integer value of given value
	 * @param value
	 * @return lower integer
	 */
	inline static float floor(float value) {
		return std::floor(value);
	}

	/**
	 * Returns the higher value of given values
	 * @param value 1
	 * @param value 2
	 * @return higher value
	 */
	inline static int32_t max(int32_t value1, int32_t value2) {
		return value1 > value2?value1:value2;
	}

	/**
	 * Returns the higher value of given values
	 * @param value 1
	 * @param value 2
	 * @return higher value
	 */
	inline static float max(float value1, float value2) {
		return value1 > value2?value1:value2;
	}

	/**
	 * Returns the lesser value of given values
	 * @param value 1
	 * @param value 2
	 * @return lesser value
	 */
	inline static int32_t min(int32_t value1, int32_t value2) {
		return value1 < value2?value1:value2;
	}

	/**
	 * Returns the lesser value of given values
	 * @param value 1
	 * @param value 2
	 * @return lesser value
	 */
	inline static float min(float value1, float value2) {
		return value1 < value2?value1:value2;
	}

	/**
	 * Returns the value of the value 1 raised to the power of value2
	 * @param value 1
	 * @param value 2
	 * @return pow
	 */
	inline static double pow(double value1, double value2) {
		return std::pow(value1, value2);
	}

	/**
	 * Returns a random value between 0.0 .. 1.0
	 * @return random value
	 */
	inline static float random() {
		return (float)rand() / RAND_MAX;
	}

	/**
	 * Returns the sine of an angle
	 * @param value
	 * @return sine
	 */
	inline static float sin(float value) {
		return ::sin(value);
	}

	/**
	 * Returns the square of given value
	 * @param value
	 * @return squaere
	 */
	inline static float sqrt(float value) {
		return ::sqrt(value);
	}

	/**
	 * Returns the tangent of an angle
	 * @param value
	 * @return tangent
	 */
	inline static float tan(float value) {
		return ::tan(value);
	}

};

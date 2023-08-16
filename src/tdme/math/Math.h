#pragma once

#include <cmath>
#include <cstdlib>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#define NOMINMAX
	#undef max
	#undef min
#endif

/**
 * Standard math functions
 * @author Andreas Drewke
 */
class tdme::math::Math final
{
public:
	static constexpr float PI { 3.141592653589793f };
	static constexpr float EPSILON { 0.0000001f };
	static constexpr float DEG2RAD { 0.017453294f };
	static constexpr float G { 9.80665f };

	/**
	 * Clamps a value to min or max value
	 * @param value value
	 * @param min min value
	 * @param max max value
	 * @return clamped value
	 */
	inline static auto clamp(auto value, auto min, auto max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	/**
	 * Returns sign of value
	 * @param value value
	 * @return -1 if value is negative or +1 if positive
	 */
	inline static auto sign(auto value) {
		if (abs(value) < EPSILON) return value + 1;
		return value / Math::abs(value);
	}

	/**
	 * Do the square product
	 * @param value value
	 * @return square product
	 */
	inline static auto square(auto value) {
		return value * value;
	}

	/**
	 * Returns absolute value
	 * @param value value
	 * @return absolute value
	 */
	inline static auto abs(auto value) {
		return std::abs(value);
	}

	/**
	 * Returns the arc cosine of a value
	 * @param x x
	 * @return arc cosine of x
	 */
	inline static float acos(float x) {
		return std::acos(x);
	}

	/**
	 * Returns the arc sine of a value
	 * @param x x
	 * @return arc sine of x
	 */
	inline static float asin(float x) {
		return std::asin(x);
	}

	/**
	 * Returns the arc tangent of a value
	 * @param x x
	 * @return arc tangent of x
	 */
	inline static float atan(float x) {
		return std::atan(x);
	}

	/**
	 * Returns the angle from the conversion of rectangular coordinates to polar coordinates.
	 * @param y y
	 * @param x x
	 * @return arc tangent of y/x
	 */
	inline static float atan2(float y, float x) {
		return std::atan2(y, x);
	}

	/**
	 * Returns the higher integer value of given value
	 * @param value value
	 * @return higher integer
	 */
	inline static float ceil(float value) {
		return std::ceil(value);
	}

	/**
	 * Returns the cosine of an angle
	 * @param x x
	 * @return cosine of x
	 */
	inline static float cos(float x) {
		return std::cos(x);
	}

	/**
	 * Returns the lower integer value of given value
	 * @param value value
	 * @return lower integer
	 */
	inline static float floor(float value) {
		return std::floor(value);
	}

	/**
	 * Returns the higher value of given values
	 * @param value1 value 1
	 * @param value2 value 2
	 * @return higher value
	 */
	inline static auto max(auto value1, auto value2) {
		return value1 > value2?value1:value2;
	}

	/**
	 * Returns the lesser value of given values
	 * @param value1 value 1
	 * @param value2 value 2
	 * @return lesser value
	 */
	inline static auto min(auto value1, auto value2) {
		return value1 < value2?value1:value2;
	}

	/**
	 * Returns the rounded value of given float value
	 * @param value value
	 * @return rounded value
	 */
	inline static float round(float value) {
		return std::round(value);
	}

	/**
	 * Returns the value of base raised to the power
	 * @param base base
	 * @param power power
	 * @return base raised to the power
	 */
	inline static auto pow(auto base, auto power) {
		return std::pow(base, power);
	}

	/**
	 * Returns a random value between 0.0 .. 1.0
	 * @return random value
	 */
	inline static float random() {
		return (float)rand() / (float)RAND_MAX;
	}

	/**
	 * Returns the sine of an angle
	 * @param x x
	 * @return sin of x
	 */
	inline static float sin(float x) {
		return std::sin(x);
	}

	/**
	 * Returns the square root of given value
	 * @param value value
	 * @return square root
	 */
	inline static float sqrt(float value) {
		return std::sqrt(value);
	}

	/**
	 * Returns the tangent of an angle
	 * @param x x
	 * @return tangent of x
	 */
	inline static float tan(float x) {
		return std::tan(x);
	}

	/**
	 * Returns e raised to the given power
	 * @param power power
	 * @return e raised to the given power
	 */
	inline static float exp(float power) {
		return std::exp(power);
	}

	/**
	 * Returns the natural (base e) logarithm of value
	 * @param value value
	 * @return natural (base e) logarithm of value
	 */
	inline static float log(float value) {
		return std::log(value);
	}

	/**
	 * Returns modulo of value, so that return value is -range < value < range
	 * @param value value
	 * @param range range
	 * @return modulo of value
	 */
	inline static auto mod(auto value, auto range) {
		return value % range;
	}

	/**
	 * Returns modulo of value, so that return value is -range < value < range
	 * @param value value
	 * @param range range
	 * @return modulo of value
	 */
	inline static float mod(float value, float range) {
		return std::fmod(value, range);
	}

	/**
	 * Returns absolute modulo of value, so that return value is 0 <= value < range
	 * @param value value
	 * @param range range
	 * @return modulo of value
	 */
	inline static auto absmod(auto value, auto range) {
		while (value < 0.0f) value+= range;
		return value % range;
	}

	/**
	 * Returns absolute modulo of value, so that return value is 0.0f <= value < range
	 * @param value value
	 * @param range range
	 * @return modulo of value
	 */
	inline static float absmod(float value, float range) {
		while (value < 0.0f) value+= range;
		return std::fmod(value, range);
	}

};

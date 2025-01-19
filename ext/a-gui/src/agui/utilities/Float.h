#pragma once

#include <agui/agui.h>
#include <agui/math/Math.h>
#include <agui/utilities/fwd-agui.h>

#include <cmath>
#include <limits>
#include <string>
#include <string_view>

using std::isinf;
using std::isfinite;
using std::isfinite;
using std::isnan;
using std::numeric_limits;
using std::string;
using std::string_view;

// namespaces
namespace agui {
namespace utilities {
	using agui::math::Math;
}
}

/**
 * Float class
 * @author Andreas Drewke
 */
class agui::utilities::Float final
{
public:
	static constexpr float MAX_VALUE { numeric_limits<float>::max() };
	static constexpr float MIN_VALUE { -numeric_limits<float>::max() };
	static constexpr float NAN_VALUE { numeric_limits<float>::quiet_NaN() };

	/**
	 * Check if given string is a float string
	 * @param str string
	 * @return given string is float
	 */
	static bool is(const string& str);

	/**
	 * Check if given string is a float string
	 * @param str string
	 * @return given string is float
	 */
	static bool viewIs(const string_view& str);

	/**
	 * Parse float
	 * @param str string
	 * @return float
	 */
	static float parse(const string& str);

	/**
	 * Parse float
	 * @param str string
	 * @return float
	 */
	static float viewParse(const string_view& str);

	/**
	 * Check if float is not a number
	 * @param value float value
	 * @return if value is not a number
	 */
	inline static bool isNaN(float value) {
		return isnan(value);
	}

	/**
	 * Check if float is infinite
	 * @param value float value
	 * @return if value is infinite
	 */
	inline static bool isInfinite(float value) {
		return isinf(value);
	}

	/**
	 * Check if float is infinite
	 * @param value float value
	 * @return if value is finite
	 */
	inline static bool isFinite(float value) {
		return isfinite(value);
	}

	/**
	 * Interpolates between a and b by 0f<=t<=1f linearly
	 * @param a float a
	 * @param b float b
	 * @param t t
	 * @return interpolated float value
	 */
	inline static float interpolateLinear(float a, float b, float t) {
		return (b * t) + ((1.0f - t) * a);
	}

	/**
	 * @return f1 and f2 are equals
	 */
	inline static bool equals(float f1, float f2) {
		return Math::abs(f2 - f1) < Math::EPSILON;
	}

};

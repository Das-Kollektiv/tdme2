// Generated from /tdme/src/tdme/utils/Key.java

#pragma once

#include <tdme/utils/fwd-tdme.h>

#include <limits>
#include <string>

using std::numeric_limits;
using std::wstring;

/**
 * Float
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::Float final
{
public:
	static constexpr int32_t MAX_EXPONENT { 127 };
	static constexpr float MAX_VALUE { 3.4028235E38f };
	static constexpr int32_t MIN_EXPONENT { -126 };
	static constexpr float MIN_NORMAL { 1.17549435E-38f };
	static constexpr float MIN_VALUE { 1.4E-45f };
	static constexpr float NEGATIVE_INFINITY { (-numeric_limits<float>::infinity()) };
	static constexpr float NaN { numeric_limits<float>::quiet_NaN() };
	static constexpr float POSITIVE_INFINITY { numeric_limits<float>::infinity() };
	static constexpr int32_t SIZE { 32 };

	/**
	 * Parse float
	 * @param string
	 * @return float
	 */
	static float parseFloat(const wstring& string);

	/**
	 * Check if float is nane
	 * @param float value
	 */
	static bool isNaN(float value);
};

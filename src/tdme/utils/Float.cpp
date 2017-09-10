#include <tdme/utils/Float.h>

#include <cmath>
#include <string>

using std::string;
using std::stof;
using std::isnan;

using tdme::utils::Float;

constexpr int32_t tdme::utils::Float::MAX_EXPONENT;
constexpr float tdme::utils::Float::MAX_VALUE;
constexpr int32_t tdme::utils::Float::MIN_EXPONENT;
constexpr float tdme::utils::Float::MIN_NORMAL;
constexpr float tdme::utils::Float::MIN_VALUE;
constexpr float tdme::utils::Float::NEGATIVE_INFINITY;
constexpr float tdme::utils::Float::NaN;
constexpr float tdme::utils::Float::POSITIVE_INFINITY;
constexpr int32_t tdme::utils::Float::SIZE;

float Float::parseFloat(const wstring& string) {
	if (string.length() == 0) return -1.0f;
	return stof(string);
}

bool Float::isNaN(float value)
{
	return isnan(value);
}

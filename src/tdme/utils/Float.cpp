#include <tdme/utils/Float.h>

#include <string>

using std::string;
using std::to_string;
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

float Float::parseFloat(const string& str) {
	if (str.length() == 0) return 0.0f;
	return stof(str);
}

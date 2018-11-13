#include <tdme/utils/Float.h>

#include <string>

using std::string;
using std::to_string;
using std::stof;
using std::isnan;

using tdme::utils::Float;

constexpr float tdme::utils::Float::MAX_VALUE;
constexpr float tdme::utils::Float::MIN_VALUE;
constexpr float tdme::utils::Float::NaN;
constexpr int32_t tdme::utils::Float::SIZE;

float Float::parseFloat(const string& str) {
	if (str.length() == 0) return 0.0f;
	return stof(str);
}

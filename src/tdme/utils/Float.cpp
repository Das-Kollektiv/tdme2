#include <tdme/utils/Float.h>

#include <string>

using std::string;
using std::stof;

using tdme::utils::Float;

float Float::parseFloat(const wstring& string) {
	if (string.length() == 0) return -1.0f;
	return stof(string);
}

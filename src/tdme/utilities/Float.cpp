#include <tdme/utilities/Float.h>

#include <algorithm>
#include <cctype>
#include <string>

#include <tdme/utilities/StringTools.h>

using std::find_if;
using std::isnan;
using std::stof;
using std::string;
using std::to_string;

using tdme::utilities::Float;

using tdme::utilities::StringTools;

bool Float::isFloat(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	int dotCount = 0;
	return
		str.empty() == false &&
		find_if(trimmedStr.begin() + (trimmedStr[0] == '-'?1:0), trimmedStr.end(), [&dotCount](char c) { return isdigit(c) == false && (c != '.' || ++dotCount > 1); }) == trimmedStr.end();
}

float Float::parseFloat(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	if (trimmedStr.empty() == true) return 0.0f;
	if (trimmedStr == "-") return -0.0f;
	int dotCount = 0;
	int digitSum = 0;
	return
		(str.empty() == false &&
		find_if(trimmedStr.begin() + (trimmedStr[0] == '-'?1:0), trimmedStr.end(), [&dotCount, &digitSum](char c) { if (isdigit(c) == true) digitSum+= c - '0'; return isdigit(c) == false && (c != '.' || ++dotCount > 1); }) == trimmedStr.end()) == true && digitSum > 0?stof(trimmedStr):0.0f;
}

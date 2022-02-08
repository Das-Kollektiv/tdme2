#include <tdme/utilities/Float.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>
#include <string_view>

#include <tdme/tdme.h>
#include <tdme/utilities/StringTools.h>

using std::find_if;
using std::isnan;
using std::stof;
using std::string;
using std::string_view;
using std::to_string;

using tdme::utilities::Float;

using tdme::utilities::StringTools;

bool Float::is(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	int dotCount = 0;
	return
		str.empty() == false &&
		find_if(trimmedStr.begin() + (trimmedStr[0] == '-'?1:0), trimmedStr.end(), [&dotCount](char c) { return isdigit(c) == false && (c != '.' || ++dotCount > 1); }) == trimmedStr.end();
}

bool Float::viewIs(const string_view& str) {
	auto trimmedStr = StringTools::viewTrim(str);
	int dotCount = 0;
	return
		str.empty() == false &&
		find_if(trimmedStr.begin() + (trimmedStr[0] == '-'?1:0), trimmedStr.end(), [&dotCount](char c) { return isdigit(c) == false && (c != '.' || ++dotCount > 1); }) == trimmedStr.end();
}

float Float::parse(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	if (trimmedStr.empty() == true) return 0.0f;
	if (trimmedStr == "-") return -0.0f;
	int dotCount = 0;
	int digitSum = 0;
	return
		(str.empty() == false &&
		find_if(trimmedStr.begin() + (trimmedStr[0] == '-'?1:0), trimmedStr.end(), [&dotCount, &digitSum](char c) { if (isdigit(c) == true) digitSum+= c - '0'; return isdigit(c) == false && (c != '.' || ++dotCount > 1); }) == trimmedStr.end()) == true && digitSum > 0?stof(trimmedStr):0.0f;
}

float Float::viewParse(const string_view& str) {
	auto trimmedStr = StringTools::viewTrim(str);
	if (trimmedStr.empty() == true) return 0.0f;
	if (trimmedStr == "-") return -0.0f;
	// TODO: we need to do this this way as long there is no from_chars with float
	char buf[str.size() + 1];
	memcpy(buf, &trimmedStr[0], trimmedStr.size());
	buf[str.size()] = 0;
	return atof(buf);
}

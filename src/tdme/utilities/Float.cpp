#include <tdme/utilities/Float.h>

#include <algorithm>
#include <cctype>
#include <string>

using std::find_if;
using std::isnan;
using std::stof;
using std::string;
using std::to_string;

using tdme::utilities::Float;

bool Float::isFloat(const string& str) {
	int dotCount = 0;
	return
		str.empty() == false &&
		find_if(str.begin() + (str[0] == '-'?1:0), str.end(), [&dotCount](char c) { return isdigit(c) == false && (c != '.' || ++dotCount > 1); }) == str.end();
}

float Float::parseFloat(const string& str) {
	int dotCount = 0;
	int digitSum = 0;
	return
		(str.empty() == false &&
		find_if(str.begin() + (str[0] == '-'?1:0), str.end(), [&dotCount, &digitSum](char c) { if (isdigit(c) == true) digitSum+= c - '0'; return isdigit(c) == false && (c != '.' || ++dotCount > 1); }) == str.end()) == true && digitSum > 0?stof(str):0.0f;
}

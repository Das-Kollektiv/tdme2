#include <tdme/utilities/Integer.h>

#include <string.h>

#include <algorithm>
#include <cctype>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using tdme::utilities::Console;
using tdme::utilities::StringTools;

using std::find_if;
using std::isdigit;
using std::stoi;
using std::string;
using std::to_string;

using tdme::utilities::Integer;

bool Integer::isInt(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	return
		trimmedStr.empty() == false && find_if(trimmedStr.begin() + (trimmedStr[0] == '-'?1:0), trimmedStr.end(), [](char c) { return isdigit(c) == false; }) == trimmedStr.end();
}

int Integer::parseInt(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	if (trimmedStr.empty() == true) return 0;
	if (trimmedStr == "-") return -0;
	return stoi(trimmedStr);
}

void Integer::encode(const uint32_t decodedInt, string& encodedString) {
	encodedString = "";
	char encodingCharSet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW-+/*.";
	for (auto i = 0; i < 6; i++) {
		auto charIdx = (decodedInt >> (i * 6)) & 63;
		encodedString = encodingCharSet[charIdx] + encodedString;
	}
}

bool Integer::decode(const string& encodedString, uint32_t& decodedInt) {
	char encodingCharSet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW-+/*.";
	decodedInt = 0;
	for (auto i = 0; i < encodedString.length(); i++) {
		auto codeIdx = -1;
		char c = encodedString[encodedString.length() - i - 1];
		char* codePtr = strchr(encodingCharSet, c);
		if (codePtr == NULL) {
			return false;
		} else {
			codeIdx = codePtr - encodingCharSet;
		}
		decodedInt+= codeIdx << (i * 6);
	}
	return true;
}


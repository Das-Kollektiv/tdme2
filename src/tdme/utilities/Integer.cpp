#include <tdme/utilities/Integer.h>

#include <string.h>

#include <algorithm>
#include <cctype>
#include <charconv>
#include <string>
#include <string_view>

#include <tdme/tdme.h>
#include <tdme/utilities/StringTools.h>

using tdme::utilities::StringTools;

using std::find_if;
using std::from_chars;
using std::isdigit;
using std::stoi;
using std::string;
using std::string_view;
using std::to_string;

using tdme::utilities::Integer;

bool Integer::is(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	return
		trimmedStr.empty() == false &&
		find_if(
			trimmedStr.begin() + (trimmedStr[0] == '-'?1:0),
			trimmedStr.end(),
			[](unsigned char c) {
				return isdigit(c) == 0;
			}
		) == trimmedStr.end();
}

bool Integer::viewIs(const string_view& str) {
	auto trimmedStr = StringTools::viewTrim(str);
	return
		trimmedStr.empty() == false &&
		find_if(
			trimmedStr.begin() + (trimmedStr[0] == '-'?1:0),
			trimmedStr.end(),
			[](unsigned char c) {
				return isdigit(c) == 0;
			}
		) == trimmedStr.end();
}

int Integer::parse(const string& str) {
	auto trimmedStr = StringTools::trim(str);
	if (trimmedStr.empty() == true) return 0;
	if (trimmedStr == "-") return -0;
	return stoi(trimmedStr);
}

int Integer::viewParse(const string_view& str) {
	auto trimmedStr = StringTools::viewTrim(str);
	if (trimmedStr.empty() == true) return 0;
	if (trimmedStr == "-") return -0;
	int result;
	from_chars(&trimmedStr[0], &trimmedStr[trimmedStr.size()], result);
	return result;
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

bool Integer::viewDecode(const string_view& encodedString, uint32_t& decodedInt) {
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

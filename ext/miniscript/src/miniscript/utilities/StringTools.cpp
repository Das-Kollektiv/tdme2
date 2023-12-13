#include <miniscript/utilities/StringTools.h>

#include <algorithm>
#include <functional>
#include <regex>
#include <string>
#include <string_view>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/StringTokenizer.h>

using std::find_if;
using std::isspace;
using std::regex;
using std::regex_match;
using std::regex_replace;
using std::replace;
using std::string;
using std::string_view;
using std::tolower;
using std::toupper;
using std::transform;

using miniscript::utilities::StringTools;

using miniscript::utilities::Character;
using miniscript::utilities::StringTokenizer;

const string StringTools::replace(const string& src, const char what, const char by, int64_t beginIndex) {
	string result = src;
	std::replace(result.begin() + beginIndex, result.end(), what, by);
	return result;
}

const string StringTools::replace(const string& src, const string& what, const string& by, int64_t beginIndex) {
	string result = src;
	if (what.empty()) return result;
	while ((beginIndex = result.find(what, beginIndex)) != std::string::npos) {
		result.replace(beginIndex, what.length(), by);
		beginIndex += by.length();
	}
	return result;
}

bool StringTools::equalsIgnoreCase(const string& string1, const string& string2) {
	string stringA = string1;
	string stringB = string2;
	transform(stringA.begin(), stringA.end(), stringA.begin(), (int(*)(int))toupper);
	transform(stringB.begin(), stringB.end(), stringB.begin(), (int(*)(int))toupper);
	return stringA == stringB;
}

const string StringTools::trim(const string& src) {
	string result = src;
	result.erase(
		result.begin(),
		find_if(
			result.begin(),
			result.end(),
			[](int c) {
				return isspace(c) == 0;
			}
		)
	);
	result.erase(
		find_if(
			result.rbegin(),
			result.rend(),
			[](int c) {
				return isspace(c) == 0;
			}
		).base(),
		result.end()
	);
	return result;
}

const string_view StringTools::viewTrim(const string_view& src) {
	int64_t start = 0;
	for (int64_t i = 0; i < src.size(); i++) {
		if (isspace(src[i]) != 0) start++; else break;
	}
	int64_t end = 0;
	for (int64_t i = src.size() - 1; i >= 0; i--) {
		if (isspace(src[i]) != 0) end++; else break;
	}
	return string_view(&src[start], src.size() - start - end);
}

const string StringTools::toLowerCase(const string& src) {
	string result = src;
	transform(result.begin(), result.end(), result.begin(), (int(*)(int))tolower);
	return result;
}

const string StringTools::toUpperCase(const string& src) {
	string result = src;
	transform(result.begin(), result.end(), result.begin(), (int(*)(int))toupper);
	return result;
}

bool StringTools::regexMatch(const string& src, const string& pattern) {
	// TODO: return found groups
	return regex_match(src, regex(pattern, std::regex::ECMAScript));
}

bool StringTools::regexSearch(const string& src, const string& pattern) {
	// TODO: return found groups
	return regex_search(src, regex(pattern, std::regex::ECMAScript));
}

const string StringTools::regexReplace(const string& src, const string& pattern, const string& by) {
	return regex_replace(src, regex(pattern, std::regex::ECMAScript), by);
}

const vector<string> StringTools::tokenize(const string& str, const string& delimiters, bool emptyTokens) {
	StringTokenizer t;
	t.tokenize(str, delimiters, emptyTokens);
	return t.getTokens();
}

int64_t StringTools::getUTF8Length(const string& str) {
	UTF8CharacterIterator u8It(str);
	u8It.seekCharacterPosition(4611686018427387903); // 2 ^ 62 - 1
	return u8It.getCharacterPosition();
}

const string StringTools::getUTF8CharAt(const string& str, int64_t index) {
	// utf8 character iterator
	UTF8CharacterIterator u8It(str);
	u8It.seekCharacterPosition(index);
	//
	return u8It.hasNext() == true?::miniscript::utilities::Character::toString(u8It.next()):string();
}

int64_t StringTools::getUTF8BinaryIndex(const string& str, int64_t charIdx) {
	UTF8CharacterIterator u8It(str);
	u8It.seekCharacterPosition(charIdx);
	return u8It.getBinaryPosition();
}

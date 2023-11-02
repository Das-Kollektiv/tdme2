#include <tdme/utilities/StringTools.h>

#include <algorithm>
#include <functional>
#include <regex>
#include <string>
#include <string_view>

#include <tdme/tdme.h>
#include <tdme/utilities/StringTokenizer.h>

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

using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

const string StringTools::replace(const string& src, const char what, const char by, int beginIndex) {
	string result = src;
	std::replace(result.begin() + beginIndex, result.end(), what, by);
	return result;
}

const string StringTools::replace(const string& src, const string& what, const string& by, int beginIndex) {
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
	auto start = 0;
	for (auto i = 0; i < src.size(); i++) {
		if (isspace(src[i]) != 0) start++; else break;
	}
	auto end = 0;
	for (int i = src.size() - 1; i >= 0; i--) {
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
	return regex_match(src, regex(pattern));
}

bool StringTools::regexSearch(const string& src, const string& pattern) {
	// TODO: return found groups
	return regex_search(src, regex(pattern, std::regex::ECMAScript));
}

const string StringTools::regexReplace(const string& src, const string& pattern, const string& by) {
	return regex_replace(src, regex(pattern, std::regex::ECMAScript), by);
}

const vector<string> StringTools::tokenize(const string& str, const string& delimiters) {
	StringTokenizer t;
	t.tokenize(str, delimiters);
	return t.getTokens();
}

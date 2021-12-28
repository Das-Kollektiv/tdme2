#include <tdme/utilities/StringTools.h>

#include <algorithm>
#include <functional>
#include <regex>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/StringTokenizer.h>

using std::find_if;
using std::isspace;
using std::regex;
using std::regex_match;
using std::regex_replace;
using std::replace;
using std::string;
using std::tolower;
using std::toupper;
using std::transform;

using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

const bool StringTools::startsWith(const string& src, const string& prefix) {
    return src.find(prefix) == 0;
}

const bool StringTools::endsWith(const string& src, const string& suffix) {
	return
		src.size() >= suffix.size() &&
		src.compare(src.size() - suffix.size(), suffix.size(), suffix) == 0;
}

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

int32_t StringTools::firstIndexOf(const string& src, char what) {
	return src.find_first_of(what);
}

int32_t StringTools::firstIndexOf(const string& src, const string& what) {
	return src.find_first_of(what);
}

int32_t StringTools::lastIndexOf(const string& src, char what) {
	return src.find_last_of(what);
}

int32_t StringTools::lastIndexOf(const string& src, const string& what) {
	return src.find_last_of(what);
}

const string StringTools::substring(const string& src, int32_t beginIndex) {
	return src.substr(beginIndex);
}

const string StringTools::substring(const string& src, int32_t beginIndex, int32_t endIndex) {
	return src.substr(beginIndex, endIndex - beginIndex);
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
				return !isspace(c);
			}
		)
	);
	result.erase(
		find_if(
			result.rbegin(),
			result.rend(),
			[](int c) {
	        	return !isspace(c);
	    	}
		).base(),
		result.end()
	);
	return result;
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
	return regex_match(src, regex(pattern));
}

const string StringTools::regexReplace(const string& src, const string& pattern, const string& by) {
	return regex_replace(src, regex(pattern), by);
}

const vector<string> StringTools::tokenize(const string& str, const string& delimiters) {
	StringTokenizer t;
	t.tokenize(str, delimiters);
	return t.getTokens();
}

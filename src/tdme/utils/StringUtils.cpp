#include <tdme/utils/StringUtils.h>

#include <algorithm>
#include <functional>
#include <regex>
#include <string>

using std::find_if;
using std::isspace;
using std::not1;
using std::replace;
using std::regex_match;
using std::regex_replace;
using std::string;
using std::transform;
using std::tolower;
using std::toupper;
using std::string;
using std::regex;

using tdme::utils::StringUtils;

const bool StringUtils::startsWith(const string& src, const string& prefix) {
    return src.find(prefix) == 0;
}

const bool StringUtils::endsWith(const string& src, const string& suffix) {
	return
		src.size() >= suffix.size() &&
		src.compare(src.size() - suffix.size(), suffix.size(), suffix) == 0;
}

const string StringUtils::replace(const string& src, const char what, const char by) {
	string result = src;
	std::replace(result.begin(), result.end(), what, by);
	return result;
}

const string StringUtils::replace(const string& src, const string& what, const string& by) {
	string result = src;
	if (what.empty()) return result;
	size_t start_pos = 0;
	while ((start_pos = result.find(what, start_pos)) != std::string::npos) {
		result.replace(start_pos, what.length(), by);
		start_pos += by.length();
	}
	return result;
}

int32_t StringUtils::lastIndexOf(const string& src, char what) {
	return src.find_last_of(what);
}

const string StringUtils::substring(const string& src, int32_t beginIndex) {
	return src.substr(beginIndex);
}

const string StringUtils::substring(const string& src, int32_t beginIndex, int32_t endIndex) {
	return src.substr(beginIndex, endIndex - beginIndex);
}

bool StringUtils::equalsIgnoreCase(const string& string1, const string& string2) {
	string stringA = string1;
	string stringB = string2;
	transform(stringA.begin(), stringA.end(), stringA.begin(), (int(*)(int))toupper);
	transform(stringB.begin(), stringB.end(), stringB.begin(), (int(*)(int))toupper);
	return stringA == stringB;
}

const string StringUtils::trim(const string& src) {
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

const string StringUtils::toLowerCase(const string& src) {
	string result = src;
	transform(result.begin(), result.end(), result.begin(), (int(*)(int))tolower);
	return result;
}

const string StringUtils::toUpperCase(const string& src) {
	string result = src;
	transform(result.begin(), result.end(), result.begin(), (int(*)(int))toupper);
	return result;
}

bool StringUtils::matches(const string& src, const string& pattern) {
	return regex_match(src, regex(pattern));
}

const string StringUtils::replaceAll(const string& src, const string& pattern, const string& by) {
	return regex_replace(src, regex(pattern), by);
}

#include <tdme/utils/StringUtils.h>

#include <algorithm>
#include <functional>
#include <regex>
#include <string>

using std::find_if;
using std::isspace;
using std::not1;
using std::ptr_fun;
using std::replace;
using std::regex_match;
using std::regex_replace;
using std::string;
using std::transform;
using std::tolower;
using std::toupper;
using std::wstring;
using std::wregex;


using tdme::utils::StringUtils;

const bool StringUtils::startsWith(const wstring& src, const wstring& prefix) {
    return src.find(prefix) == 0;
}

const bool StringUtils::endsWith(const wstring& src, const wstring& suffix) {
	return
		src.size() >= suffix.size() &&
		src.compare(src.size() - suffix.size(), suffix.size(), suffix) == 0;
}

const wstring StringUtils::replace(const wstring& string, const wchar_t& what, const wchar_t& by) {
	wstring result = string;
	std::replace(result.begin(), result.end(), what, by);
	return result;
}

const wstring StringUtils::replace(const wstring& string, const wstring& what, const wstring& by) {
	wstring result = string;
	if (what.empty()) return result;
	size_t start_pos = 0;
	while ((start_pos = result.find(what, start_pos)) != std::string::npos) {
		result.replace(start_pos, what.length(), by);
		start_pos += by.length();
	}
	return result;
}

int32_t StringUtils::lastIndexOf(const wstring& string, wchar_t what) {
	return string.find_last_of(what);
}

const wstring StringUtils::substring(const wstring& string, int32_t beginIndex) {
	return string.substr(beginIndex);
}

const wstring StringUtils::substring(const wstring& string, int32_t beginIndex, int32_t endIndex) {
	return string.substr(beginIndex, endIndex - beginIndex);
}

bool StringUtils::equalsIgnoreCase(const wstring& string1, const wstring& string2) {
	wstring stringA = string1;
	wstring stringB = string2;
	transform(stringA.begin(), stringA.end(), stringA.begin(), (int(*)(int))toupper);
	transform(stringB.begin(), stringB.end(), stringB.begin(), (int(*)(int))toupper);
	return stringA == stringB;
}

const wstring StringUtils::trim(const wstring& string) {
	wstring result = string;
	result.erase(
		result.begin(),
		find_if(result.begin(), result.end(), not1(std::ptr_fun<int, int>(std::isspace)))
	);
	result.erase(
		find_if(result.rbegin(), result.rend(), not1(std::ptr_fun<int, int>(std::isspace))).base(),
		result.end()
	);
	return result;
}

const wstring StringUtils::toLowerCase(const wstring& string) {
	wstring result = string;
	transform(result.begin(), result.end(), result.begin(), (int(*)(int))tolower);
	return result;
}

const wstring StringUtils::toUpperCase(const wstring& string) {
	wstring result = string;
	transform(result.begin(), result.end(), result.begin(), (int(*)(int))toupper);
	return result;
}

bool StringUtils::matches(const wstring& string, const wstring& pattern) {
	return regex_match(string, wregex(pattern));
}

const wstring StringUtils::replaceAll(const wstring& string, const wstring& pattern, const wstring& by) {
	return regex_replace(string, wregex(pattern), by);
}

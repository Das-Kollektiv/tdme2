#pragma once

#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::smatch;
using std::string;
using std::string_view;
using std::vector;

/**
 * String tools class
 * @author Andreas Drewke
 */
class tdme::utilities::StringTools final
{
public:
	/**
	 * Checks if string starts with prefix
	 * @param str string
     * @param prefix prefix string
	 * @returns if string starts with prefix
	 */
	inline static const bool startsWith(const string& str, const string& prefix) {
		return str.find(prefix) == 0;
	}

	/**
	 * Checks if string starts with prefix
	 * @param str string
     * @param prefix prefix string
	 * @returns if string starts with prefix
	 */
	inline static const bool viewStartsWith(const string_view& str, const string_view& prefix) {
		return str.find(prefix) == 0;
	}

	/**
	 * Checks if string ends with suffix
	 * @param str string
     * @param suffix suffix string
	 * @returns if string ends with suffix
	 */
	inline static const bool endsWith(const string& str, const string& suffix) {
		return
			str.size() >= suffix.size() &&
			str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	/**
	 * Checks if string ends with suffix
	 * @param str string
     * @param suffix suffix string
	 * @returns if string ends with suffix
	 */
	inline static const bool viewEndsWith(const string_view& str, const string_view& suffix) {
		return
			str.size() >= suffix.size() &&
			str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	/**
	 * Replace char with another char
	 * @param str string
	 * @param what what to replace
	 * @param by to replace by
	 * @param beginIndex index to begin with
	 * @returns replace result
	 */
	static const string replace(const string& str, const char what, const char by, int64_t beginIndex = 0);

	/**
	 * Replace string with another string
	 * @param str string
	 * @param what what to replace
	 * @param by to replace by
	 * @param beginIndex index to begin with
	 * @returns replace result
	 */
	static const string replace(const string& str, const string& what, const string& by, int64_t beginIndex = 0);

	/**
	 * Finds first index of given character
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @returns index or string::npos if not found
	 */
	inline static int64_t indexOf(const string& str, char what, int64_t beginIndex = 0) {
		return str.find(what, beginIndex);
	}

	/**
	 * Finds first index of given string
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @returns index or string::npos if not found
	 */
	inline static int64_t indexOf(const string& str, const string& what, int64_t beginIndex = 0) {
		return str.find(what, beginIndex);
	}

	/**
	 * Finds first index of given character
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @returns index or string::npos if not found
	 */
	inline static int64_t firstIndexOf(const string& str, char what, int64_t beginIndex = 0) {
		return indexOf(str, what, beginIndex);
	}

	/**
	 * Finds first index of given string
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @returns index or string::npos if not found
	 */
	inline static int64_t firstIndexOf(const string& str, const string& what, int64_t beginIndex = 0) {
		return indexOf(str, what, beginIndex);
	}

	/**
	 * Finds last index of given character
	 * @param str string
	 * @param what what
	 * @param endIndex end index or string::npos
	 * @returns index or string::npos if not found
	 */
	inline static int64_t lastIndexOf(const string& str, const char what, int64_t endIndex = string::npos) {
		return str.rfind(what, endIndex);
	}

	/**
	 * Finds last index of given string
	 * @param str string
	 * @param what what
	 * @param endIndex end index or string::npos
	 * @returns index or string::npos if not found
	 */
	inline static int64_t lastIndexOf(const string& str, const string& what, int64_t endIndex = string::npos) {
		return str.rfind(what, endIndex);
	}

	/**
	 * Finds first index of character provided within given string
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @returns index or string::npos if not found
	 */
	inline static int64_t firstIndexOfChar(const string& str, char what, int64_t beginIndex = 0) {
		return str.find_first_of(what, beginIndex);
	}

	/**
	 * Finds first index of characters provided within given string
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @returns index or string::npos if not found
	 */
	inline static int64_t firstIndexOfChars(const string& str, const string& what, int64_t beginIndex = 0) {
		return str.find_first_of(what, beginIndex);
	}

	/**
	 * Finds last index of character provided within given string
	 * @param str string
	 * @param what what
	 * @param endIndex end index or string::npos
	 * @returns index or string::npos if not found
	 */
	inline static int64_t lastIndexOfChar(const string& str, char what, int64_t endIndex = string::npos) {
		return str.find_last_of(what, endIndex);
	}

	/**
	 * Finds last index of characters provided within given string
	 * @param str string
	 * @param what what
	 * @param endIndex end index or string::npos
	 * @returns index or string::npos if not found
	 */
	inline static int64_t lastIndexOfChars(const string& str, const string& what, int64_t endIndex = string::npos) {
		return str.find_last_of(what, endIndex);
	}

	/**
	 * Returns substring of given string from begin index
	 * @param str string
	 * @param beginIndex begin index
	 * @returns substring result
	 */
	inline static const string substring(const string& str, int64_t beginIndex) {
		return str.substr(beginIndex);
	}

	/**
	 * Returns substring of given string from begin index
	 * @param str string
	 * @param beginIndex begin index
	 * @returns substring result
	 */
	inline static const string_view viewSubstring(const string_view& str, int64_t beginIndex) {
		return str.substr(beginIndex);
	}

	/**
	 * Returns substring of given string from begin index to end index
	 * @param str string
	 * @param beginIndex begin index
	 * @param endIndex end index
	 * @returns substring result
	 */
	inline static const string substring(const string& str, int64_t beginIndex, int64_t endIndex) {
		return str.substr(beginIndex, endIndex - beginIndex);
	}

	/**
	 * Returns substring of given string from begin index to end index
	 * @param str string
	 * @param beginIndex begin index
	 * @param endIndex end index
	 * @returns substring result
	 */
	inline static const string_view viewSubstring(const string_view& str, int64_t beginIndex, int64_t endIndex) {
		return str.substr(beginIndex, endIndex - beginIndex);
	}

	/**
	 * Checks if strings equal ignoring case
	 * @param string1 string 1
	 * @param string2 string 2
	 * @returns equality
	 */
	static bool equalsIgnoreCase(const string& string1, const string& string2);

	/**
	 * Trim string
	 * @param str string
	 * @returns trimmed string
	 */
	static const string trim(const string& str);

	/**
	 * Trim string
	 * @param str string
	 * @returns trimmed string
	 */
	static const string_view viewTrim(const string_view& str);

	/**
	 * Transform string to lower case
	 * @param str string
	 * @returns lowercase string
	 */
	static const string toLowerCase(const string& str);

	/**
	 * Transform string to upper case
	 * @param str string
	 * @returns uppercase string
	 */
	static const string toUpperCase(const string& str);

	/**
	 * Check if pattern matches whole string
	 * @param str string
	 * @param pattern pattern
	 * @param matches matches
	 * @returns if pattern matches whole string
	 */
	static bool regexMatch(const string& str, const string& pattern, smatch* matches = nullptr);

	/**
	 * Do regex pattern search
	 * @param str string
	 * @param pattern pattern
	 * @param matches matches
	 * @returns if search was successful
	 */
	static bool regexSearch(const string& str, const string& pattern, smatch* matches = nullptr);

	/**
	 * Replace regex pattern with given string
	 * @param str string
	 * @param pattern pattern
	 * @param by replace string
	 * @returns replace result
	 */
	static const string regexReplace(const string& str, const string& pattern, const string& by);

	/**
	 * Tokenize
	 * @param str string
	 * @param delimiters delimiters
	 * @param emptyTokens include empty tokens
	 * @returns tokens
	 */
	static const vector<string> tokenize(const string& str, const string& delimiters, bool emptyTokens = false);

	/**
	 * Pad a string left
	 * @param str string
	 * @param by by
	 * @param toSize to size
	 * @returns padded string
	 */
	inline static const string padLeft(const string& str, const string& by, int64_t toSize) {
		auto result = str;
		while (result.size() < toSize) result = by + result;
		return result;
	}

	/**
	 * Pad a string right
	 * @param str string
	 * @param by by
	 * @param toSize to size
	 * @returns padded string
	 */
	inline static const string padRight(const string& str, const string& by, int64_t toSize) {
		auto result = str;
		while (result.size() < toSize) result = result + by;
		return result;
	}

	/**
	 * Indent a string
	 * @param str string
	 * @param with with
	 * @param count count
	 * @returns resulting string
	 */
	inline static const string indent(const string& str, const string& with, int64_t count) {
		string indentString;
		for (auto i = 0; i < count; i++) indentString+= with;
		return indentString + str;
	}

	/**
	 * Generate a string
	 * @param what what
	 * @param count count
	 * @returns resulting string
	 */
	inline static const string generate(const string& what, int64_t count = 1) {
		string result;
		for (auto i = 0; i < count; i++) result+= what;
		return result;
	}

	/**
	 * Get UTF8 string length
	 * @param str string
	 * @returns UTF8 string length
	 */
	static int64_t getUTF8Length(const string& str);

	/**
	 * Get UTF8 character at given index
	 * @param str string
	 * @param index index
	 * @param cache UTF8 position cache
	 */
	static const string getUTF8CharAt(const string& str, int64_t index);

	/**
	 * Get UTF8 binary buffer index
	 * @param str string
	 * @param charIdx character index
	 * @returns UTF binary buffer position from given character/code point index
	 */
	static int64_t getUTF8BinaryIndex(const string& str, int64_t charIdx);

};


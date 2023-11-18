#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/UTF8CharacterIterator.h>

using std::string;
using std::string_view;
using std::vector;

using tdme::utilities::UTF8CharacterIterator;

/**
 * String tools class
 * @author Andreas Drewke
 */
class tdme::utilities::StringTools final
{
public:
	/**
	 * Checks if string starts with prefix
	 * @param src source string
     * @param prefix prefix string
	 * @return bool
	 */
	inline static const bool startsWith(const string& src, const string& prefix) {
		return src.find(prefix) == 0;
	}

	/**
	 * Checks if string starts with prefix
	 * @param src source string
     * @param prefix prefix string
	 * @return bool
	 */
	inline static const bool viewStartsWith(const string_view& src, const string& prefix) {
		return src.find(prefix) == 0;
	}

	/**
	 * Checks if string ends with suffix
	 * @param src source string
     * @param suffix suffix string
	 * @return bool
	 */
	inline static const bool endsWith(const string& src, const string& suffix) {
		return
			src.size() >= suffix.size() &&
			src.compare(src.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	/**
	 * Checks if string ends with suffix
	 * @param src source string
     * @param suffix suffix string
	 * @return bool
	 */
	inline static const bool viewEndsWith(const string_view& src, const string& suffix) {
		return
			src.size() >= suffix.size() &&
			src.compare(src.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	/**
	 * Replace char with another char
	 * @param src source string to be processed
	 * @param what what to replace
	 * @param by to replace by
	 * @param beginIndex index to begin with
	 * @return new string
	 */
	static const string replace(const string& src, const char what, const char by, int beginIndex = 0);

	/**
	 * Replace string with another string
	 * @param src source string to be processed
	 * @param what what to replace
	 * @param by to replace by
	 * @param beginIndex index to begin with
	 * @return new string
	 */
	static const string replace(const string& src, const string& what, const string& by, int beginIndex = 0);

	/**
	 * Finds index of given character
	 * @param src source string
	 * @param what what
	 * @param beginIndex index to begin with
	 * @return index or -1 if not found
	 */
	inline static int32_t indexOf(const string& src, char what, int beginIndex = 0) {
		return src.find(what, beginIndex);
	}

	/**
	 * Finds first index of given string
	 * @param src source string
	 * @param what what
	 * @param beginIndex index to begin with
	 * @return index or -1 if not found
	 */
	inline static int32_t indexOf(const string& src, const string& what, int beginIndex = 0) {
		return src.find(what, beginIndex);
	}

	/**
	 * Finds first index of given character
	 * @param src source string
	 * @param what what
	 * @param beginIndex index to begin with
	 * @return index or -1 if not found
	 */
	inline static int32_t firstIndexOf(const string& src, char what, int beginIndex = 0) {
		return src.find_first_of(what, beginIndex);
	}

	/**
	 * Finds first index of characters provided within given string
	 * @param src source string
	 * @param what what
	 * @param beginIndex index to begin with
	 * @return index or -1 if not found
	 */
	inline static int32_t firstIndexOf(const string& src, const string& what, int beginIndex = 0) {
		return src.find_first_of(what, beginIndex);
	}

	/**
	 * Finds last index of given character
	 * @param src source string
	 * @param what what
	 * @param beginIndex index to begin with
	 * @return index or -1 if not found
	 */
	inline static int32_t lastIndexOf(const string& src, char what, int beginIndex = -1) {
		return src.find_last_of(what, beginIndex);
	}

	/**
	 * Finds last index of characters provided within given string
	 * @param src source string
	 * @param what what
	 * @param beginIndex index to begin with
	 * @return index or -1 if not found
	 */
	inline static int32_t lastIndexOf(const string& src, const string& what, int beginIndex = -1) {
		return src.find_last_of(what, beginIndex);
	}

	/**
	 * Returns substring of given string from begin index
	 * @param src source string
	 * @param beginIndex begin index
	 * @return new string
	 */
	inline static const string substring(const string& src, int32_t beginIndex) {
		return src.substr(beginIndex);
	}

	/**
	 * Returns substring of given string from begin index
	 * @param src source string
	 * @param beginIndex begin index
	 * @return new string
	 */
	inline static const string_view viewSubstring(const string_view& src, int32_t beginIndex) {
		return src.substr(beginIndex);
	}

	/**
	 * Returns substring of given string from begin index to end index
	 * @param src source string
	 * @param beginIndex begin index
	 * @param endIndex end index
	 * @return new string
	 */
	inline static const string substring(const string& src, int32_t beginIndex, int32_t endIndex) {
		return src.substr(beginIndex, endIndex - beginIndex);
	}

	/**
	 * Returns substring of given string from begin index to end index
	 * @param src source string
	 * @param beginIndex begin index
	 * @param endIndex end index
	 * @return new string
	 */
	inline static const string_view viewSubstring(const string_view& src, int32_t beginIndex, int32_t endIndex) {
		return src.substr(beginIndex, endIndex - beginIndex);
	}

	/**
	 * Checks if string equals ignoring case
	 * @param string1 string 1
	 * @param string2 string 2
	 * @return equals
	 */
	static bool equalsIgnoreCase(const string& string1, const string& string2);

	/**
	 * Trim string
	 * @param src source string
	 * @return trimmed string
	 */
	static const string trim(const string& src);

	/**
	 * Trim string
	 * @param src source string
	 * @return trimmed string
	 */
	static const string_view viewTrim(const string_view& src);

	/**
	 * Transform string to lower case
	 * @param src source string
	 * @return transformed string
	 */
	static const string toLowerCase(const string& src);

	/**
	 * Transform string to upper case
	 * @param src source string
	 * @return transformed string
	 */
	static const string toUpperCase(const string& src);

	/**
	 * Check if pattern matches whole string
	 * @param src source string to test
	 * @param pattern pattern
	 * @return if pattern matches whole string
	 */
	static bool regexMatch(const string& src, const string& pattern);

	/**
	 * Do regex pattern search
	 * @param src source string to test
	 * @param pattern pattern
	 * @return if search was successful
	 */
	static bool regexSearch(const string& src, const string& pattern);

	/**
	 * Replace regex pattern with given string
	 * @param src source string to operate on
	 * @param pattern pattern to search
	 * @param by string that will replace pattern occurrances
	 */
	static const string regexReplace(const string& src, const string& pattern, const string& by);

	/**
	 * Tokenize
	 * @param str string to tokenize
	 * @param delimiters delimiters
	 * @param emptyToken include empty token
	 * @return tokens
	 */
	static const vector<string> tokenize(const string& str, const string& delimiters, bool emptyToken = false);

	/**
	 * Pad a string left
	 * @param src source
	 * @param by by
	 * @param toSize to size
	 */
	inline static const string padLeft(const string& src, const string& by, int toSize) {
		auto result = src;
		while (result.size() < toSize) result = by + result;
		return result;
	}

	/**
	 * Pad a string right
	 * @param src source
	 * @param by by
	 * @param toSize to size
	 */
	inline static const string padRight(const string& src, const string& by, int toSize) {
		auto result = src;
		while (result.size() < toSize) result = result + by;
		return result;
	}

	/**
	 * Indent a string
	 * @param src source
	 * @param with with
	 * @param count count
	 */
	inline static const string indent(const string& src, const string& with, int count) {
		string indentString;
		for (auto i = 0; i < count; i++) indentString+= with;
		return indentString + src;
	}

	/**
	 * Get Utf8 string length
	 * @param str string
	 * @return utf8 string length
	 */
	inline static int getUtf8Length(const string& str) {
		UTF8CharacterIterator u8It(str);
		while (u8It.hasNext() == true) u8It.next();
		return u8It.getCharacterPosition();
	}

	/**
	 * Get Utf8 binary buffer index
	 * @param str string
	 * @param charIdx character index
	 * @return UTF binary buffer position from given character/code point index
	 */
	inline static int getUtf8BinaryIndex(const string& str, int charIdx) {
		UTF8CharacterIterator u8It(str);
		u8It.seekCharacterPosition(charIdx);
		return u8It.getBinaryPosition();
	}

};


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

/**
 * UTF8 String tools class
 * @author Andreas Drewke
 */
class tdme::utilities::UTF8StringTools final
{
public:
	/**
	 * Checks if string starts with prefix
	 * @param str string
	 * @param prefix prefix string
	 * @return if string starts with prefix
	 */
	inline static const bool startsWith(const string& str, const string& prefix) {
		return str.find(prefix) == 0;
	}

	/**
	 * Checks if string starts with prefix
	 * @param str string
	 * @param prefix prefix string
	 * @return if string starts with prefix
	 */
	inline static const bool viewStartsWith(const string_view& str, const string& prefix) {
		return str.find(prefix) == 0;
	}

	/**
	 * Checks if string ends with suffix
	 * @param str string
	 * @param suffix suffix string
	 * @return if string ends with suffix
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
	 * @return if string ends with suffix
	 */
	inline static const bool viewEndsWith(const string_view& str, const string& suffix) {
		return
			str.size() >= suffix.size() &&
			str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
	}

	/**
	 * Replace string with another string
	 * @param str string
	 * @param what what to replace
	 * @param by to replace by
	 * @param beginIndex index to begin with
	 * @param cache str UTF8 position cache
	 * @return replace result
	 */
	static const string replace(
		const string& str,
		const string& what,
		const string& by,
		int64_t beginIndex = 0,
		::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr
	);

	/**
	 * Finds first index of given string
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @param cache str UTF8 position cache
	 * @return index or string::npos if not found
	 */
	inline static int64_t indexOf(
		const string& str,
		const string& what,
		int64_t beginIndex = 0,
		::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr
	) {
		return firstIndexOf(str, what, beginIndex, cache);
	}

	/**
	 * Finds first index of given string
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @param cache str UTF8 position cache
	 * @return index or string::npos if not found
	 */
	static int64_t firstIndexOf(
		const string& str,
		const string& what,
		int64_t beginIndex = 0,
		::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr
	);

	/**
	 * Finds last index of given string
	 * @param str string
	 * @param what what
	 * @param endIndex end index or string::npos
	 * @param cache str UTF8 position cache
	 * @return index or string::npos if not found
	 */
	static int64_t lastIndexOf(
		const string& str,
		const string& what,
		int64_t endIndex = string::npos,
		::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr
	);

	/**
	 * Finds first index of characters provided within given string
	 * @param str string
	 * @param what what
	 * @param beginIndex begin index
	 * @param srcCache str UTF8 position cache
	 * @param whatCache what UTF8 position cache
	 * @return index or string::npos if not found
	 */
	static int64_t firstIndexOfChars(const string& str, const string& what, int64_t beginIndex = 0, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* srcCache = nullptr, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* whatCache = nullptr);

	/**
	 * Finds last index of characters provided within given string
	 * @param str string
	 * @param what what
	 * @param endIndex end index or string::npos
	 * @param srcCache str UTF8 position cache
	 * @param whatCache what UTF8 position cache
	 * @return index or string::npos if not found
	 */
	static int64_t lastIndexOfChars(const string& str, const string& what, int64_t endIndex = string::npos, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* srcCache = nullptr, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* whatCache = nullptr);

	/**
	 * Returns substring of given string from begin index to end index
	 * @param str string
	 * @param beginIndex begin index
	 * @param endIndex end index or string::npos
	 * @param cache str UTF8 position cache
	 * @return substring result
	 */
	inline static const string substring(const string& str, int64_t beginIndex, int64_t endIndex = string::npos, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* srcCache = nullptr, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr) {
		auto result = viewSubstring(string_view(str), beginIndex, endIndex, cache);
		return string(result.data(), result.size());
	}

	/**
	 * Returns substring of given string from begin index to end index
	 * @param str string
	 * @param beginIndex begin index
	 * @param endIndex end index or string::npos
	 * @param cache str UTF8 position cache
	 * @return substring result
	 */
	static const string_view viewSubstring(const string_view& str, int64_t beginIndex, int64_t endIndex, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Checks if strings equal ignoring case
	 * @param string1 string 1
	 * @param string2 string 2
	 * @param string1Cache string1 UTF8 position cache
	 * @param string2Cache string2 UTF8 position cache
	 * @return equality
	 */
	static bool equalsIgnoreCase(
		const string& string1,
		const string& string2,
		::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* string1Cache = nullptr,
		::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* string2Cache = nullptr
	);

	/**
	 * Trim string
	 * @param str string
	 * @param cache UTF8 position cache
	 * @return trimmed string
	 */
	static const string trim(const string& str, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Trim string
	 * @param str string
	 * @param cache UTF8 position cache
	 * @return trimmed string
	 */
	static const string_view viewTrim(const string_view& str, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Transform string to lower case
	 * @param str string
	 * @param cache UTF8 position cache
	 * @return lowercase string
	 */
	static const string toLowerCase(const string& str, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Transform string to upper case
	 * @param str string
	 * @param cache UTF8 position cache
	 * @return uppercase string
	 */
	static const string toUpperCase(const string& str, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Check if pattern matches whole string
	 * @param str string
	 * @param pattern pattern
	 * @return if pattern matches whole string
	 */
	static bool regexMatch(const string& str, const string& pattern);

	/**
	 * Do regex pattern search
	 * @param str string
	 * @param pattern pattern
	 * @return if search was successful
	 */
	static bool regexSearch(const string& str, const string& pattern);

	/**
	 * Replace regex pattern with given string
	 * @param str string
	 * @param pattern pattern
	 * @param by replace string
	 * @return replace result
	 */
	static const string regexReplace(const string& str, const string& pattern, const string& by);

	/**
	 * Tokenize
	 * @param str string
	 * @param delimiters delimiters
	 * @param emptyTokens include empty tokens
	 * @return tokens
	 */
	static const vector<string> tokenize(const string& str, const string& delimiters, bool emptyTokens = false);

	/**
	 * Pad a string left
	 * @param str string
	 * @param by by
	 * @param toLength to length
	 * @param cache str UTF8 position cache
	 * @return padded string
	 */
	static const string padLeft(const string& str, const string& by, int64_t toLength, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Pad a string right
	 * @param str string
	 * @param by by
	 * @param toLength to length
	 * @param cache str UTF8 position cache
	 * @return padded string
	 */
	static const string padRight(const string& str, const string& by, int64_t toLength, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Indent a string
	 * @param str string
	 * @param with with
	 * @param count count
	 * @return resulting string
	 */
	inline static const string indent(const string& str, const string& with, int64_t count) {
		string result;
		for (auto i = 0; i < count; i++) result+= with;
		return result + str;
	}

	/**
	 * Generate a string
	 * @param what what
	 * @param count count
	 * @return resulting string
	 */
	inline static const string generate(const string& what, int64_t count = 1) {
		string result;
		for (auto i = 0; i < count; i++) result+= what;
		return result;
	}

	/**
	 * Get UTF8 string length
	 * @param str string
	 * @param cache UTF8 position cache
	 * @return UTF8 string length
	 */
	static int64_t getLength(const string& str, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Get UTF8 character at given index
	 * @param str string
	 * @param index index
	 * @param cache UTF8 position cache
	 */
	static const string getCharAt(const string& str, int64_t index, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

	/**
	 * Get UTF8 binary buffer index
	 * @param str string
	 * @param charIdx character index
	 * @param cache UTF8 position cache
	 * @return UTF binary buffer position from given character/code point index
	 */
	static int64_t getUTF8BinaryIndex(const string& str, int64_t charIdx, ::tdme::utilities::UTF8CharacterIterator::UTF8PositionCache* cache = nullptr);

};


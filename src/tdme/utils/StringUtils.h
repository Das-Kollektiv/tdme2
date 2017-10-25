#pragma once

#include <string>

#include <tdme/utils/fwd-tdme.h>

using std::string;

/** 
 * String utilities
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::StringUtils final
{
public:

	/**
	 * Checks if string starts with prefix
	 * @param source string
     * @param prefix string
	 * @return bool
	 */
	static const bool startsWith(const string& src, const string& prefix);

	/**
	 * Checks if string ends with suffix
	 * @param source string
     * @param suffix string
	 * @return bool
	 */
	static const bool endsWith(const string& src, const string& suffix);

	/**
	 * Replace char with another char
	 * @param source string to be processed
	 * @param what to replace
	 * @param to replace by
	 * @return new string
	 */
	static const string replace(const string& src, const char what, const char by);

	/**
	 * Replace string with another string
	 * @param source string to be processed
	 * @param what to replace
	 * @param to replace by
	 * @return new string
	 */
	static const string replace(const string& src, const string& what, const string& by);

	/**
	 * Finds last index of given character
	 * @param source string
	 * @param what
	 * @return index or -1 if not found
	 */
	static int32_t lastIndexOf(const string& src, char what);

	/**
	 * Returns substring of given string from begin index
	 * @param source string
	 * @param begin index
	 * @return new string
	 */
	static const string substring(const string& src, int32_t beginIndex);

	/**
	 * Returns substring of given string from begin index to end index
	 * @param source string
	 * @param begin index
	 * @param end index
	 * @return new string
	 */
	static const string substring(const string& src, int32_t beginIndex, int32_t endIndex);

	/**
	 * Checks if string equals ignoring case
	 * @param string 1
	 * @param string 2
	 * @return equals
	 */
	static bool equalsIgnoreCase(const string& string1, const string& string2);

	/**
	 * Trim string
	 * @param source string
	 * @return trimmed string
	 */
	static const string trim(const string& src);

	/**
	 * Transform string to lower case
	 * @param source string
	 * @return transformed string
	 */
	static const string toLowerCase(const string& src);

	/**
	 * Transform string to upper case
	 * @param source string
	 * @return transformed string
	 */
	static const string toUpperCase(const string& src);

	/**
	 * Do regex pattern matching
	 * @param source string to test
	 * @param pattern
	 * @return if patter matches
	 */
	static bool matches(const string& src, const string& pattern);

	/**
	 * Replace regex pattern with given string
	 * @param source string to operate on
	 * @param pattern to search
	 * @param string that will replace pattern occurrances
	 */
	static const string replaceAll(const string& src, const string& pattern, const string& by);

};


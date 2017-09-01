#pragma once

#include <string>

#include <tdme/utils/fwd-tdme.h>

using std::string;
using std::wstring;

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
	static const bool startsWith(const wstring& src, const wstring& prefix);

	/**
	 * Checks if string ends with suffix
	 * @param source string
     * @param suffix string
	 * @return bool
	 */
	static const bool endsWith(const wstring& src, const wstring& suffix);

	/**
	 * Replace char with another char
	 * @param string to be processed
	 * @param what to replace
	 * @param to replace by
	 * @return new string
	 */
	static const wstring replace(const wstring& string, const wchar_t& what, const wchar_t& by);

	/**
	 * Replace string with another string
	 * @param string to be processed
	 * @param what to replace
	 * @param to replace by
	 * @return new string
	 */
	static const wstring replace(const wstring& string, const wstring& what, const wstring& by);

	/**
	 * Finds last index of given character
	 * @param string
	 * @param what
	 * @return index or -1 if not found
	 */
	static int32_t lastIndexOf(const wstring& string, wchar_t what);

	/**
	 * Returns substring of given string from begin index
	 * @param string
	 * @param begin index
	 * @return new string
	 */
	static const wstring substring(const wstring& string, int32_t beginIndex);

	/**
	 * Returns substring of given string from begin index to end index
	 * @param string
	 * @param begin index
	 * @param end index
	 * @return new string
	 */
	static const wstring substring(const wstring& string, int32_t beginIndex, int32_t endIndex);

	/**
	 * Checks if string equals ignoring case
	 * @param string 1
	 * @param string 2
	 * @return equals
	 */
	static bool equalsIgnoreCase(const wstring& string1, const wstring& string2);

	/**
	 * Trim string
	 * @param string
	 * @return trimmed string
	 */
	static wstring trim(const wstring& string);

	/**
	 * Transform string to lower case
	 * @param string
	 * @return transformed string
	 */
	static wstring toLowerCase(const wstring& string);

	/**
	 * Transform string to upper case
	 * @param string
	 * @return transformed string
	 */
	static wstring toUpperCase(const wstring& string);

};


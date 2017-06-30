#pragma once

#include <string>

using std::string;
using std::wstring;

namespace tdme {
namespace utils {

/** 
 * String converter
 * @author Andreas Drewke
 * @version $Id$
 */
class StringConverter final
{
public:

	/**
	 * Convert wide string to string
	 * @param wstring
	 * @return string
	 */
	static const string toString(const wstring& string);

	/**
	 * Convert string to wide string
	 * @param string
	 * @return wstring
	 */
	static const wstring toWideString(const string& string);

};

};
};

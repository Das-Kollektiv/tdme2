#pragma once

#include <string>

#include <tdme/utils/fwd-tdme.h>

using std::string;
using std::wstring;

using tdme::utils::StringConverter;

/** 
 * String converter
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::StringConverter final
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


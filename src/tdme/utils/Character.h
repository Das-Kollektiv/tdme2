// Generated from /tdme/src/tdme/utils/Key.java

#pragma once

#include <tdme/utils/fwd-tdme.h>

/**
 * Character
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::Character final
{
public:

	/**
	 * Convert character to lower case character
	 * @param character
	 * @return lower case character
	 */
	static wchar_t toLowerCase(wchar_t character);

	/**
	 * Convert character to upper case character
	 * @param character
	 * @return upper case character
	 */
	static wchar_t toUpperCase(wchar_t character);

};

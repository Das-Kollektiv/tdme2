#pragma once

#include <cctype>
#include <cwctype>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

/**
 * Character class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utilities::Character final
{
public:

	/**
	 * Convert character to lower case character
	 * @param character character
	 * @return lower case character
	 */
	inline static char toLowerCase(char character) {
		return tolower(character);
	}

	/**
	 * Convert character to upper case character
	 * @param character character
	 * @return upper case character
	 */
	inline static char toUpperCase(char character) {
		return toupper(character);
	}

	/**
	 * Returns if character is alpha numeric
	 * @return if character is alpha numeric
	 */
	inline static bool isAlphaNumeric(char character) {
		return isalnum(character) != 0;
	}

	/**
	 * Returns if character is a white space
	 * @return if character is a white space
	 */
	inline static bool isSpace(char character) {
		return isspace(character) != 0;
	}

};

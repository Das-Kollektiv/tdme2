#pragma once

#include <cctype>
#include <cwctype>

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::string;

/**
 * Character class
 * @author Andreas Drewke
 */
class tdme::utilities::Character final
{
public:

	/**
	 * Convert character to lower case character
	 * @param character character
	 * @return lower case character
	 */
	inline static char toLowerCase(uint32_t character) {
		return tolower(character);
	}

	/**
	 * Convert character to upper case character
	 * @param character character
	 * @return upper case character
	 */
	inline static char toUpperCase(uint32_t character) {
		return toupper(character);
	}

	/**
	 * Returns if character is alpha numeric
	 * @return if character is alpha numeric
	 */
	inline static bool isAlphaNumeric(uint32_t character) {
		return isalnum(character) != 0;
	}

	/**
	 * Returns if character is a white space
	 * @return if character is a white space
	 */
	inline static bool isSpace(uint32_t character) {
		return isspace(character) != 0;
	}

	/**
	 * Generates a string from code point
	 */
	inline static const string toString(uint32_t codePoint) {
		// see: http://www.zedwood.com/article/cpp-utf8-char-to-codepoint
		char c[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };
		if (codePoint <= 0x7F) {
			c[0] = codePoint;
		} else if (codePoint <= 0x7FF) {
			c[0] = (codePoint >> 6) + 192;
			c[1] = (codePoint & 63) + 128;
		} else if (0xd800 <= codePoint && codePoint <= 0xdfff) {
		} //invalid block of utf8
		else if (codePoint <= 0xFFFF) {
			c[0] = (codePoint >> 12) + 224;
			c[1] = ((codePoint >> 6) & 63) + 128;
			c[2] = (codePoint & 63) + 128;
		} else if (codePoint <= 0x10FFFF) {
			c[0] = (codePoint >> 18) + 240;
			c[1] = ((codePoint >> 12) & 63) + 128;
			c[2] = ((codePoint >> 6) & 63) + 128;
			c[3] = (codePoint & 63) + 128;
		}
		return string(c);
	}

};

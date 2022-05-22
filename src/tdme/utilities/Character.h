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
	 * Generates a string from given character / code point
	 * @param character character
	 * @return string representation of given character
	 */
	inline static const string toString(uint32_t character) {
		// see: http://www.zedwood.com/article/cpp-utf8-char-to-codepoint
		char u8Bytes[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };
		if (character <= 0x7F) {
			u8Bytes[0] = character;
		} else if (character <= 0x7FF) {
			u8Bytes[0] = (character >> 6) + 192;
			u8Bytes[1] = (character & 63) + 128;
		} else if (0xd800 <= character && character <= 0xdfff) {
		} //invalid block of utf8
		else if (character <= 0xFFFF) {
			u8Bytes[0] = (character >> 12) + 224;
			u8Bytes[1] = ((character >> 6) & 63) + 128;
			u8Bytes[2] = (character & 63) + 128;
		} else if (character <= 0x10FFFF) {
			u8Bytes[0] = (character >> 18) + 240;
			u8Bytes[1] = ((character >> 12) & 63) + 128;
			u8Bytes[2] = ((character >> 6) & 63) + 128;
			u8Bytes[3] = (character & 63) + 128;
		}
		return string(u8Bytes);
	}

};

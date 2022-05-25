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
		string string;
		appendToString(string, character);
		return string;
	}

	/**
	 * Generates a string from given character / code point
	 * @param string string
	 * @param character character
	 * @return string representation of given character
	 */
	inline static void appendToString(string& string, uint32_t character) {
		// see: http://www.zedwood.com/article/cpp-utf8-char-to-codepoint
		if (character <= 0x7F) {
			string+= character;
		} else if (character <= 0x7FF) {
			string+= (character >> 6) + 192;
			string+= (character & 63) + 128;
		} else if (0xd800 <= character && character <= 0xdfff) {
		} //invalid block of utf8
		else if (character <= 0xFFFF) {
			string+= (character >> 12) + 224;
			string+= ((character >> 6) & 63) + 128;
			string+= (character & 63) + 128;
		} else if (character <= 0x10FFFF) {
			string+= (character >> 18) + 240;
			string+= ((character >> 12) & 63) + 128;
			string+= ((character >> 6) & 63) + 128;
			string+= (character & 63) + 128;
		}
	}

};

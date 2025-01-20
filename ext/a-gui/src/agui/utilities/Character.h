#pragma once

#include <cwctype>

#include <string>

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>

using std::string;

/**
 * Character class
 * @author Andreas Drewke
 */
class agui::utilities::Character final
{
public:

	/**
	 * Convert character to lower case character
	 * @param character character
	 * @returns lower case character
	 */
	inline static uint32_t toLowerCase(uint32_t character) {
		return towlower(character);
	}

	/**
	 * Convert character to upper case character
	 * @param character character
	 * @returns upper case character
	 */
	inline static uint32_t toUpperCase(uint32_t character) {
		return towupper(character);
	}

	/**
	 * Returns if character is alpha numeric
	 * @returns if character is alpha numeric
	 */
	inline static bool isAlphaNumeric(uint32_t character) {
		return iswalnum(character) != 0;
	}

	/**
	 * Returns if character is a white space
	 * @returns if character is a white space
	 */
	inline static bool isSpace(uint32_t character) {
		return iswspace(character) != 0;
	}

	/**
	 * Generates a string from given character / code point
	 * @param character character
	 * @returns string representation of given character
	 */
	inline static const string toString(uint32_t character) {
		string string;
		appendToString(string, character);
		return string;
	}

	/**
	 * Appends a character / code point to given string
	 * @param string string
	 * @param character character
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

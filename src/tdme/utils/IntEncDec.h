#pragma once

#include <stdint.h>

#include <string>

#include <tdme/utils/fwd-tdme.h>

using std::string;

/**
 * Integer to string conversion and vice versa
 * @author Andreas Drewke
 */
class tdme::utils::IntEncDec {
public:
	/**
	 * @brief Encodes an 32 bit unsigned integer to a 6 char string representation
	 * @param int value to encode
	 * @param string
	 */
	static void encodeInt(const uint32_t decodedInt, string& encodedString);

	/**
	 * @brief Decodes an 6 char string representation to a unsigned 32 bit integer
	 * @param encoded string
	 * @param integer
	 */
	static bool decodeInt(const string& encodedInt, uint32_t& decodedInt);
};

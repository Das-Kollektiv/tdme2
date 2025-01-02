#pragma once

#include <stdint.h>

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/fwd-minitscript.h>

using std::string;

/**
 * Integer to hex string conversion utility class
 * @author Andreas Drewke
 */
class minitscript::utilities::Hex {
public:

	/**
	 * @brief Encodes an 64 bit unsigned integer to a hex string representation
	 * @param decodedInt int value to encode
	 * @return encodedString
	 */
	inline static const string encodeInt(const uint64_t decodedInt) {
		string encodedString;
		encodeInt(decodedInt, encodedString);
		return encodedString;
	}

	/**
	 * @brief Decodes a hex string representation to an 64 bit unsigned integer
	 * @param encodedInt string value to decode
	 * @return decodedString
	 */
	inline static uint64_t decodeInt(const string& encodedString) {
		uint64_t decodedInt;
		if (decodeInt(encodedString, decodedInt) == false) return -1LL;
		return decodedInt;
	}

	/**
	 * @brief Encodes an 64 bit unsigned integer to a hex string representation
	 * @param decodedInt int value to encode
	 * @param encodedString string
	 */
	static void encodeInt(const uint64_t decodedInt, string& encodedString);

	/**
	 * @brief Decodes an hex string representation to 64 bit unsigned integer
	 * @param encodedString encoded string
	 * @param decodedInt decoded Int
	 * @return success
	 */
	static bool decodeInt(const string& encodedString, uint64_t& decodedInt);

};

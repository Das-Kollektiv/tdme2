#pragma once

#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/fwd-minitscript.h>

using std::string;
using std::vector;

/**
 * Base64 encoding/decoding class
 * @author Andreas Drewke
 */
class minitscript::utilities::Base64 {
public:
	/**
	 * @brief Encodes an string to base 64 string
	 * @param decodedString string to encode
	 * @return encodedString
	 */
	inline static const string encode(const string& decodedString) {
		string encodedString;
		encode(decodedString, encodedString);
		return encodedString;
	}

	/**
	 * @brief Decodes an base64 encoded string
	 * @param encodedString encoded string
	 * @return decodedString
	 */
	inline static const string decode(const string& encodedString) {
		string decodedString;
		decode(encodedString, decodedString);
		return decodedString;
	}

	/**
	 * Encodes an string to base 64 string
	 * @param decodedString string to encode
	 * @param encodedString encoded string
	 */
	static void encode(const string& decodedString, string& encodedString);

	/**
	 * Encodes uint8_t vector to base 64 string
	 * @param decodedData data to encode
	 * @param encodedString encoded string
	 */
	static void encode(const vector<uint8_t>& decodedData, string& encodedString);

	/**
	 * Decodes an base64 encoded string
	 * @param encodedString encoded string
	 * @param decodedString decoded string
	 */
	static void decode(const string& encodedString, string& decodedString);

	/**
	 * Decodes an base64 encoded string into uint8_t vector
	 * @param encodedString encoded string
	 * @param decodedData decoded data
	 */
	static void decode(const string& encodedString, vector<uint8_t>& decodedData);

};

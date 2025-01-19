#pragma once

#if defined(_WIN32) && defined(_MSC_VER)
	#define NOMINMAX
	#undef max
	#undef min
#endif

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

#include <limits>
#include <string>
#include <string_view>

using std::numeric_limits;
using std::string;
using std::string_view;

/**
 * Integer class
 * @author Andreas Drewke
 */
class tdme::utilities::Integer final
{
public:
	static constexpr int MAX_VALUE { numeric_limits<int>::max() };
	static constexpr int MIN_VALUE { -numeric_limits<int>::max() };

	/**
	 * Check if given string is a integer string
	 * @param str string
	 * @returns given string is integer
	 */
	static bool is(const string& str);

	/**
	 * Check if given string is a integer string
	 * @param str string
	 * @returns given string is integer
	 */
	static bool viewIs(const string_view& str);

	/**
	 * Parse integer
	 * @param str string
	 * @returns integer
	 */
	static int parse(const string& str);

	/**
	 * Parse integer
	 * @param str string
	 * @returns integer
	 */
	static int viewParse(const string_view& str);

	/**
	 * @brief Encodes an 32 bit unsigned integer to a 6 char string representation
	 * @param decodedInt int value to encode
	 * @returns encodedString
	 */
	inline static const string encode(const uint32_t decodedInt) {
		string encodedString;
		encode(decodedInt, encodedString);
		return encodedString;
	}

	/**
	 * @brief Decodes an 6 char string representation to a unsigned 32 bit integer
	 * @param encodedString encoded string
	 * @returns decodedString
	 */
	inline static const uint32_t decode(const string& encodedString) {
		uint32_t decodedInt;
		decode(encodedString, decodedInt);
		return decodedInt;
	}

	/**
	 * @brief Decodes an 6 char string representation to a unsigned 32 bit integer
	 * @param encodedString encoded string
	 * @returns decodedString
	 */
	inline static const uint32_t viewDecode(const string_view& encodedString) {
		uint32_t decodedInt;
		viewDecode(encodedString, decodedInt);
		return decodedInt;
	}

	/**
	 * @brief Encodes an 32 bit unsigned integer to a 6 char string representation
	 * @param decodedInt int value to encode
	 * @param encodedString string
	 */
	static void encode(const uint32_t decodedInt, string& encodedString);

	/**
	 * @brief Decodes an 6 char string representation to a unsigned 32 bit integer
	 * @param encodedString encoded string
	 * @param decodedInt integer
	 */
	static bool decode(const string& encodedString, uint32_t& decodedInt);

	/**
	 * @brief Decodes an 6 char string representation to a unsigned 32 bit integer
	 * @param encodedString encoded string
	 * @param decodedInt integer
	 */
	static bool viewDecode(const string_view& encodedString, uint32_t& decodedInt);

};

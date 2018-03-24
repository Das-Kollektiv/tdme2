
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::string;

/** 
 * Mutable string
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::MutableString final
{
public:

	/**
	 * @return length
	 */
	int32_t length() const;

	/**
	 * Get char at index
	 * @param idx
	 * @return char
	 */
	char charAt(int32_t idx) const;

	/**
	 * Reset
	 */
	MutableString& reset();

	/**
	 * Set character
	 * @param c
	 * @return this mutable string
	 */
	MutableString& set(char c);

	/**
	 * Append character
	 * @param c
	 * @return this mutable string
	 */
	MutableString& append(char c);

	/**
	 * Insert character c at idx
	 * @param c
	 * @return this mutable string
	 */
	MutableString& insert(int32_t idx, char c);

	/**
	 * Set string
	 * @param s
	 * @return this mutable string
	 */
	MutableString& set(const string& s);

	/**
	 * Append string
	 * @param s
	 * @return this mutable string
	 */
	MutableString& append(const string& s);

	/**
	 * Insert string at idx
	 * @param c
	 * @return this mutable string
	 */
	MutableString& insert(int32_t idx, const string& s);

	/**
	 * Set mutable string
	 * @param s
	 * @return this mutable string
	 */
	MutableString& set(const MutableString& s);

	/**
	 * Append mutable string
	 * @param s
	 * @return this mutable string
	 */
	MutableString& append(const MutableString& s);

	/**
	 * Insert mutable string at idx
	 * @param c
	 * @return this mutable string
	 */
	MutableString& insert(int32_t idx, const MutableString& s);

	/**
	 * Set integer
	 * @param i
	 * @return this mutable string
	 */
	MutableString& set(int32_t i);

	/**
	 * Append integer
	 * @see http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
	 * @param i
	 * @return this mutable string
	 */
	MutableString& append(int32_t i);

	/**
	 * Insert integer at idx
	 * @see http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
	 * @param i
	 * @return this mutable string
	 */
	MutableString& insert(int32_t idx, int32_t i);

	/**
	 * Set float
	 * @param f
	 * @param decimals
	 * @return this mutable string
	 */
	MutableString& set(float f, int32_t decimals);

	/**
	 * Append float with given decimals
	 * @see http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
	 * @param f
	 * @param decimals
	 * @return this mutable string
	 */
	MutableString& append(float f, int32_t decimals);

	/**
	 * Insert float at idx
	 * @see http://stackoverflow.com/questions/7123490/how-compiler-is-converting-integer-to-string-and-vice-versa
	 * @param i
	 * @return this mutable string
	 */
	MutableString& insert(int32_t idx, float f, int32_t decimals);

	/**
	 * Delete characters at idx with given length
	 * @param idx
	 * @param length
	 * @return this mutable string
	 */
	MutableString& delete_(int32_t idx, int32_t count);

	/**
	 * Returns the character index where string s have been found or -1 if not found
	 * @param string
	 * @param index
	 * @return index where string has been found or -1
	 */
	int32_t indexOf(const MutableString& s, int32_t idx) const;

	/**
	 * Returns the character index where string s have been found or -1 if not found
	 * @param string
	 * @return index where string has been found or -1
	 */
	int32_t indexOf(const MutableString& s) const;

	/**
	 * Equals
	 * @param string 2
	 * @return string 2 equals this string
	 */
	bool equals(const string& s2) const;

	/**
	 * Equals
	 * @param string 2
	 * @return string 2 equals this string
	 */
	bool equals(const MutableString& s2) const;

	/**
	 * @return string
	 */
	const string& getString() const;

	/**
	 * Public default constructor
	 */
	MutableString();

	/**
	 * Public constructor
	 * @param string
	 */
	MutableString(const string& s);

	/**
	 * Public constructor
	 * @param integer
	 */
	MutableString(int i);

	/**
	 * Public constructor
	 * @param f
	 * @param decimals
	 */
	MutableString(float f, int32_t decimals);

private:
	string data;
};

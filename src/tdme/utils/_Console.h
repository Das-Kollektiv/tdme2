// Generated from /tdme/src/tdme/utils/_Console.java

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <tdme/os/threading/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utils/fwd-tdme.h>

using std::string;
using std::wstring;

/** 
 * Console 
 * @author Andreas Drewke
 * @versio $Id$
 */
class tdme::utils::_Console
{
public:
	/** 
	 * Print given string and trailing newline to console
	 * @param wstring
	 */
	static void println(const wstring& string);

	/** 
	 * Print given string and trailing newline to console
	 * @param string
	 */
	static void println(const string& string);

	/**
	 * Print byte and trailing newline to console
	 * @param value
	 */
	static void println(int8_t value);

	/** 
	 * Print short and trailing newline to console
	 * @param value
	 */
	static void println(int16_t value);

	/** 
	 * Print int and trailing newline to console
	 * @param value
	 */
	static void println(int32_t value);

	/** 
	 * Print long and trailing newline to console
	 * @param value
	 */
	static void println(int64_t value);

	/** 
	 * Print float and trailing newline to console
	 * @param value
	 */
	static void println(float value);

	/** 
	 * Print double and trailing newline to console
	 * @param value
	 */
	static void println(double value);

	/** 
	 * Print boolean and trailing newline to console
	 * @param value
	 */
	static void println(bool value);

	/** 
	 * Print char and trailing newline to console
	 * @param value
	 */
	static void println(char16_t value);

	/** 
	 * Print given string
	 * @param wstring
	 */
	static void print(const wstring& string);

	/**
	 * Print given string
	 * @param string
	 */
	static void print(const string& string);

	/** 
	 * Print byte to console
	 * @param value
	 */
	static void print(int8_t value);

	/** 
	 * Print short to console
	 * @param value
	 */
	static void print(int16_t value);

	/** 
	 * Print int to console
	 * @param value
	 */
	static void print(int32_t value);

	/** 
	 * Print long to console
	 * @param value
	 */
	static void print(int64_t value);

	/** 
	 * Print float to console
	 * @param value
	 */
	static void print(float value);

	/** 
	 * Print double to console
	 * @param value
	 */
	static void print(double value);

	/** 
	 * Print boolean to console
	 * @param value
	 */
	static void print(bool value);

	/** 
	 * Print char to console
	 * @param value
	 */
	static void print(char16_t value);

	/** 
	 * Print new line to console
	 * @param text
	 */
	static void println();

private:
	static Mutex mutex;
};

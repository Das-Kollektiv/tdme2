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
	 * Print new line to console
	 * @param text
	 */
	static void println();

private:
	static Mutex mutex;
};

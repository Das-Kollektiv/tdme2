#pragma once

#include <string_view>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/fwd-miniscript.h>

using std::string_view;

/**
 * Console class
 * @author Andreas Drewke
 * @versio $Id$
 */
class miniscript::utilities::Console
{
public:
	/**
	 * Print given string and trailing newline to console
	 * @param str string
	 */
	static void println(const string_view& str);

	/**
	 * Print given string
	 * @param str string
	 */
	static void print(const string_view& str);

	/**
	 * Print new line to console
	 */
	static void println();

};

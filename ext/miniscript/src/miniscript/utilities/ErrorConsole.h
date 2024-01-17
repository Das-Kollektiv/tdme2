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
class miniscript::utilities::ErrorConsole
{
public:
	/**
	 * Print given string and trailing newline to error console
	 * @param str string
	 */
	static void println(const string_view& str);

	/**
	 * Print given string to error console without trainling new line
	 * @param str string
	 */
	static void print(const string_view& str);

	/**
	 * Print newline to error console
	 */
	static void println();

};

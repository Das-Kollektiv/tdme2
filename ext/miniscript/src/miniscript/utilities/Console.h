#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/fwd-miniscript.h>

using std::string;
using std::string_view;
using std::vector;

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
	 * Print given string without trainling newline to console
	 * @param str string
	 */
	static void print(const string_view& str);

	/**
	 * Print newline to console
	 */
	static void println();

	/**
	 * Read line from console
	 */
	static const string readln();

	/**
	 * Read all input from console into string
	 */
	static const string readAll();

	/**
	 * Read all input from console into string vector
	 */
	static const vector<string> readAllAsArray();

};

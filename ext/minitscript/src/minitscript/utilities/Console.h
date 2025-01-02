#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/fwd-minitscript.h>

using std::unique_ptr;
using std::string;
using std::string_view;
using std::vector;

/**
 * Console class
 * @author Andreas Drewke
 * @versio $Id$
 */
class minitscript::utilities::Console
{
public:
	/**
	 * Console logger
	 */
	struct Logger
	{
		/**
		 * Destructor
		 */
		virtual ~Logger() {}

		/**
		 * Print given string and trailing newline to console
		 * @param str string
		 */
		virtual void printLine(const string_view& str) = 0;

		/**
		 * Print given string without trainling newline to console
		 * @param str string
		 */
		virtual void print(const string_view& str) = 0;

		/**
		 * Print given string and trailing newline to console
		 * @param str string
		 */
		virtual void printLine() = 0;
	};

	/**
	 * Set logger
	 * @param logger logger
	 */
	static void setLogger(Logger* logger);

	/**
	 * Initialize
	 */
	static void initialize();

	/**
	 * Print given string and trailing newline to console
	 * @param str string
	 */
	static void printLine(const string_view& str);

	/**
	 * Print given string without trainling newline to console
	 * @param str string
	 */
	static void print(const string_view& str);

	/**
	 * Print newline to console
	 */
	static void printLine();

	/**
	 * Read line from console
	 */
	static const string readLine();

	/**
	 * Read all input from console into string
	 */
	static const string readAll();

	/**
	 * Read all input from console into string vector
	 */
	static const vector<string> readAllAsArray();

private:
	MINITSCRIPT_STATIC_DLL_IMPEXT static unique_ptr<Logger> logger;
};

#pragma once

#include <memory>
#include <string_view>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/fwd-minitscript.h>

using std::string_view;
using std::unique_ptr;

/**
 * Console class
 * @author Andreas Drewke
 * @versio $Id$
 */
class minitscript::utilities::ErrorConsole
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
	 * Print given string and trailing newline to error console
	 * @param str string
	 */
	static void printLine(const string_view& str);

	/**
	 * Print given string to error console without trainling new line
	 * @param str string
	 */
	static void print(const string_view& str);

	/**
	 * Print newline to error console
	 */
	static void printLine();

private:
	MINITSCRIPT_STATIC_DLL_IMPEXT static unique_ptr<Logger> logger;
};

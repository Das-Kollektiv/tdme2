#pragma once

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>

using std::string;

/**
 * MinitScript script application methods
 * @author Andreas Drewke
 */
class minitscript::minitscript::ApplicationMethods {
public:
	/**
	 * Register constants
	 * @param minitScript minitScript
	 */
	static void registerConstants(MinitScript* minitScript);

	/**
	 * Register methods
	 * @param minitScript minitScript
	 */
	static void registerMethods(MinitScript* minitScript);

	/**
	 * Execute
	 * @param command command
	 * @param exitCode pointer to exit code
	 * @param error pointer to error string
	 */
	static const string execute(const string& command, int* exitCode = nullptr, string* error = nullptr);

};

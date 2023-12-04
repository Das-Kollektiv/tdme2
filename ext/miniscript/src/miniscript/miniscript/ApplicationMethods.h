#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using miniscript::miniscript::MiniScript;

using std::string;

/**
 * MiniScript script application methods
 * @author Andreas Drewke
 */
class miniscript::miniscript::ApplicationMethods {
public:
	/**
	 * Register methods
	 * @param miniScript miniScript
	 */
	static void registerMethods(MiniScript* miniScript);

	/**
	 * Execute
	 * @param command command
	 */
	static const string execute(const string& command);

};

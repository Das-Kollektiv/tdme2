#pragma once

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using miniscript::miniscript::MiniScript;

/**
 * MiniScript script console methods
 * @author Andreas Drewke
 */
class miniscript::miniscript::ConsoleMethods {
public:
	/**
	 * Register constants
	 * @param miniScript miniScript
	 */
	static void registerConstants(MiniScript* miniScript);

	/**
	 * Register methods
	 * @param miniScript miniScript
	 */
	static void registerMethods(MiniScript* miniScript);

};

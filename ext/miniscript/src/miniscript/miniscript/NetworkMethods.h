#pragma once

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using miniscript::miniscript::MiniScript;

/**
 * MiniScript script network methods
 * @author Andreas Drewke
 */
class miniscript::miniscript::NetworkMethods {
public:
	/**
	 * Register methods
	 * @param miniScript miniScript
	 */
	static void registerMethods(MiniScript* miniScript);

};

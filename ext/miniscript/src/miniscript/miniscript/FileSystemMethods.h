#pragma once

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using miniscript::miniscript::MiniScript;

/**
 * MiniScript script file system methods
 * @author Andreas Drewke
 */
class miniscript::miniscript::FileSystemMethods {
public:
	/**
	 * Register methods
	 * @param miniScript miniScript
	 */
	static void registerMethods(MiniScript* miniScript);

};

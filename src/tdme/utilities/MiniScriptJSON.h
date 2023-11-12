#pragma once

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::utilities::MiniScript;

/**
 * MiniScript JSON functions
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptJSON {
public:
	/**
	 * Register methods
	 * @param miniScript miniScript
	 */
	static void registerMethods(MiniScript* miniScript);

};

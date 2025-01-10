#pragma once

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>
#include <minitscript/minitscript/MinitScript.h>

/**
 * MinitScript script base methods
 * @author Andreas Drewke
 */
class minitscript::minitscript::BaseMethods {
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

};

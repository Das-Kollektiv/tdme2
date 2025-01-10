#pragma once

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>

/**
 * MinitScript script byte array methods
 * @author Andreas Drewke
 */
class minitscript::minitscript::ByteArrayMethods {
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

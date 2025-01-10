#pragma once

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>

/**
 * MinitScript script xml methods
 * @author Andreas Drewke
 */
class minitscript::minitscript::XMLMethods {
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

private:
	/**
	 * Escape given string in terms of XML
	 * @param str string
	 */
	static const string escape(const string& str);

};

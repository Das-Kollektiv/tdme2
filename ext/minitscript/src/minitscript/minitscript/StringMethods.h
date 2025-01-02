#pragma once

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>

using minitscript::minitscript::MinitScript;

/**
 * MinitScript script string methods
 * @author Andreas Drewke
 */
class minitscript::minitscript::StringMethods {
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
	 * Tokenize
	 * @param stringValue string value
	 * @param delimiters delimters
	 * @param emptyTokens empty tokens
	 */
	static vector<string> tokenize(const string& stringValue, const string& delimiters, bool emptyTokens = false);

};

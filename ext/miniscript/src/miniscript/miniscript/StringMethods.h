#pragma once

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>
#include <miniscript/utilities/UTF8CharacterIterator.h>

using miniscript::miniscript::MiniScript;
using miniscript::utilities::UTF8CharacterIterator;

/**
 * MiniScript script string methods
 * @author Andreas Drewke
 */
class miniscript::miniscript::StringMethods {
public:
	/**
	 * Register methods
	 * @param miniScript miniScript
	 */
	static void registerMethods(MiniScript* miniScript);

	/**
	 * Tokenize
	 * @param stringValue string value
	 * @param delimiters delimters
	 * @param emptyTokens empty tokens
	 */
	static vector<string> tokenize(const string& stringValue, const string& delimiters, bool emptyTokens = false);

};

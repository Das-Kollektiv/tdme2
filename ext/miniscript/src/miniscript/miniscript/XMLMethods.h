#pragma once

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using miniscript::miniscript::MiniScript;

/**
 * MiniScript script xml methods
 * @author Andreas Drewke
 */
class miniscript::miniscript::XMLMethods {
public:
	/**
	 * Register methods
	 * @param miniScript miniScript
	 */
	static void registerMethods(MiniScript* miniScript);

private:
	/**
	 * Escape given string in terms of XML
	 * @param str string
	 */
	static const string escape(const string& str);

};

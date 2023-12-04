#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/fwd-miniscript.h>

using std::string;

/**
 * Version
 * @author Andreas Drewke
 */
struct miniscript::miniscript::Version final
{
public:
	/**
	 * @return version
	 */
	static string getVersion();

	/**
	 * @return copyright
	 */
	static string getCopyright();

};

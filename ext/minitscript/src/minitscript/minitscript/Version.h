#pragma once

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>

using std::string;

/**
 * Version
 * @author Andreas Drewke
 */
struct minitscript::minitscript::Version final
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

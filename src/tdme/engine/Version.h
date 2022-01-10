#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::string;

/**
 * Version
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::Version final
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

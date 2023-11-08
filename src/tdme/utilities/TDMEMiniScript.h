#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/MiniScript.h>

using std::string;

using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::TDMEMiniScript;

/**
 * TDME MiniScript
 */
class TDMEMiniScript: public MiniScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(TDMEMiniScript)

	/**
	 * Load script
	 * @param pathName path name
	 * @param fileName file name
	 */
	static TDMEMiniScript* loadScript(const string& pathName, const string& fileName);

	/**
	 * Public constructor
	 */
	TDMEMiniScript();

};

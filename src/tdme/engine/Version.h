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
	inline static string getVersion() {
		return "1.9.99";
	}

	/**
	 * @return copyright
	 */
	inline static string getCopyright() {
		return "Programmed 2012-2021 by Andreas Drewke, drewke.net. Please see the license @ https://github.com/andreasdr/tdme2/blob/master/LICENSE";
	}

};
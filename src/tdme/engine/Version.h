#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::string;

/**
 * Version
 * @author Andreas Drewke
 */
struct tdme::engine::Version final
{
public:
	/**
	 * @returns version
	 */
	static string getVersion();

	/**
	 * @returns copyright
	 */
	static string getCopyright();

};

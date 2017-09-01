// Generated from /tdme/src/tdme/utils/Key.java

#pragma once

#include <tdme/utils/fwd-tdme.h>

#include <string>

using std::wstring;

/**
 * Key
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::Float final
{
public:

	/**
	 * Parse float
	 * @param string
	 * @return float
	 */
	static float parseFloat(const wstring& string);

};

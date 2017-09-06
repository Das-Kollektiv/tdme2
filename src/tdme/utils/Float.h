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
	static constexpr float MAX_VALUE { 3.4028235E38f };

	/**
	 * Parse float
	 * @param string
	 * @return float
	 */
	static float parseFloat(const wstring& string);

};

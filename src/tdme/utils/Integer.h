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
class tdme::utils::Integer final
{
public:

	/**
	 * Parse integer
	 * @param string
	 * @return integer
	 */
	static int parseInt(const wstring& string);

};

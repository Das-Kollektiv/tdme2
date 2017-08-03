#pragma once

#include <string>

#include <tdme/utils/fwd-tdme.h>

using std::string;
using std::wstring;

/** 
 * String utilities
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::utils::StringUtils final
{
public:

	/**
	 * Checks if string starts with prefix
	 * @param source string
     * @param prefix string
	 * @return bool
	 */
	static const bool startsWith(const wstring& src, const wstring& prefix);

};


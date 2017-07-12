#pragma once

#include <tdme/os/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include "../utils/_Exception.h"

using tdme::utils::_Exception;

/** 
 * File system exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::os::_FileSystemException: public _Exception
{
public:

	/**
	 * @brief Public constructor
	 * @param message Exception message
	 */
	_FileSystemException(const wstring& message) throw();

};

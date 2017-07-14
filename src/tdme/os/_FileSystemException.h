#pragma once

#include <tdme/os/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/_ExceptionBase.h>

using tdme::utils::_ExceptionBase;

/** 
 * File system exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::os::_FileSystemException: public _ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message Exception message
	 */
	_FileSystemException(const string& message) throw();

};

#pragma once

#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/_ExceptionBase.h>

using tdme::utils::_ExceptionBase;

/** 
 * File system exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::os::filesystem::_FileSystemException: public _ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message Exception message
	 */
	_FileSystemException(const string& message) throw();

};

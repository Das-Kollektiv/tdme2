#pragma once

#include <tdme/engine/fileio/models/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/_ExceptionBase.h>

using tdme::utils::_ExceptionBase;

/**
 * Model file IO exception
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::models::ModelFileIOException: public _ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message Exception message
	 */
	ModelFileIOException(const string& message) throw();

};

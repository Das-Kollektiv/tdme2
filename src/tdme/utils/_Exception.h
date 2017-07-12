/**
 * @author Andreas Drewke
 * @version $Id: 40a4a8159e048a3026211e19a8dcb2f6a226ed81 $
 */
#pragma once

#include <stdexcept>
#include <string>

#include <fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::runtime_error;
using std::wstring;

/**
 * Exception base class
 * @author Andreas Drewke
 */
class tdme::utils::_Exception: public runtime_error {
	public:
		/**
		 * @brief Public constructor
		 * @param message Exception message
		 */
		_Exception(const wstring& message) throw();
		~_Exception() throw();
};


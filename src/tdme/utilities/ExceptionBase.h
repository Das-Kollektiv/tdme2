/**
 * @author Andreas Drewke
 */
#pragma once

#include <stdexcept>
#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::runtime_error;
using std::string;

/**
 * Exception base class
 * @author Andreas Drewke
 */
class tdme::utilities::ExceptionBase: public runtime_error {
	public:
		/**
		 * @brief Public constructor
		 * @param message message Exception message
		 */
		ExceptionBase(const string& message) throw();
		~ExceptionBase() throw();
};

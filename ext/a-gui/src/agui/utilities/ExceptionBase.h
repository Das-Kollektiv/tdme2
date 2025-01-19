/**
 * @author Andreas Drewke
 */
#pragma once

#include <stdexcept>
#include <string>

#include <agui/agui.h>
#include <agui/utilities/fwd-agui.h>

using std::runtime_error;
using std::string;

/**
 * Exception base class
 * @author Andreas Drewke
 */
class agui::utilities::ExceptionBase: public runtime_error {
	public:
		/**
		 * @brief Public constructor
		 * @param message message Exception message
		 */
		ExceptionBase(const string& message) throw();
		~ExceptionBase() throw();
};

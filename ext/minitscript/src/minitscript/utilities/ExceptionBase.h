/**
 * @author Andreas Drewke
 */
#pragma once

#include <stdexcept>
#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/fwd-minitscript.h>

using std::runtime_error;
using std::string;

/**
 * Exception base class
 * @author Andreas Drewke
 */
class minitscript::utilities::ExceptionBase: public runtime_error {
public:
	/**
	 * @brief Public constructor
	 * @param message message Exception message
	 */
	ExceptionBase(const string& message) throw();
	~ExceptionBase() throw();
};

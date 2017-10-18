#pragma once

#include <string>

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/ExceptionBase.h>
#include <tdme/os/network/fwd-tdme.h>

using tdme::utils::ExceptionBase;

/**
 * Base exception class for NIO exceptions
 * @author Andreas Drewke
 */
class tdme::os::network::NIOException: public ExceptionBase {
	public:
		/**
		 * @brief public constructor
		 * @param message exception message
		 */
		NIOException(const string &message) throw();
};

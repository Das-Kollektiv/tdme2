#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/os/network/fwd-tdme.h>

using tdme::utilities::ExceptionBase;

/**
 * Base exception class for NIO exceptions
 * @author Andreas Drewke
 */
class tdme::os::network::NIOException: public ExceptionBase {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NIOException(const string &message) throw();
};

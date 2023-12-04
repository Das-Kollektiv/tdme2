#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/network/httpclient/fwd-miniscript.h>
#include <miniscript/utilities/ExceptionBase.h>

using miniscript::utilities::ExceptionBase;

/**
 * HTTP client exception
 * @author Andreas Drewke
 */
class miniscript::network::httpclient::HTTPClientException: public ExceptionBase {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	HTTPClientException(const string &message) throw();
};

#pragma once

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/network/httpclient/fwd-minitscript.h>
#include <minitscript/utilities/ExceptionBase.h>

/**
 * HTTP client exception
 * @author Andreas Drewke
 */
class minitscript::network::httpclient::HTTPClientException: public ::minitscript::utilities::ExceptionBase {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	HTTPClientException(const string &message) throw();
};

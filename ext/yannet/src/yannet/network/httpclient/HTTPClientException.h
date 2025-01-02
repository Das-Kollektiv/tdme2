#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/network/httpclient/fwd-yannet.h>
#include <yannet/utilities/ExceptionBase.h>

/**
 * HTTP client exception
 * @author Andreas Drewke
 */
class yannet::network::httpclient::HTTPClientException: public yannet::utilities::ExceptionBase {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	HTTPClientException(const string &message) throw();
};

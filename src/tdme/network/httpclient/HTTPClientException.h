#pragma once

#include <string>

#include <tdme/network/httpclient/fwd-tdme.h>
#include <tdme/utils/ExceptionBase.h>

using tdme::utils::ExceptionBase;

/**
 * HTTP client exception
 * @author Andreas Drewke
 */
class tdme::network::httpclient::HTTPClientException: public ExceptionBase {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	HTTPClientException(const string &message) throw();
};

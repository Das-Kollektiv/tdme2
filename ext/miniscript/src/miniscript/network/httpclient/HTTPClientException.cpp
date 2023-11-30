#include <miniscript/network/httpclient/HTTPClientException.h>

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/network/httpclient/HTTPClientException.h>

using miniscript::network::httpclient::HTTPClientException;

using std::string;

using miniscript::utilities::ExceptionBase;

HTTPClientException::HTTPClientException(const string &message) throw() : ExceptionBase(message) {
}


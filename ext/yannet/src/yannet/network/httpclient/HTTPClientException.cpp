#include <yannet/network/httpclient/HTTPClientException.h>

#include <string>

#include <yannet/yannet.h>
#include <yannet/network/httpclient/HTTPClientException.h>

using yannet::network::httpclient::HTTPClientException;

using std::string;

using yannet::utilities::ExceptionBase;

HTTPClientException::HTTPClientException(const string &message) throw() : ExceptionBase(message) {
}


#include <minitscript/network/httpclient/HTTPClientException.h>

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/network/httpclient/HTTPClientException.h>

using minitscript::network::httpclient::HTTPClientException;

using std::string;

using minitscript::utilities::ExceptionBase;

HTTPClientException::HTTPClientException(const string &message) throw() : ExceptionBase(message) {
}


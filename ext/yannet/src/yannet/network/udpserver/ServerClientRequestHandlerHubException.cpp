#include <yannet/network/udpserver/ServerClientRequestHandlerHubException.h>

#include <string>

#include <yannet/yannet.h>
#include <yannet/utilities/ExceptionBase.h>

using std::string;

using yannet::network::udpserver::ServerClientRequestHandlerHubException;
using yannet::utilities::ExceptionBase;

ServerClientRequestHandlerHubException::ServerClientRequestHandlerHubException(const string &message) throw() : ExceptionBase(message) {
}

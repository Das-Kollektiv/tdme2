#include <tdme/network/udpserver/NIOServerClientRequestHandlerHubException.h>

#include <string>

#include <tdme/utilities/ExceptionBase.h>

using std::string;

using tdme::network::udpserver::NIOServerClientRequestHandlerHubException;
using tdme::utilities::ExceptionBase;

NIOServerClientRequestHandlerHubException::NIOServerClientRequestHandlerHubException(const string &message) throw() : ExceptionBase(message) {
}

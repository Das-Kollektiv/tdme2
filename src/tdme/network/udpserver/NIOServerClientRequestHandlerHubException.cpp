#include <tdme/network/udpserver/NIOServerClientRequestHandlerHubException.h>

#include <string>

#include <tdme/utils/ExceptionBase.h>

using std::string;

using tdme::network::udpserver::NIOServerClientRequestHandlerHubException;
using tdme::utils::ExceptionBase;

NIOServerClientRequestHandlerHubException::NIOServerClientRequestHandlerHubException(const string &message) throw() : ExceptionBase(message) {
}

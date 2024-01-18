#include <signal.h>

#include <memory>
#include <string>

#include "UDPServerTest_UDPServer.h"
#include "UDPServerTest_UDPServerClient.h"

#include <tdme/tdme.h>
#include <tdme/os/network/Network.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using tdme::os::network::Network;
using tdme::os::threading::Queue;
using tdme::os::threading::Thread;
using tdme::utilities::Console;

class ServerBroadcaster : public Thread {
public:
	// forbid class copy
	FORBID_CLASS_COPY(ServerBroadcaster)

	//
	ServerBroadcaster(EchoUDPServer *server) : Thread("broadcaster"), server(server), time(0) {}

	virtual ~ServerBroadcaster() {
	}

	virtual void run() {
		while (isStopRequested() == false) {
			Thread::sleep(1000);
			if (++time == 5) {
				// get client key list
				auto clientKeySet = server->getClientKeySet();
				for (const auto& clientKey: clientKeySet) {
					auto client = static_cast<EchoUDPServerClient*>(server->getClientByKey(clientKey));
					if (client != NULL) {
						auto packet = client->createPacket();
						packet->putString("broadcast test");
						client->send(packet, true);
						client->releaseReference();
					}
				}
				time = 0;
			}
		}
	}
private:
	EchoUDPServer *server;
	unsigned int time;
};

unique_ptr<EchoUDPServer> server;
unique_ptr<ServerBroadcaster> bc;

void sigHandlerINT(int signal) {
	Console::printLine("Interrupt signal catched");
	if (server != nullptr) {
		// stop broad caster
		server->stop();
	}
}

int main(int argc, char *argv[]) {
	// install SIGNINT handler
	if (signal(SIGINT, sigHandlerINT) == SIG_ERR) {
		Console::printLine("Can't install signal handler for SIGINT");
	}

	// initialize network module
	Network::initialize();

	// start echo server
	server = make_unique<EchoUDPServer>("127.0.0.1", 10000, 100);
	bc = make_unique<ServerBroadcaster>(server.get());
	bc->start();
	server->start();

	// wait until server has been stopped
	server->join();

	// stop and wait for broad caster
	bc->stop();
	bc->join();

	//
	Console::shutdown();
	return 0;
}

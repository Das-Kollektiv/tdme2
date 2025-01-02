#include <signal.h>

#include <iostream>
#include <memory>

#include <yannet/yannet.h>
#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpclient/UDPClient.h>
#include <yannet/network/udpclient/UDPClientMessage.h>
#include <yannet/os/network/Network.h>
#include <yannet/os/threading/Thread.h>

#include <yannet/utilities/Console.h>

using std::make_unique;
using std::unique_ptr;

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

using yannet::network::udp::UDPPacket;
using yannet::network::udpclient::UDPClient;
using yannet::network::udpclient::UDPClientMessage;
using yannet::os::network::Network;
using yannet::os::threading::Thread;
using yannet::utilities::Console;

unique_ptr<UDPClient> client;

class InputThread: public Thread {
public:
	InputThread(): Thread("inputthread") {
	}

	virtual void run() {
		while (isStopRequested() == false) {
			string input;
			cin >> input;
			auto packet = new UDPPacket();
			packet->putString(input);
			if (client != nullptr) {
				client->sendMessage(client->createMessage(packet), true);
			}
		}
	}
};

unique_ptr<InputThread> inputThread;

void sigHandlerINT(int signal) {
	Console::printLine("Interrupt signal catched");
	if (inputThread != nullptr) {
		inputThread->stop();
	}
	if (client != nullptr) {
		client->stop();
	}
}

int main(int argc, char *argv[]) {
	// install SIGNINT handler
	if (signal(SIGINT, sigHandlerINT) == SIG_ERR) {
		Console::printLine("Can't install signal handler for SIGINT");
	}
	// initialize network module
	Network::initialize();

	// input thread
	inputThread = make_unique<InputThread>();
	inputThread->start();

	// UDP client
	client = make_unique<UDPClient>("127.0.0.1", 10000);
	client->start();

	// handle incoming messages
	while (client->isStopRequested() == false) {
		Thread::sleep(1L);
		// process incoming messages
		auto message = unique_ptr<UDPClientMessage>(client->receiveMessage());
		if (message == nullptr) continue;
		if (client->processSafeMessage(message.get()) == true) {
			Console::printLine("Received message: " + message->getPacket()->getString());
		}
	}

	//
	Console::shutdown();
	return 0;
}

#include <tdme/engine/logics/ApplicationServer.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/logics/ApplicationServerClient.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/ServerThread.h>
#include <tdme/engine/physics/World.h>
#include <tdme/network/udpserver/UDPServer.h>
#include <tdme/network/udpserver/UDPServerClient.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;

using tdme::engine::logics::ApplicationServer;

using tdme::engine::logics::ApplicationServerClient;
using tdme::engine::logics::Context;
using tdme::engine::logics::ServerThread;
using tdme::network::udpserver::UDPServer;
using tdme::network::udpserver::UDPServerClient;
using tdme::utilities::Console;

ApplicationServer::ApplicationServer(const string& host, const unsigned int port, const unsigned int maxCCU, int pathFindingThreadCount) : UDPServer("ws", host, port, maxCCU), pathFindingThreadCount(pathFindingThreadCount) {
	setIOThreadCount(2);
	setWorkerThreadCount(2);

	//
	Console::println("ApplicationServer::ApplicationServer(): Starting WS UDP server @ " + host + ":" + to_string(port));
}

void ApplicationServer::run() {
	// init
	Console::println("ApplicationServer::ApplicationServer(): Initializing");

	//
	context = new Context(true);
	context->getPathFinding()->setThreadCount(pathFindingThreadCount);
	context->setWorld(new World());
	// TODO: Add default game logics here
	context->addGameLogicsNew();
	gameLogicThread = new ServerThread(context, this);
	context->setGameLogicMutex(this->gameLogicThread->getMutex());

	// starting game logic thread
	Console::println("ApplicationServer::ApplicationServer(): Starting game logic thread");
	gameLogicThread->start();

	// run NIO UDP server
	UDPServer::run();

	// TODO: run shutdown logic
}

ApplicationServer::~ApplicationServer() {
	Console::println("ApplicationServer::~ApplicationServer(): Shutting down");

	//
	context->shutdown();

	//
	gameLogicThread->stop();
	gameLogicThread->join();
	delete gameLogicThread;

	//
	delete context;
}

UDPServerClient* ApplicationServer::accept(const uint32_t clientId, const std::string& ip, const unsigned int port) {
	Console::println("Accepting client connection with '" + ip + ":" + to_string(port) + "'");

	//
	return new ApplicationServerClient(clientId, ip, port);
}

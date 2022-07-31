#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/ApplicationServerClient.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/NetworkLogic.h>
#include <tdme/engine/logics/NewClientLogic.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/engine/logics/ServerThread.h>
#include <tdme/engine/physics/World.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

using std::remove;
using std::string;
using std::to_string;
using std::unordered_set;
using std::vector;

using tdme::engine::logics::ApplicationServerClient;
using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::logics::NetworkLogic;
using tdme::engine::logics::NewClientLogic;
using tdme::engine::logics::LogicNetworkPacket;
using tdme::engine::logics::ServerThread;
using tdme::engine::physics::World;
using tdme::network::udp::UDPPacket;
using tdme::os::threading::Mutex;
using tdme::os::threading::ReadWriteLock;
using tdme::os::threading::Thread;
using tdme::utilities::Console;
using tdme::utilities::Time;

ServerThread::ServerThread(Context* context, ApplicationServer* server) : Thread("applicationserverthread", 4 * 1024 * 1024), mutex("applicationserverthread-mutex") {
	this->context = context;
	this->server = server;
}

Mutex* ServerThread::getMutex() {
	return &mutex;
}

void ServerThread::createDatagrams(vector<LogicNetworkPacket>& safeGameNetworkPackets, vector<LogicNetworkPacket>& fastGameNetworkPackets, vector<UDPPacket*>& sendPacketsSafe, vector<UDPPacket*>& sendPacketsFast) {
	// collect safe messages
	if (safeGameNetworkPackets.size() > 0) {
		auto packet = UDPServerClient::createPacket();
		// safe packet
		packet->putBool(true);
		//
		for (auto& gameNetworkPacket: safeGameNetworkPackets) {
			// game network packet size
			char size = gameNetworkPacket.getPosition();
			// datagram size
			auto datagramSize = packet->getPosition();
			//
			if (datagramSize + 5 + (uint16_t)size > UDPPacket::PACKET_MAX_SIZE) {
				//
				if (datagramSize < UDPPacket::PACKET_MAX_SIZE) {
					// no more game network packets
					packet->putByte(0);
				}
				sendPacketsSafe.push_back(packet);
				//
				packet = UDPServerClient::createPacket();
				// safe packet
				packet->putBool(true);
			}
			// size
			packet->putByte(size);
			// game logic type id
			packet->putInt(gameNetworkPacket.getGameLogicTypeId());
			// payload
			packet->putBytes(gameNetworkPacket.getData(), gameNetworkPacket.getPosition());
		}
		// datagram size
		auto datagramSize = packet->getPosition();
		//
		if (datagramSize > 17 + 1) {
			if (datagramSize < UDPPacket::PACKET_MAX_SIZE) {
				// end of game network packets
				packet->putByte(0);
			}
			//
			sendPacketsSafe.push_back(packet);
		} else {
			delete packet;
		}
	}
	// collect fast messages
	if (fastGameNetworkPackets.size() > 0) {
		auto packet = UDPServerClient::createPacket();
		// no safe packet
		packet->putBool(false);
		//
		for (auto& gameNetworkPacket: fastGameNetworkPackets) {
			// game network packet size
			auto size = gameNetworkPacket.getPosition();
			// datagram size
			auto datagramSize = packet->getPosition();
			//
			if (datagramSize + 5 + (uint16_t)size > UDPPacket::PACKET_MAX_SIZE) {
				if (datagramSize < UDPPacket::PACKET_MAX_SIZE) {
					// no more game network packets
					packet->putByte(0);
				}
				sendPacketsFast.push_back(packet);
				packet = UDPServerClient::createPacket();
				// no safe packet
				packet->putBool(false);
			}
			// size
			packet->putByte(size);
			// game logic type id
			packet->putInt(gameNetworkPacket.getGameLogicTypeId());
			// payload
			packet->putBytes(gameNetworkPacket.getData(), gameNetworkPacket.getPosition());
		}
		// datagram size
		auto datagramSize = packet->getPosition();
		//
		if (datagramSize > 14 + 1) {
			if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 14) {
				// end of game network packets
				packet->putByte(0);
			}
			//
			sendPacketsFast.push_back(packet);
		} else {
			delete packet;
		}
	}
}

string ServerThread::getNetworkPacketGameLogicTypes(vector<LogicNetworkPacket>& gameNetworkPackets) {
	unordered_set<uint32_t> networkPacketTypesSet;
	string networkPacketTypes;
	for (auto& gameNetworkPacket: gameNetworkPackets) {
		networkPacketTypesSet.insert(gameNetworkPacket.getGameLogicTypeId());
	}
	for (auto& typeId: networkPacketTypesSet) {
		if (networkPacketTypes.size() > 0) networkPacketTypes+= ", ";
		networkPacketTypes+= typeId;
	}
	return networkPacketTypes;
}

void ServerThread::run() {
	int64_t timeLast = Time::getCurrentMillis();
	auto clientKeySetLast = server->getClientKeySet();
	vector<string> newClientKeys;
	map<string, vector<LogicNetworkPacket>> clientNetworkPacketsUnhandled;
	auto initializedLastFrame = false;
	while(isStopRequested() == false) {
		int64_t timeNow = Time::getCurrentMillis();
		map<string, vector<LogicNetworkPacket>> clientNetworkPackets;

		// determine current clients
		vector<ApplicationServerClient*> clients;
		vector<ApplicationServerClient*> updateClients;
		auto clientKeySet = server->getClientKeySet();
		for (auto clientKey: clientKeySet) {
			auto client = static_cast<ApplicationServerClient*>(server->getClientByKey(clientKey));
			if (client == nullptr) continue;
			// new client?
			if (clientKeySetLast.find(clientKey) == clientKeySetLast.end()) {
				newClientKeys.push_back(client->getKey());
			} else {
				// nope, known client
				updateClients.push_back(client);
			}
			// we have a client
			clients.push_back(client);
		}

		// push unhandlet packets to client packets, display an warning if not handled for 1s
		for (auto client: clients) {
			for (auto& packet: clientNetworkPacketsUnhandled[client->getKey()]) {
				if (timeNow - packet.getTime() > 1000L) {
					Console::println("ServerThread::run(): unhandled IN packet: 1s late: " + client->getKey() + ": " + to_string(packet.getGameLogicTypeId()));
				}
				packet.setReinjected();
				clientNetworkPackets[client->getKey()].push_back(packet);
			}
		}
		clientNetworkPacketsUnhandled.clear();

		// multicast packets to send for update
		map<string, vector<LogicNetworkPacket>> mcUpdateSafeGameNetworkPackets;
		map<string, vector<LogicNetworkPacket>> mcUpdateFastGameNetworkPackets;
		// broadcast packets to send for update
		vector<LogicNetworkPacket> bcUpdateSafeGameNetworkPackets;
		vector<LogicNetworkPacket> bcUpdateFastGameNetworkPackets;
		// multicast packets to send for initiation
		map<string, vector<LogicNetworkPacket>> mcInitialSafeGameNetworkPackets;
		map<string, vector<LogicNetworkPacket>> mcInitialFastGameNetworkPackets;
		// broadcast packets to send for initialization
		vector<LogicNetworkPacket> bcInitialSafeGameNetworkPackets;
		vector<LogicNetworkPacket> bcInitialFastGameNetworkPackets;

		// game logic + handle network packets
		mutex.lock();

		//
		context->initGameLogics();

		// new clients
		vector<ApplicationServerClient*> newClients;
		{
			//	new clients
			vector<string> newClientKeysToRemove;
			for (auto clientKey: newClientKeys) {
				auto client = static_cast<ApplicationServerClient*>(server->getClientByKey(clientKey));
				if (client == nullptr) {
					newClientKeysToRemove.push_back(clientKey);
					continue;
				}
				if (dynamic_cast<NewClientLogic*>(context->getGameLogic("l"))->handleNewClient(clientKey, client->getIp() + ":" + to_string(client->getPort())) == true) {
					newClientKeysToRemove.push_back(clientKey);
					newClients.push_back(client);
				} else {
					client->shutdown();
				}
			}
			for (auto clientKey: newClientKeysToRemove) {
				newClientKeys.erase(remove(newClientKeys.begin(), newClientKeys.end(), clientKey), newClientKeys.end());
			}
		}

		{
			//	new game logics: create initial network packets for clients
			auto gameLogicsNew = context->getGameLogicsNew();

			//	basically add new game logics to game logics
			context->addGameLogicsNew();

			//
			for (auto gameLogic: gameLogicsNew) static_cast<NetworkLogic*>(gameLogic)->createInitialNetworkPackets();
		}

		// fetch client packets
		for (auto client: clients) {
			client->getNetworkPacketsMutex().lock();
			clientNetworkPackets[client->getKey()] = client->getNetworkPackets();
			if (VERBOSE_NETWORK == true && clientNetworkPackets[client->getKey()].size() > 0) {
				Console::println(
					"ServerThread::run(): in: " +
					client->getKey() + ":" +
					to_string(clientNetworkPackets[client->getKey()].size()) + ": " +
					"(" + getNetworkPacketGameLogicTypes(client->getNetworkPackets()) + ")"
				);
			}
			client->getNetworkPackets().clear();
			client->getNetworkPacketsMutex().unlock();
		}

		// handle client packets
		// TODO: do rather a hashmap for looking up game logics by packet type id
		for (auto client: clients) {
			for (auto& packet: clientNetworkPackets[client->getKey()]) {
				for (auto gameLogic: context->getGameLogics()) {
					NetworkLogic* gameLogicNetwork = static_cast<NetworkLogic*>(gameLogic);
					if (gameLogicNetwork->getNetworkPacketTypeId() == packet.getGameLogicTypeId()) {
						packet.reset();
						gameLogicNetwork->handleNetworkPacket(packet);
					}
				}
			}
		}

		// we propably have game logics added, create initial packets from them and handle their in packets
		// TODO: do rather a hashmap for looking up game logics by packet type id
		while (true == true) {
			//	new game logics: create initial network packets for clients
			auto gameLogicsNew = context->getGameLogicsNew();

			//	basically add new game logics to game logics
			auto gameLogicsAdded = context->addGameLogicsNew();
			if (gameLogicsAdded == 0) break;

			//
			for (auto gameLogic: gameLogicsNew) static_cast<NetworkLogic*>(gameLogic)->createInitialNetworkPackets();

			// handle client packets
			for (auto client: clients) {
				for (auto& packet: clientNetworkPackets[client->getKey()]) {
					for (auto gameLogic: gameLogicsNew) {
						NetworkLogic* gameLogicNetwork = static_cast<NetworkLogic*>(gameLogic);
						if (gameLogicNetwork->getNetworkPacketTypeId() == packet.getGameLogicTypeId()) {
							packet.reset();
							gameLogicNetwork->handleNetworkPacket(packet);
						}
					}
				}
			}
		}

		//	do game logics
		for (auto gameLogic: context->getGameLogics()) {
			gameLogic->updateGameLogic();
			gameLogic->clearQueuedSounds();
		}

		// we propably have game logics added, create initial packets from them and handle their in packets
		while (true == true) {
			//	new game logics: create initial network packets for clients
			auto gameLogicsNew = context->getGameLogicsNew();

			//	basically add new game logics to game logics
			auto gameLogicsAdded = context->addGameLogicsNew();
			if (gameLogicsAdded == 0) break;

			//
			for (auto gameLogic: gameLogicsNew) static_cast<NetworkLogic*>(gameLogic)->createInitialNetworkPackets();

			// handle client packets
			for (auto client: clients) {
				for (auto& packet: clientNetworkPackets[client->getKey()]) {
					for (auto gameLogic: gameLogicsNew) {
						NetworkLogic* gameLogicNetwork = static_cast<NetworkLogic*>(gameLogic);
						if (gameLogicNetwork->getNetworkPacketTypeId() == packet.getGameLogicTypeId()) {
							packet.reset();
							gameLogicNetwork->handleNetworkPacket(packet);
						}
					}
				}
			}

			for (auto gameLogic: gameLogicsNew) {
				gameLogic->updateGameLogic();
				gameLogic->clearQueuedSounds();
			}
		}

		//	fire on game logics processed
		for (auto gameLogic: context->getGameLogics()) gameLogic->onGameLogicsProcessed();

		// check if there are in packets that have not yet been processed
		for (auto client: clients) {
			for (auto& packet: clientNetworkPackets[client->getKey()]) {
				if (packet.isProcessed() == false) {
					clientNetworkPacketsUnhandled[client->getKey()].push_back(packet);
				}
			}
		}

		// colllect broadcast network packets for update
		for (auto gameLogic: context->getGameLogics()) {
			NetworkLogic* gameLogicNetwork = static_cast<NetworkLogic*>(gameLogic);
			for (auto& gameNetworkPacket: gameLogicNetwork->getNetworkPackets()) {
				// packet logic type id
				if (gameNetworkPacket.getGameLogicTypeId() == LogicNetworkPacket::GAMELOGIC_TYPEID_NONE) {
					gameNetworkPacket.setGameLogicTypeId(gameLogicNetwork->getNetworkPacketTypeId());
				}
				// broadcast
				if (gameNetworkPacket.getRecipients().size() == 0) {
					if (gameNetworkPacket.getSafe() == true) {
						bcUpdateSafeGameNetworkPackets.push_back(gameNetworkPacket);
					} else {
						bcUpdateFastGameNetworkPackets.push_back(gameNetworkPacket);
					}
				} else {
					// multicast
					for (auto recipient: gameNetworkPacket.getRecipients()) {
						if (gameNetworkPacket.getSafe() == true) {
							mcUpdateSafeGameNetworkPackets[recipient].push_back(gameNetworkPacket);
						} else {
							mcUpdateFastGameNetworkPackets[recipient].push_back(gameNetworkPacket);
						}
					}
				}
			}
			gameLogicNetwork->getNetworkPackets().clear();
		}

		// colllect broadcast network packets for initialization
		if (newClients.size() > 0) {
			for (auto gameLogic: context->getGameLogics()) {
				NetworkLogic* gameLogicNetwork = static_cast<NetworkLogic*>(gameLogic);
				gameLogicNetwork->createInitialNetworkPackets();
				for (auto& gameNetworkPacket: gameLogicNetwork->getNetworkPackets()) {
					// set game logic type id
					if (gameNetworkPacket.getGameLogicTypeId() == LogicNetworkPacket::GAMELOGIC_TYPEID_NONE) {
						gameNetworkPacket.setGameLogicTypeId(gameLogicNetwork->getNetworkPacketTypeId());
					}
					// broadcast packets
					if (gameNetworkPacket.getRecipients().size() == 0) {
						if (gameNetworkPacket.getSafe() == true) {
							bcInitialSafeGameNetworkPackets.push_back(gameNetworkPacket);
						} else {
							bcInitialFastGameNetworkPackets.push_back(gameNetworkPacket);
						}
					} else {
						for (auto recipient: gameNetworkPacket.getRecipients()) {
							if (gameNetworkPacket.getSafe() == true) {
								mcInitialSafeGameNetworkPackets[recipient].push_back(gameNetworkPacket);
							} else {
								mcInitialFastGameNetworkPackets[recipient].push_back(gameNetworkPacket);
							}
						}
					}
				}
				gameLogicNetwork->getNetworkPackets().clear();
			}
		}

		//
		context->doneGameLogics();

		// done
		mutex.unlock();

		// send initial messages to new clients
		if (newClients.size() > 0) {
			// broad cast
			{
				// broadcast datagrams to send for initialization
				vector<UDPPacket*> bcSendInitialPacketsSafe;
				vector<UDPPacket*> bcSendInitialPacketsFast;
				createDatagrams(bcInitialSafeGameNetworkPackets, bcInitialFastGameNetworkPackets, bcSendInitialPacketsSafe, bcSendInitialPacketsFast);
				if (VERBOSE_NETWORK == true && bcSendInitialPacketsSafe.size() > 0) {
					Console::println(
						"ServerThread::run(): initial: bc out: safe: " +
						to_string(bcSendInitialPacketsSafe.size()) + ": " +
						getNetworkPacketGameLogicTypes(bcInitialSafeGameNetworkPackets)
					);
				}
				if (VERBOSE_NETWORK == true && bcSendInitialPacketsFast.size() > 0) {
					Console::println(
						"ServerThread::run(): initial: bc out: fast: " +
						to_string(bcSendInitialPacketsFast.size()) + ": " +
						getNetworkPacketGameLogicTypes(bcInitialFastGameNetworkPackets)
					);
				}
				for (auto client: newClients) {
					for (auto packet: bcSendInitialPacketsSafe) client->send(packet, true, false);
					for (auto packet: bcSendInitialPacketsFast) client->send(packet, false, false);
				}
				for (auto packet: bcSendInitialPacketsSafe) delete packet;
				for (auto packet: bcSendInitialPacketsFast) delete packet;
			}
			{
				// multi cast
				for (auto client: newClients) {
					vector<UDPPacket*> mcSendInitialPacketsSafe;
					vector<UDPPacket*> mcSendInitialPacketsFast;
					auto& mcInitialSafePacketsClient = mcInitialSafeGameNetworkPackets[client->getKey()];
					auto& mcInitialFastPacketsClient = mcInitialFastGameNetworkPackets[client->getKey()];
					createDatagrams(mcInitialSafePacketsClient, mcInitialFastPacketsClient, mcSendInitialPacketsSafe, mcSendInitialPacketsFast);
					if (VERBOSE_NETWORK == true && mcSendInitialPacketsSafe.size() > 0) {
						Console::println(
							"ServerThread::run(): initial: mc out: " +
							client->getKey() +
							": safe: " + to_string(mcSendInitialPacketsSafe.size()) + ": " +
							getNetworkPacketGameLogicTypes(mcInitialSafePacketsClient)
						);
					}
					if (VERBOSE_NETWORK == true && mcSendInitialPacketsFast.size() > 0) {
						Console::println(
							"ServerThread::run(): initial: mc out: " +
							client->getKey() +
							": fast: " + to_string(mcSendInitialPacketsFast.size()) + ": " +
							getNetworkPacketGameLogicTypes(mcInitialFastPacketsClient)
						);
					}
					for (auto packet: mcSendInitialPacketsSafe) client->send(packet, true);
					for (auto packet: mcSendInitialPacketsFast) client->send(packet, false);
				}
			}
		}

		// send messages to update clients
		{
			// broad cast
			{
				// broadcast datagrams to send for update
				vector<UDPPacket*> bcSendUpdatePacketsSafe;
				vector<UDPPacket*> bcSendUpdatePacketsFast;
				createDatagrams(bcUpdateSafeGameNetworkPackets, bcUpdateFastGameNetworkPackets, bcSendUpdatePacketsSafe, bcSendUpdatePacketsFast);
				if (VERBOSE_NETWORK == true && bcSendUpdatePacketsSafe.size() > 0) {
					Console::println(
						"ServerThread::run(): bc out: safe: " +
						to_string(bcSendUpdatePacketsSafe.size()) + ": " +
						getNetworkPacketGameLogicTypes(bcUpdateSafeGameNetworkPackets)
					);
				}
				if (VERBOSE_NETWORK == true && bcSendUpdatePacketsFast.size() > 0) {
					Console::println(
						"ServerThread::run(): bc out: fast: " +
						to_string(bcSendUpdatePacketsFast.size()) + ": " +
						getNetworkPacketGameLogicTypes(bcUpdateFastGameNetworkPackets)
					);
				}
				for (auto client: updateClients) {
					for (auto packet: bcSendUpdatePacketsSafe) client->send(packet, true, false);
					for (auto packet: bcSendUpdatePacketsFast) client->send(packet, false, false);
				}
				for (auto packet: bcSendUpdatePacketsSafe) delete packet;
				for (auto packet: bcSendUpdatePacketsFast) delete packet;
			}
			// multi cast
			{
				for (auto client: clients) {
					vector<UDPPacket*> mcSendUpdatePacketsSafe;
					vector<UDPPacket*> mcSendUpdatePacketsFast;
					auto& mcUpdateSafePacketsClient = mcUpdateSafeGameNetworkPackets[client->getKey()];
					auto& mcUpdateFastPacketsClient = mcUpdateFastGameNetworkPackets[client->getKey()];
					if (VERBOSE_NETWORK == true && mcSendUpdatePacketsSafe.size() > 0) {
						Console::println(
							"ServerThread::run(): mc out: " +
							client->getKey() + ": safe: " +
							to_string(mcSendUpdatePacketsSafe.size()) + ": " +
							getNetworkPacketGameLogicTypes(mcUpdateSafePacketsClient)
						);
					}
					if (VERBOSE_NETWORK == true && mcSendUpdatePacketsFast.size() > 0) {
						Console::println(
							"ServerThread::run(): mc out: " +
							client->getKey() + ": fast: " +
							": fast: " + to_string(mcSendUpdatePacketsFast.size()) + ": " +
							getNetworkPacketGameLogicTypes(mcUpdateFastPacketsClient)
						);
					}
					createDatagrams(mcUpdateSafePacketsClient, mcUpdateFastPacketsClient, mcSendUpdatePacketsSafe, mcSendUpdatePacketsFast);
					for (auto packet: mcSendUpdatePacketsSafe) client->send(packet, true);
					for (auto packet: mcSendUpdatePacketsFast) client->send(packet, false);
				}
			}
		}

		// release references
		for (auto client: clients) {
			client->releaseReference();
		}

		// set last client key set
		clientKeySetLast = clientKeySet;

		// get some rest
		int64_t timeDelta = Time::getCurrentMillis() - timeLast;
		if (timeDelta > 33) {
			Console::println("ServerThread::run(): time delta < 33FPS, it took " + to_string(timeDelta) + " ms to compute");
			timeDelta = 33;
		} else
		if (timeDelta < 16) {
			timeDelta = 16;
		}
		// update world if we have any
		if (context->isInitialized() == true) {
			context->getWorld()->update(timeDelta / 1000.0f);
		} else {
		}
		timeDelta = Time::getCurrentMillis() - timeLast;
		if (timeDelta < 16) {
			Thread::sleep(16 - timeDelta);
		}
		timeLast = Time::getCurrentMillis();
	}
}

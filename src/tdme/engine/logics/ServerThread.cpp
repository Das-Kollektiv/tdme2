#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/ApplicationServerClient.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/engine/logics/NetworkLogic.h>
#include <tdme/engine/logics/NewClientLogic.h>
#include <tdme/engine/logics/ServerThread.h>
#include <tdme/engine/physics/World.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::remove;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

using tdme::engine::logics::ApplicationServerClient;
using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicNetworkPacket;
using tdme::engine::logics::NetworkLogic;
using tdme::engine::logics::NewClientLogic;
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

void ServerThread::createDatagrams(vector<LogicNetworkPacket>& safeLogicNetworkPackets, vector<LogicNetworkPacket>& fastLogicNetworkPackets, vector<UDPPacket*>& sendPacketsSafe, vector<UDPPacket*>& sendPacketsFast) {
	// collect safe messages
	if (safeLogicNetworkPackets.size() > 0) {
		auto packet = unique_ptr<UDPPacket>(UDPServerClient::createPacket());
		// safe packet
		packet->putBool(true);
		//
		for (auto& logicNetworkPacket: safeLogicNetworkPackets) {
			// network packet size
			char size = logicNetworkPacket.getPosition();
			// datagram size
			auto datagramSize = packet->getPosition();
			//
			if (datagramSize + 5 + (uint16_t)size > UDPPacket::PACKET_MAX_SIZE) {
				//
				if (datagramSize < UDPPacket::PACKET_MAX_SIZE) {
					// no more network packets
					packet->putByte(0);
				}
				sendPacketsSafe.push_back(packet.release());
				//
				packet = unique_ptr<UDPPacket>(UDPServerClient::createPacket());
				// safe packet
				packet->putBool(true);
			}
			// size
			packet->putByte(size);
			// logic type id
			packet->putInt(logicNetworkPacket.getLogicTypeId());
			// payload
			packet->putBytes(logicNetworkPacket.getData(), logicNetworkPacket.getPosition());
		}
		// datagram size
		auto datagramSize = packet->getPosition();
		//
		if (datagramSize > 17 + 1) {
			if (datagramSize < UDPPacket::PACKET_MAX_SIZE) {
				// end of network packets
				packet->putByte(0);
			}
			//
			sendPacketsSafe.push_back(packet.release());
		}
	}
	// collect fast messages
	if (fastLogicNetworkPackets.size() > 0) {
		auto packet = unique_ptr<UDPPacket>(UDPServerClient::createPacket());
		// no safe packet
		packet->putBool(false);
		//
		for (auto& logicNetworkPacket: fastLogicNetworkPackets) {
			// network packet size
			auto size = logicNetworkPacket.getPosition();
			// datagram size
			auto datagramSize = packet->getPosition();
			//
			if (datagramSize + 5 + (uint16_t)size > UDPPacket::PACKET_MAX_SIZE) {
				if (datagramSize < UDPPacket::PACKET_MAX_SIZE) {
					// no more network packets
					packet->putByte(0);
				}
				sendPacketsFast.push_back(packet.release());
				packet = unique_ptr<UDPPacket>(UDPServerClient::createPacket());
				// no safe packet
				packet->putBool(false);
			}
			// size
			packet->putByte(size);
			// logic type id
			packet->putInt(logicNetworkPacket.getLogicTypeId());
			// payload
			packet->putBytes(logicNetworkPacket.getData(), logicNetworkPacket.getPosition());
		}
		// datagram size
		auto datagramSize = packet->getPosition();
		//
		if (datagramSize > 14 + 1) {
			if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 14) {
				// end of network packets
				packet->putByte(0);
			}
			//
			sendPacketsFast.push_back(packet.release());
		}
	}
}

const string ServerThread::getLogicNetworkPacketsLogicTypes(vector<LogicNetworkPacket>& logicNetworkPackets) {
	unordered_set<uint32_t> networkPacketTypesSet;
	string networkPacketTypes;
	for (auto& logicNetworkPacket: logicNetworkPackets) {
		networkPacketTypesSet.insert(logicNetworkPacket.getLogicTypeId());
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
	//
	unordered_map<string, vector<LogicNetworkPacket>> clientNetworkPacketsUnhandled;
	// multicast packets to send for update
	unordered_map<string, vector<LogicNetworkPacket>> mcUpdateSafeLogicNetworkPackets;
	unordered_map<string, vector<LogicNetworkPacket>> mcUpdateFastLogicNetworkPackets;
	// broadcast packets to send for update
	vector<LogicNetworkPacket> bcUpdateSafeLogicNetworkPackets;
	vector<LogicNetworkPacket> bcUpdateFastLogicNetworkPackets;
	// multicast packets to send for initiation
	unordered_map<string, vector<LogicNetworkPacket>> mcInitialSafeLogicNetworkPackets;
	unordered_map<string, vector<LogicNetworkPacket>> mcInitialFastLogicNetworkPackets;
	// broadcast packets to send for initialization
	vector<LogicNetworkPacket> bcInitialSafeLogicNetworkPackets;
	vector<LogicNetworkPacket> bcInitialFastLogicNetworkPackets;
	//
	unordered_map<string, vector<LogicNetworkPacket>> clientNetworkPackets;
	//
	vector<ApplicationServerClient*> clients;
	vector<ApplicationServerClient*> updateClients;
	//
	vector<UDPPacket*> bcSendInitialPacketsSafe;
	vector<UDPPacket*> bcSendInitialPacketsFast;
	//
	vector<UDPPacket*> mcSendInitialPacketsSafe;
	vector<UDPPacket*> mcSendInitialPacketsFast;
	//
	vector<UDPPacket*> bcSendUpdatePacketsSafe;
	vector<UDPPacket*> bcSendUpdatePacketsFast;
	//
	vector<UDPPacket*> mcSendUpdatePacketsSafe;
	vector<UDPPacket*> mcSendUpdatePacketsFast;
	//
	auto initializedLastFrame = false;
	while(isStopRequested() == false) {
		int64_t timeNow = Time::getCurrentMillis();

		// determine current clients
		auto clientKeySet = server->getClientKeySet();
		for (auto& clientKey: clientKeySet) {
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
					Console::println("ServerThread::run(): unhandled IN packet: 1s late: " + client->getKey() + ": " + to_string(packet.getLogicTypeId()));
				}
				packet.setReinjected();
				clientNetworkPackets[client->getKey()].push_back(packet);
			}
		}
		clientNetworkPacketsUnhandled.clear();

		// logic + handle network packets
		mutex.lock();

		//
		context->initUpdateLogics();

		// new clients
		vector<ApplicationServerClient*> newClients;
		{
			//	new clients
			vector<string> newClientKeysToRemove;
			for (const auto& clientKey: newClientKeys) {
				auto client = static_cast<ApplicationServerClient*>(server->getClientByKey(clientKey));
				if (client == nullptr) {
					newClientKeysToRemove.push_back(clientKey);
					continue;
				}
				if (dynamic_cast<NewClientLogic*>(context->getLogic("l"))->handleNewClient(clientKey, client->getIp() + ":" + to_string(client->getPort())) == true) {
					newClientKeysToRemove.push_back(clientKey);
					newClients.push_back(client);
				} else {
					client->shutdown();
				}
			}
			for (const auto& clientKey: newClientKeysToRemove) {
				newClientKeys.erase(remove(newClientKeys.begin(), newClientKeys.end(), clientKey), newClientKeys.end());
			}
		}

		{
			//	new logics: create initial network packets for clients
			auto newLogics = context->getNewLogics();

			//	basically add new logics to logics
			context->addNewLogics();

			//
			for (auto newLogic: newLogics) static_cast<NetworkLogic*>(newLogic)->createInitialNetworkPackets();
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
					"(" + getLogicNetworkPacketsLogicTypes(client->getNetworkPackets()) + ")"
				);
			}
			client->getNetworkPackets().clear();
			client->getNetworkPacketsMutex().unlock();
		}

		// handle client packets
		// TODO: do rather a hashmap for looking up logics by packet type id
		for (auto client: clients) {
			for (auto& packet: clientNetworkPackets[client->getKey()]) {
				for (auto logic: context->getLogics()) {
					NetworkLogic* networkLogic = static_cast<NetworkLogic*>(logic);
					if (networkLogic->getNetworkPacketTypeId() == packet.getLogicTypeId()) {
						packet.reset();
						networkLogic->handleNetworkPacket(packet);
					}
				}
			}
		}

		// we propably have logics added, create initial packets from them and handle their in packets
		// TODO: do rather a hashmap for looking up logics by packet type id
		while (true == true) {
			//	new logics: create initial network packets for clients
			auto newLogics = context->getNewLogics();

			//	basically add new logics to logics
			auto addedNewLogics = context->addNewLogics();
			if (addedNewLogics == 0) break;

			//
			for (auto logic: newLogics) static_cast<NetworkLogic*>(logic)->createInitialNetworkPackets();

			// handle client packets
			for (auto client: clients) {
				for (auto& packet: clientNetworkPackets[client->getKey()]) {
					for (auto logic: newLogics) {
						NetworkLogic* networkLogic = static_cast<NetworkLogic*>(logic);
						if (networkLogic->getNetworkPacketTypeId() == packet.getLogicTypeId()) {
							packet.reset();
							networkLogic->handleNetworkPacket(packet);
						}
					}
				}
			}
		}

		//	do logics
		for (auto logic: context->getLogics()) {
			logic->updateLogic();
			logic->clearQueuedSounds();
		}

		// we propably have logics added, create initial packets from them and handle their in packets
		while (true == true) {
			//	new logics: create initial network packets for clients
			auto newLogics = context->getNewLogics();

			//	basically add new logics to logics
			auto addedNewLogics = context->addNewLogics();
			if (addedNewLogics == 0) break;

			//
			for (auto logic: newLogics) static_cast<NetworkLogic*>(logic)->createInitialNetworkPackets();

			// handle client packets
			for (auto client: clients) {
				for (auto& packet: clientNetworkPackets[client->getKey()]) {
					for (auto logic: newLogics) {
						NetworkLogic* networkLogic = static_cast<NetworkLogic*>(logic);
						if (networkLogic->getNetworkPacketTypeId() == packet.getLogicTypeId()) {
							packet.reset();
							networkLogic->handleNetworkPacket(packet);
						}
					}
				}
			}

			for (auto logic: newLogics) {
				logic->updateLogic();
				logic->clearQueuedSounds();
			}
		}

		//	fire on logics processed
		for (auto logic: context->getLogics()) logic->onLogicsProcessed();

		// check if there are in packets that have not yet been processed
		for (auto client: clients) {
			for (auto& packet: clientNetworkPackets[client->getKey()]) {
				if (packet.isProcessed() == false) {
					clientNetworkPacketsUnhandled[client->getKey()].push_back(packet);
				}
			}
		}

		// colllect broadcast network packets for update
		for (auto logic: context->getLogics()) {
			NetworkLogic* networkLogic = static_cast<NetworkLogic*>(logic);
			for (auto& logicNetworkPacket: networkLogic->getNetworkPackets()) {
				// packet logic type id
				if (logicNetworkPacket.getLogicTypeId() == LogicNetworkPacket::LOGIC_TYPEID_NONE) {
					logicNetworkPacket.setLogicTypeId(networkLogic->getNetworkPacketTypeId());
				}
				// broadcast
				if (logicNetworkPacket.getRecipients().size() == 0) {
					if (logicNetworkPacket.getSafe() == true) {
						bcUpdateSafeLogicNetworkPackets.push_back(logicNetworkPacket);
					} else {
						bcUpdateFastLogicNetworkPackets.push_back(logicNetworkPacket);
					}
				} else {
					// multicast
					for (const auto& recipient: logicNetworkPacket.getRecipients()) {
						if (logicNetworkPacket.getSafe() == true) {
							mcUpdateSafeLogicNetworkPackets[recipient].push_back(logicNetworkPacket);
						} else {
							mcUpdateFastLogicNetworkPackets[recipient].push_back(logicNetworkPacket);
						}
					}
				}
			}
			networkLogic->getNetworkPackets().clear();
		}

		// colllect broadcast network packets for initialization
		if (newClients.size() > 0) {
			for (auto logic: context->getLogics()) {
				NetworkLogic* networkLogic = static_cast<NetworkLogic*>(logic);
				networkLogic->createInitialNetworkPackets();
				for (auto& logicNetworkPacket: networkLogic->getNetworkPackets()) {
					// set logic type id
					if (logicNetworkPacket.getLogicTypeId() == LogicNetworkPacket::LOGIC_TYPEID_NONE) {
						logicNetworkPacket.setLogicTypeId(networkLogic->getNetworkPacketTypeId());
					}
					// broadcast packets
					if (logicNetworkPacket.getRecipients().size() == 0) {
						if (logicNetworkPacket.getSafe() == true) {
							bcInitialSafeLogicNetworkPackets.push_back(logicNetworkPacket);
						} else {
							bcInitialFastLogicNetworkPackets.push_back(logicNetworkPacket);
						}
					} else {
						for (auto recipient: logicNetworkPacket.getRecipients()) {
							if (logicNetworkPacket.getSafe() == true) {
								mcInitialSafeLogicNetworkPackets[recipient].push_back(logicNetworkPacket);
							} else {
								mcInitialFastLogicNetworkPackets[recipient].push_back(logicNetworkPacket);
							}
						}
					}
				}
				networkLogic->getNetworkPackets().clear();
			}
		}

		//
		context->doneUpdateLogics();

		// done
		mutex.unlock();

		// send initial messages to new clients
		if (newClients.size() > 0) {
			// broad cast
			{
				// broadcast datagrams to send for initialization
				createDatagrams(bcInitialSafeLogicNetworkPackets, bcInitialFastLogicNetworkPackets, bcSendInitialPacketsSafe, bcSendInitialPacketsFast);
				if (VERBOSE_NETWORK == true && bcSendInitialPacketsSafe.size() > 0) {
					Console::println(
						"ServerThread::run(): initial: bc out: safe: " +
						to_string(bcSendInitialPacketsSafe.size()) + ": " +
						getLogicNetworkPacketsLogicTypes(bcInitialSafeLogicNetworkPackets)
					);
				}
				if (VERBOSE_NETWORK == true && bcSendInitialPacketsFast.size() > 0) {
					Console::println(
						"ServerThread::run(): initial: bc out: fast: " +
						to_string(bcSendInitialPacketsFast.size()) + ": " +
						getLogicNetworkPacketsLogicTypes(bcInitialFastLogicNetworkPackets)
					);
				}
				for (auto client: newClients) {
					for (auto packet: bcSendInitialPacketsSafe) client->send(packet, true, false);
					for (auto packet: bcSendInitialPacketsFast) client->send(packet, false, false);
				}
				for (auto packet: bcSendInitialPacketsSafe) delete packet;
				for (auto packet: bcSendInitialPacketsFast) delete packet;
				//
				bcSendInitialPacketsSafe.clear();
				bcSendInitialPacketsFast.clear();
			}
			{
				// multi cast
				for (auto client: newClients) {
					auto& mcInitialSafePacketsClient = mcInitialSafeLogicNetworkPackets[client->getKey()];
					auto& mcInitialFastPacketsClient = mcInitialFastLogicNetworkPackets[client->getKey()];
					createDatagrams(mcInitialSafePacketsClient, mcInitialFastPacketsClient, mcSendInitialPacketsSafe, mcSendInitialPacketsFast);
					if (VERBOSE_NETWORK == true && mcSendInitialPacketsSafe.size() > 0) {
						Console::println(
							"ServerThread::run(): initial: mc out: " +
							client->getKey() +
							": safe: " + to_string(mcSendInitialPacketsSafe.size()) + ": " +
							getLogicNetworkPacketsLogicTypes(mcInitialSafePacketsClient)
						);
					}
					if (VERBOSE_NETWORK == true && mcSendInitialPacketsFast.size() > 0) {
						Console::println(
							"ServerThread::run(): initial: mc out: " +
							client->getKey() +
							": fast: " + to_string(mcSendInitialPacketsFast.size()) + ": " +
							getLogicNetworkPacketsLogicTypes(mcInitialFastPacketsClient)
						);
					}
					for (auto packet: mcSendInitialPacketsSafe) client->send(packet, true);
					for (auto packet: mcSendInitialPacketsFast) client->send(packet, false);
					//
					mcSendInitialPacketsSafe.clear();
					mcSendInitialPacketsFast.clear();
				}
			}
		}

		// send messages to update clients
		{
			// broad cast
			{
				// broadcast datagrams to send for update
				createDatagrams(bcUpdateSafeLogicNetworkPackets, bcUpdateFastLogicNetworkPackets, bcSendUpdatePacketsSafe, bcSendUpdatePacketsFast);
				if (VERBOSE_NETWORK == true && bcSendUpdatePacketsSafe.size() > 0) {
					Console::println(
						"ServerThread::run(): bc out: safe: " +
						to_string(bcSendUpdatePacketsSafe.size()) + ": " +
						getLogicNetworkPacketsLogicTypes(bcUpdateSafeLogicNetworkPackets)
					);
				}
				if (VERBOSE_NETWORK == true && bcSendUpdatePacketsFast.size() > 0) {
					Console::println(
						"ServerThread::run(): bc out: fast: " +
						to_string(bcSendUpdatePacketsFast.size()) + ": " +
						getLogicNetworkPacketsLogicTypes(bcUpdateFastLogicNetworkPackets)
					);
				}
				for (auto client: updateClients) {
					for (auto packet: bcSendUpdatePacketsSafe) client->send(packet, true, false);
					for (auto packet: bcSendUpdatePacketsFast) client->send(packet, false, false);
				}
				for (auto packet: bcSendUpdatePacketsSafe) delete packet;
				for (auto packet: bcSendUpdatePacketsFast) delete packet;
				//
				bcSendUpdatePacketsSafe.clear();
				bcSendUpdatePacketsFast.clear();
			}
			// multi cast
			{
				for (auto client: clients) {
					auto& mcUpdateSafePacketsClient = mcUpdateSafeLogicNetworkPackets[client->getKey()];
					auto& mcUpdateFastPacketsClient = mcUpdateFastLogicNetworkPackets[client->getKey()];
					if (VERBOSE_NETWORK == true && mcSendUpdatePacketsSafe.size() > 0) {
						Console::println(
							"ServerThread::run(): mc out: " +
							client->getKey() + ": safe: " +
							to_string(mcSendUpdatePacketsSafe.size()) + ": " +
							getLogicNetworkPacketsLogicTypes(mcUpdateSafePacketsClient)
						);
					}
					if (VERBOSE_NETWORK == true && mcSendUpdatePacketsFast.size() > 0) {
						Console::println(
							"ServerThread::run(): mc out: " +
							client->getKey() + ": fast: " +
							": fast: " + to_string(mcSendUpdatePacketsFast.size()) + ": " +
							getLogicNetworkPacketsLogicTypes(mcUpdateFastPacketsClient)
						);
					}
					createDatagrams(mcUpdateSafePacketsClient, mcUpdateFastPacketsClient, mcSendUpdatePacketsSafe, mcSendUpdatePacketsFast);
					for (auto packet: mcSendUpdatePacketsSafe) client->send(packet, true);
					for (auto packet: mcSendUpdatePacketsFast) client->send(packet, false);
					//
					mcSendUpdatePacketsSafe.clear();
					mcSendUpdatePacketsFast.clear();
				}
			}
		}

		// release references
		for (auto client: clients) {
			client->releaseReference();
		}

		//
		clientNetworkPackets.clear();
		clients.clear();
		updateClients.clear();

		//
		mcUpdateSafeLogicNetworkPackets.clear();
		mcUpdateFastLogicNetworkPackets.clear();
		bcUpdateSafeLogicNetworkPackets.clear();
		bcUpdateFastLogicNetworkPackets.clear();
		mcInitialSafeLogicNetworkPackets.clear();
		mcInitialFastLogicNetworkPackets.clear();
		bcInitialSafeLogicNetworkPackets.clear();
		bcInitialFastLogicNetworkPackets.clear();

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

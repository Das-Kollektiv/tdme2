#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/ClientLogicThread.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/engine/logics/NetworkLogic.h>
#include <tdme/engine/physics/World.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/network/udpclient/UDPClient.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Time.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::logics::ClientLogicThread;
using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicNetworkPacket;
using tdme::engine::logics::NetworkLogic;
using tdme::engine::physics::World;
using tdme::network::udp::UDPPacket;
using tdme::network::udpclient::UDPClient;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::utilities::Console;
using tdme::utilities::Time;

ClientLogicThread::ClientLogicThread(Context* context, UDPClient* udpClient) : Thread("applicationserverclientthread", 4 * 1024 * 1024), mutex("applicationserverclientthread-mutex") {
	this->context = context;
	this->udpClient = udpClient;
}

Mutex* ClientLogicThread::getMutex() {
	return &mutex;
}

void ClientLogicThread::run() {
	Console::println("ClientLogicThread::run(): init");

	//
	int64_t timeLast = Time::getCurrentMillis();
	vector<LogicNetworkPacket> inGameNetworkPacketsUnhandled;
	while(isStopRequested() == false) {
		int64_t timeNow = Time::getCurrentMillis();
		vector<LogicNetworkPacket> inGameNetworkPackets;

		// push unhandlet packets to IN packets, display an warning if not handled for 1s
		for (auto& gameNetworkPacket: inGameNetworkPacketsUnhandled) {
			if (timeNow - gameNetworkPacket.getTime() > 1000L) {
				string gameLogicTypeIdString;
				gameLogicTypeIdString+= (char)((gameNetworkPacket.getGameLogicTypeId() >> 0) & 0xFF);
				gameLogicTypeIdString+= (char)((gameNetworkPacket.getGameLogicTypeId() >> 8) & 0xFF);
				gameLogicTypeIdString+= (char)((gameNetworkPacket.getGameLogicTypeId() >> 16) & 0xFF);
				gameLogicTypeIdString+= (char)((gameNetworkPacket.getGameLogicTypeId() >> 24) & 0xFF);
				Console::println("ClientLogicThread::run(): unhandled IN packet: 1s late: " + gameLogicTypeIdString);
				Console::println("Packet ASCII: ");
				for (auto i = 0; i < 255; i++) {
					Console::print(string() + (char)(gameNetworkPacket.getData()[i]));
				}
				Console::println("Packet ORD: ");
				for (auto i = 0; i < 255; i++) {
					Console::print(to_string(int(gameNetworkPacket.getData()[i])) + " ");
				}
				Console::println();
			}
			gameNetworkPacket.setReinjected();
			inGameNetworkPackets.push_back(gameNetworkPacket);
		}
		inGameNetworkPacketsUnhandled.clear();

		// get in packets
		mutex.lock();
		if (udpClient != nullptr) {
			UDPClientMessage* message = nullptr;
			while ((message = udpClient->receiveMessage()) != nullptr) {
				// get if safe message
				auto packet = message->getPacket();
				if (packet == nullptr) {
					delete message;
					continue;
				}
				// safe
				auto safe = packet->getBool();
				if (safe == true && udpClient->processSafeMessage(message) == false) {
					delete message;
					continue;
				}
				// Console::println("got packet safe: " + to_string(safe == 1));
				while (packet->getPosition() < UDPPacket::PACKET_MAX_SIZE - 17) {
					// size
					auto size = packet->getByte();
					// Console::println("got packet size " + to_string((int)size));
					// end of
					if (size == 0) break;
					// message logic type id
					auto gameLogicTypeId = packet->getInt();
					// Console::println(string("got packet logic ") + (char)gameLogicTypeId);
					// create network packet
					inGameNetworkPackets.push_back(
						LogicNetworkPacket(
							message->getMessageId(),
							safe,
							message->getRetryCount(),
							gameLogicTypeId,
							packet,
							size
						)
					);
				}
				delete message;
			}
		}

		//
		context->initGameLogics();

		// handle in packets
		handleInGameNetworkPackets(context->getGameLogics(), inGameNetworkPackets);

		// after handling network packets its possible that game logics have been added, handle in packets for those too
		while (true == true) {
			// get new game logics
			auto gameLogicsNew = context->getGameLogicsNew();

			// basically add new game logics to game logics
			auto gameLogicsAdded = context->addGameLogicsNew();
			if (gameLogicsAdded == 0) break;

			// run game logics new
			handleInGameNetworkPackets(gameLogicsNew, inGameNetworkPackets);
		}

		// update current game logics
		for (auto gameLogic: context->getGameLogics()) {
			gameLogic->updateGameLogic();
		}

		// handle in packets and do game logics for new game logics
		while (true == true) {
			// get new game logics
			auto gameLogicsNew = context->getGameLogicsNew();

			// add new game logics to game logics
			auto logicsAdded = context->addGameLogicsNew();
			if (logicsAdded == 0) break;

			// run game logics new
			handleInGameNetworkPackets(gameLogicsNew, inGameNetworkPackets);

			// run game logics for new game logics
			for (auto gameLogic: gameLogicsNew) gameLogic->updateGameLogic();
		}

		//	fire on game logics processed for game logics
		for (auto gameLogic: context->getGameLogics()) {
			gameLogic->onGameLogicsProcessed();
		}

		//
		context->doneGameLogics();

		// check if there are in packets that have not yet been processed
		for (auto& packet: inGameNetworkPackets) {
			if (packet.isProcessed() == false) {
				inGameNetworkPacketsUnhandled.push_back(packet);
			}
		}

		// network sending
		if (udpClient == nullptr) {
			//	done
			mutex.unlock();

			// We have no UDP client, so just clear outgoing packages
			for (auto gameLogic: context->getGameLogics()) {
				NetworkLogic* gameLogicNetwork = dynamic_cast<NetworkLogic*>(gameLogic);
				if (gameLogicNetwork != nullptr) {
					gameLogicNetwork->getNetworkPackets().clear();
				}
			}
		} else {
			// We have a UDP client, so send packages
			vector<LogicNetworkPacket> safeGameNetworkPackets;
			vector<LogicNetworkPacket> fastGameNetworkPackets;
			for (auto gameLogic: context->getGameLogics()) {
				NetworkLogic* gameLogicNetwork = dynamic_cast<NetworkLogic*>(gameLogic);
				if (gameLogicNetwork != nullptr) {
					for (auto& gameNetworkPacket: gameLogicNetwork->getNetworkPackets()) {
						if (gameNetworkPacket.getGameLogicTypeId() == LogicNetworkPacket::GAMELOGIC_TYPEID_NONE) {
							gameNetworkPacket.setGameLogicTypeId(gameLogicNetwork->getNetworkPacketTypeId());
						}
						if (gameNetworkPacket.getSafe() == true) {
							safeGameNetworkPackets.push_back(gameNetworkPacket);
						} else {
							fastGameNetworkPackets.push_back(gameNetworkPacket);
						}
					}
					gameLogicNetwork->getNetworkPackets().clear();
				}
			}
			//	done
			mutex.unlock();

			// send safe messages
			{
				auto udpClientPacket = new UDPPacket();
				// safe
				udpClientPacket->putBool(true);
				//
				for (auto& safeGameNetworkPacket: safeGameNetworkPackets) {
					// size
					auto size = safeGameNetworkPacket.getPosition();
					// datagram size
					auto datagramSize = udpClientPacket->getSize();
					//
					if (datagramSize + 2 + (uint16_t)size > UDPPacket::PACKET_MAX_SIZE - 17) {
						if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 17) {
							// no more game network packets, size = 0
							udpClientPacket->putByte(0);
						}
						udpClient->sendMessage(udpClient->createMessage(udpClientPacket), true);
						udpClientPacket = new UDPPacket();
						// safe
						udpClientPacket->putBool(true);
					}
					// size
					udpClientPacket->putByte(size);
					// game logic type id
					udpClientPacket->putInt(safeGameNetworkPacket.getGameLogicTypeId());
					// payload
					udpClientPacket->putBytes(safeGameNetworkPacket.getData(), safeGameNetworkPacket.getPosition());
				}
				// datagram size
				auto datagramSize = udpClientPacket->getSize();
				if (datagramSize > 1) {
					if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 17) {
						// no more game network packets, size = 0
						udpClientPacket->putByte(0);
					}
					udpClient->sendMessage(udpClient->createMessage(udpClientPacket), true);
				} else {
					delete udpClientPacket;
				}
			}
			// send fast messages
			{
				auto udpClientPacket = new UDPPacket();
				// safe
				udpClientPacket->putBool(false);
				//
				for (auto& fastGameNetworkPacket: fastGameNetworkPackets) {
					// size
					auto size = fastGameNetworkPacket.getPosition();
					// datagram size
					auto datagramSize = udpClientPacket->getSize();
					if (datagramSize + 2 + (uint16_t)size > UDPPacket::PACKET_MAX_SIZE - 17) {
						if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 17) {
							// no more game network packets, size = 0
							udpClientPacket->putByte(0);
						}
						udpClient->sendMessage(udpClient->createMessage(udpClientPacket), true);
						udpClientPacket = new UDPPacket();
						// safe
						udpClientPacket->putBool(false);
					}
					// size
					udpClientPacket->putByte(size);
					// gmae logic type id
					udpClientPacket->putInt(fastGameNetworkPacket.getGameLogicTypeId());
					// payload
					udpClientPacket->putBytes(fastGameNetworkPacket.getData(), fastGameNetworkPacket.getPosition());
				}
				// datagram size
				auto datagramSize = udpClientPacket->getSize();
				if (datagramSize > 1) {
					if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 17) {
						// no more game network packets, size = 0
						udpClientPacket->putByte(0);
					}
					udpClient->sendMessage(udpClient->createMessage(udpClientPacket), true);
				} else {
					delete udpClientPacket;
				}
			}
		}

		// get some rest
		int64_t timeDelta = Time::getCurrentMillis() - timeLast;
		if (timeDelta > 33) {
			Console::println("ClientLogicThread::run(): time delta < 33FPS, it took " + to_string(timeDelta) + " ms to compute");
			timeDelta = 33;
		} else
		if (timeDelta < 16) {
			timeDelta = 16;
		}
		// update world if context is initialized
		if (context->isInitialized() == true) {
			context->getWorld()->update(timeDelta / 1000.0f);
		}
		timeDelta = Time::getCurrentMillis() - timeLast;
		if (timeDelta < 16) {
			Thread::sleep(16 - timeDelta);
		}
		timeLast = Time::getCurrentMillis();
	}

	//
	Console::println("ClientLogicThread::run(): done");
}

void ClientLogicThread::handleInGameNetworkPackets(const vector<Logic*>& gameLogics, vector<LogicNetworkPacket>& inGameNetworkPackets) {
	for (auto& gameNetworkPacket: inGameNetworkPackets) {
		for (auto gameLogic: gameLogics) {
			NetworkLogic* gameLogicNetwork = dynamic_cast<NetworkLogic*>(gameLogic);
			if (gameLogicNetwork != nullptr) {
				if (gameLogicNetwork->getNetworkPacketTypeId() == gameNetworkPacket.getGameLogicTypeId()) {
					gameNetworkPacket.reset();
					gameLogicNetwork->handleNetworkPacket(gameNetworkPacket);
				}
			}
		}
	}
}

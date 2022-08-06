#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/ApplicationClient.h>
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

using tdme::engine::logics::ApplicationClient;
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

ApplicationClient::ApplicationClient(Context* context, UDPClient* udpClient) : Thread("applicationserverclientthread", 4 * 1024 * 1024), mutex("applicationserverclientthread-mutex") {
	this->context = context;
	this->udpClient = udpClient;
	this->context->setLogicsMutex(getMutex());
}

Mutex* ApplicationClient::getMutex() {
	return &mutex;
}

void ApplicationClient::run() {
	Console::println("ApplicationClient::run(): init");

	//
	int64_t timeLast = Time::getCurrentMillis();
	vector<LogicNetworkPacket> inLogicsNetworkPacketsUnhandled;
	while(isStopRequested() == false) {
		int64_t timeNow = Time::getCurrentMillis();
		vector<LogicNetworkPacket> inNetworkPackets;

		// push unhandlet packets to IN packets, display an warning if not handled for 1s
		for (auto& logicNetworkPacket: inLogicsNetworkPacketsUnhandled) {
			if (timeNow - logicNetworkPacket.getTime() > 1000L) {
				string logicTypeIdString;
				logicTypeIdString+= (char)((logicNetworkPacket.getLogicTypeId() >> 0) & 0xFF);
				logicTypeIdString+= (char)((logicNetworkPacket.getLogicTypeId() >> 8) & 0xFF);
				logicTypeIdString+= (char)((logicNetworkPacket.getLogicTypeId() >> 16) & 0xFF);
				logicTypeIdString+= (char)((logicNetworkPacket.getLogicTypeId() >> 24) & 0xFF);
				Console::println("ApplicationClient::run(): unhandled IN packet: 1s late: " + logicTypeIdString);
				Console::println("Packet ASCII: ");
				for (auto i = 0; i < 255; i++) {
					Console::print(string() + (char)(logicNetworkPacket.getData()[i]));
				}
				Console::println("Packet ORD: ");
				for (auto i = 0; i < 255; i++) {
					Console::print(to_string(int(logicNetworkPacket.getData()[i])) + " ");
				}
				Console::println();
			}
			logicNetworkPacket.setReinjected();
			inNetworkPackets.push_back(logicNetworkPacket);
		}
		inLogicsNetworkPacketsUnhandled.clear();

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
					auto logicTypeId = packet->getInt();
					// Console::println(string("got packet logic ") + (char)logicTypeId);
					// create network packet
					inNetworkPackets.push_back(
						LogicNetworkPacket(
							message->getMessageId(),
							safe,
							message->getRetryCount(),
							logicTypeId,
							packet,
							size
						)
					);
				}
				delete message;
			}
		}

		//
		context->initUpdateLogics();

		// handle in packets
		handleInNetworkPackets(context->getLogics(), inNetworkPackets);

		// after handling network packets its possible that logics have been added, handle in packets for those too
		while (true == true) {
			// get new logics
			auto newLogics = context->getNewLogics();

			// basically add new logics to logics
			auto addedLogics = context->addNewLogics();
			if (addedLogics == 0) break;

			// handle in network packets for new logics
			handleInNetworkPackets(newLogics, inNetworkPackets);
		}

		// update current logics
		for (auto logic: context->getLogics()) {
			logic->updateLogic();
		}

		// handle in packets and do logics for new logics
		while (true == true) {
			// get new logics
			auto newLogics = context->getNewLogics();

			// add new logics to logics
			auto addedLogics = context->addNewLogics();
			if (addedLogics == 0) break;

			// run logics new
			handleInNetworkPackets(newLogics, inNetworkPackets);

			// run new logics
			for (auto newLogic: newLogics) newLogic->updateLogic();
		}

		//	fire on logics processed for game logics
		for (auto logic: context->getLogics()) {
			logic->onLogicsProcessed();
		}

		//
		context->doneUpdateLogics();

		// check if there are in packets that have not yet been processed
		for (auto& packet: inNetworkPackets) {
			if (packet.isProcessed() == false) {
				inLogicsNetworkPacketsUnhandled.push_back(packet);
			}
		}

		// network sending
		if (udpClient == nullptr) {
			//	done
			mutex.unlock();

			// We have no UDP client, so just clear outgoing packages
			for (auto logic: context->getLogics()) {
				NetworkLogic* networkLogic = dynamic_cast<NetworkLogic*>(logic);
				if (networkLogic != nullptr) {
					networkLogic->getNetworkPackets().clear();
				}
			}
		} else {
			// We have a UDP client, so send packages
			// TODO: reuse this vectors
			vector<LogicNetworkPacket> safeLogicNetworkPackets;
			vector<LogicNetworkPacket> fastLogicNetworkPackets;
			for (auto logic: context->getLogics()) {
				NetworkLogic* networkLogic = dynamic_cast<NetworkLogic*>(logic);
				if (networkLogic != nullptr) {
					for (auto& logicNetworkPacket: networkLogic->getNetworkPackets()) {
						if (logicNetworkPacket.getLogicTypeId() == LogicNetworkPacket::LOGIC_TYPEID_NONE) {
							logicNetworkPacket.setLogicTypeId(networkLogic->getNetworkPacketTypeId());
						}
						if (logicNetworkPacket.getSafe() == true) {
							safeLogicNetworkPackets.push_back(logicNetworkPacket);
						} else {
							fastLogicNetworkPackets.push_back(logicNetworkPacket);
						}
					}
					networkLogic->getNetworkPackets().clear();
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
				for (auto& safeNetworkPacket: safeLogicNetworkPackets) {
					// size
					auto size = safeNetworkPacket.getPosition();
					// datagram size
					auto datagramSize = udpClientPacket->getSize();
					//
					if (datagramSize + 2 + (uint16_t)size > UDPPacket::PACKET_MAX_SIZE - 17) {
						if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 17) {
							// no more network packets, size = 0
							udpClientPacket->putByte(0);
						}
						udpClient->sendMessage(udpClient->createMessage(udpClientPacket), true);
						udpClientPacket = new UDPPacket();
						// safe
						udpClientPacket->putBool(true);
					}
					// size
					udpClientPacket->putByte(size);
					// logic type id
					udpClientPacket->putInt(safeNetworkPacket.getLogicTypeId());
					// payload
					udpClientPacket->putBytes(safeNetworkPacket.getData(), safeNetworkPacket.getPosition());
				}
				// datagram size
				auto datagramSize = udpClientPacket->getSize();
				if (datagramSize > 1) {
					if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 17) {
						// no more network packets, size = 0
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
				for (auto& fastNetworkPacket: fastLogicNetworkPackets) {
					// size
					auto size = fastNetworkPacket.getPosition();
					// datagram size
					auto datagramSize = udpClientPacket->getSize();
					if (datagramSize + 2 + (uint16_t)size > UDPPacket::PACKET_MAX_SIZE - 17) {
						if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 17) {
							// no more network packets, size = 0
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
					udpClientPacket->putInt(fastNetworkPacket.getLogicTypeId());
					// payload
					udpClientPacket->putBytes(fastNetworkPacket.getData(), fastNetworkPacket.getPosition());
				}
				// datagram size
				auto datagramSize = udpClientPacket->getSize();
				if (datagramSize > 1) {
					if (datagramSize < UDPPacket::PACKET_MAX_SIZE - 17) {
						// no more network packets, size = 0
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
			Console::println("ApplicationClient::run(): time delta < 33FPS, it took " + to_string(timeDelta) + " ms to compute");
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
	Console::println("ApplicationClient::run(): done");
}

void ApplicationClient::handleInNetworkPackets(const vector<Logic*>& logics, vector<LogicNetworkPacket>& inLogicNetworkPackets) {
	// TODO: improve me
	for (auto& logicNetworkPacket: inLogicNetworkPackets) {
		for (auto logic: logics) {
			NetworkLogic* networkLogic = dynamic_cast<NetworkLogic*>(logic);
			if (networkLogic != nullptr) {
				if (networkLogic->getNetworkPacketTypeId() == logicNetworkPacket.getLogicTypeId()) {
					logicNetworkPacket.reset();
					networkLogic->handleNetworkPacket(logicNetworkPacket);
				}
			}
		}
	}
}

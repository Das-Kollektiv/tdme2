#include <tdme/engine/logics/ApplicationServerClient.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/UDPServer.h>
#include <yannet/network/udpserver/UDPServerClient.h>

using std::endl;
using std::string;
using std::to_string;
using std::vector;

using tdme::engine::logics::LogicNetworkPacket;
using tdme::utilities::Console;
using tdme::utilities::Exception;

using yannet::network::udp::UDPPacket;
using yannet::network::udpserver::UDPServer;
using yannet::network::udpserver::UDPServerClient;

using tdme::engine::logics::ApplicationServerClient;

ApplicationServerClient::ApplicationServerClient(const uint32_t clientId, const string& ip, const unsigned int port) :
	UDPServerClient(clientId, ip, port), networkPacketsMutex("wsserverclient-networkpacketsmutex") {
}

ApplicationServerClient::~ApplicationServerClient() {
	Console::printLine("ApplicationServerClient::~ApplicationServerClient()");
}

void ApplicationServerClient::onRequest(const UDPPacket* packet, const uint32_t messageId, const uint8_t retries) {
	// check if safe message
	auto safe = packet->getBool();
	if (safe == true && processSafeMessage(messageId) == false) {
		return;
	}
	//
	networkPacketsMutex.lock();
	// while having datas
	while (packet->getPosition() < UDPPacket::PACKET_MAX_SIZE) {
		auto size = packet->getByte();
		// end of
		if (size == 0) break;
		// game logic type id
		auto logicTypeId = packet->getInt();
		// create network packet
		LogicNetworkPacket logicNetworkPacket(
			messageId,
			safe,
			retries,
			logicTypeId,
			packet,
			size
		);
		logicNetworkPacket.setSender(getKey());
		networkPackets.push_back(logicNetworkPacket);
	}
	networkPacketsMutex.unlock();
}

void ApplicationServerClient::onInit() {
	Console::printLine("Initiated connection with '" + getIp() + ":" + to_string(getPort()) + "', sending key");
}

void ApplicationServerClient::onClose() {
	Console::printLine("Closed connection with '" + getIp() + ":" + to_string(getPort()) + "'");
}

void ApplicationServerClient::onCustom(const string& type) {
	Console::printLine("Custom event '" + type + "' with '" + getIp() + ":" + to_string(getPort()) + "'");
}

Mutex& ApplicationServerClient::getNetworkPacketsMutex() {
	return networkPacketsMutex;
}

vector<LogicNetworkPacket>& ApplicationServerClient::getNetworkPackets() {
	return networkPackets;
}

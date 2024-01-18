#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Context.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/engine/logics/NetworkLogic.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicNetworkPacket;
using tdme::engine::logics::NetworkLogic;
using tdme::utilities::Console;

NetworkLogic::NetworkLogic(Context* context, const string& id, bool handlingHIDInput): Logic(context, id, handlingHIDInput) {
}

bool NetworkLogic::isHandlingNetworkInput() {
	return true;
}

void NetworkLogic::setSynchedFromNetwork() {
	synchedFromNetwork = true;
}

bool NetworkLogic::isSynchedFromNetwork() {
	if (synchedFromNetwork == true) {
		synchedFromNetwork = false;
		return true;
	} else {
		return false;
	}
}

bool NetworkLogic::isServer() {
	return context->isServer();
}

vector<LogicNetworkPacket>& NetworkLogic::getNetworkPackets() {
	return networkPackets;
}

void NetworkLogic::sendNetworkPacket(LogicNetworkPacket& packet) {
	if (networkPackets.size() == 50) {
		Console::printLine("NetworkLogic::sendNetworkPacket(): 50 packets: Too many packets!");
	}
	networkPackets.push_back(packet);
}

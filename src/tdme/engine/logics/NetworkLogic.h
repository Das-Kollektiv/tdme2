#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>

using std::string;
using std::vector;

using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicNetworkPacket;

/**
 * Network Logic
 * @author Andreas Drewke
 */
class tdme::engine::logics::NetworkLogic: public Logic {
public:
	// forbid class copy
	FORBID_CLASS_COPY(NetworkLogic)

	/**
	 * Public constructor
	 * @param context context
	 * @param id id
	 * @param handlingHIDInput handling hid input
	 */
	NetworkLogic(Context* context, const string& id, bool handlingHIDInput);

	/**
	 * @return is handling network input
	 */
	virtual bool isHandlingNetworkInput();

	/**
	 * @return network packet type id
	 */
	virtual uint32_t getNetworkPacketTypeId() = 0;

	/**
	 * Set that this entity has been synched from network
	 */
	void setSynchedFromNetwork();

	/**
	 * @return if entity have been synched from network, will be reset in call
	 */
	bool isSynchedFromNetwork();

	/**
	 * @return is server
	 */
	bool isServer();

	/**
	 * Handle network packet
	 * @param packet message
	 */
	virtual void handleNetworkPacket(LogicNetworkPacket& packet) = 0;

	/**
	 * Get outgoing network packets
	 * @return network packets
	 */
	vector<LogicNetworkPacket>& getNetworkPackets();

	/**
	 * Send network packet
	 * @param packet packet
	 */
	void sendNetworkPacket(LogicNetworkPacket& packet);

	/**
	 * Send network packet for initialization
	 * 	Note: This is server only for now
	 */
	virtual void createInitialNetworkPackets() = 0;

private:
	bool synchedFromNetwork { false };
	vector<LogicNetworkPacket> networkPackets;
};

#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/physics/World.h>
#include <tdme/network/udpclient/UDPClient.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>

using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::physics::World;
using tdme::network::udpclient::UDPClient;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;

/**
 * Application client
 * @author Andreas Drewke
 */
class tdme::engine::logics::ApplicationClient: public Thread {
public:
	/**
	 * Public constructor
	 * @param context context
	 * @param udpClient UDP client
	 */
	ApplicationClient(Context* context, UDPClient* udpClient = nullptr);

	/**
	 * @return mutex
	 */
	Mutex* getMutex();

	// overridden methods
	virtual void run() override;

private:

	/**
	 * Handle in logic network packets
	 * @param logics logics
	 * @param inGameNetworkPackets incoming logic network packets
	 */
	void handleInNetworkPackets(const vector<Logic*>& logics, vector<LogicNetworkPacket>& inLogicNetworkPackets);

private:
	Context* context { nullptr };
	Mutex mutex;
	UDPClient* udpClient { nullptr };
};

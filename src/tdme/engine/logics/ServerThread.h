#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/network/udp/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>

using std::string;
using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::logics::ApplicationServer;
using tdme::network::udp::UDPPacket;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;

/**
 * Application server game logic thread
 * @author Andreas Drewke
 */
class tdme::engine::logics::ServerThread: public Thread {
public:
	/**
	 * Public constructor
	 * @param context world
	 * @param server server
	 */
	ServerThread(Context* context, ApplicationServer* server);

	/**
	 * @return mutex
	 */
	Mutex* getMutex();

	/**
	 * Create datagrams
	 * @param safeGameNetworkPackets safe game network packets
	 * @param fastGameNetworkPackets fast game network packets
	 * @param sendPacketsSafe send packets safe
	 * @param sendPacketsFast send packets fast
	 */
	void createDatagrams(vector<LogicNetworkPacket>& safeGameNetworkPackets, vector<LogicNetworkPacket>& fastGameNetworkPackets, vector<UDPPacket*>& sendPacketsSafe, vector<UDPPacket*>& sendPacketsFast);

	// overrided methods
	virtual void run() override;

private:
	static constexpr int32_t VERBOSE_NETWORK { false };

	Context* context { nullptr };
	ApplicationServer* server { nullptr };
	Mutex mutex;

	/**
	 * Get network packets game logic types
	 * @param gameNetworkPackets game network packets
	 * @return network packet logics string
	 */
	string getNetworkPacketGameLogicTypes(vector<LogicNetworkPacket>& gameNetworkPackets);
};

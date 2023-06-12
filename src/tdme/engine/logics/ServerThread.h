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

using tdme::engine::logics::ApplicationServer;
using tdme::engine::logics::Context;
using tdme::network::udp::UDPPacket;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;

/**
 * Application server thread
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

private:
	static constexpr int32_t VERBOSE_NETWORK { false };

	Context* context { nullptr };
	ApplicationServer* server { nullptr };
	Mutex mutex;

	// overridden methods
	virtual void run() override;

	/**
	 * Create datagrams
	 * @param safeLogicNetworkPackets safe logic network packets
	 * @param fastLogicNetworkPackets fast logic network packets
	 * @param sendPacketsSafe send packets safe
	 * @param sendPacketsFast send packets fast
	 */
	void createDatagrams(vector<LogicNetworkPacket>& safeLogicNetworkPackets, vector<LogicNetworkPacket>& fastLogicNetworkPackets, vector<UDPPacket*>& sendPacketsSafe, vector<UDPPacket*>& sendPacketsFast);

	/**
	 * Get network packets game logic types
	 * @param logicNetworkPackets logic network packets
	 * @return network packet logics string
	 */
	const string getLogicNetworkPacketsLogicTypes(vector<LogicNetworkPacket>& logicNetworkPackets);
};

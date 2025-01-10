#pragma once

#include <memory>
#include <queue>
#include <unordered_map>

#include <yannet/network/udpserver/fwd-yannet.h>

#include <yannet/yannet.h>
#include <yannet/os/network/KernelEventMechanism.h>
#include <yannet/os/network/UDPSocket.h>
#include <yannet/os/threading/Barrier.h>
#include <yannet/os/threading/Mutex.h>
#include <yannet/os/threading/Thread.h>

#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/UDPServer.h>
#include <yannet/network/udpserver/UDPServerClient.h>

using std::queue;
using std::unique_ptr;
using std::unordered_map;

// namespaces
namespace yannet {
namespace network {
namespace udpserver {
	using ::yannet::network::udp::UDPPacket;
	using ::yannet::os::network::KernelEventMechanism;
	using ::yannet::os::network::UDPSocket;
	using ::yannet::os::threading::Barrier;
	using ::yannet::os::threading::Mutex;
	using ::yannet::os::threading::Thread;
}
}
}

/**
 * UDP Network server IO thread
 * @author Andreas Drewke
 */
class yannet::network::udpserver::UDPServerIOThread final: private Thread {
	friend class UDPServer;
	friend class UDPServerClient;

private:
	const static int MESSAGEACK_RESENDTIMES_TRIES = 7;
	STATIC_DLL_IMPEXT const static uint64_t MESSAGEACK_RESENDTIMES[MESSAGEACK_RESENDTIMES_TRIES];
	const static int MESSAGEQUEUE_SEND_BATCH_SIZE = 100;
	const static uint64_t MESSAGEACK_KEEPTIME = 5000L;
	struct Message {
		string ip;
		unsigned int port;
		uint64_t time;
		uint8_t messageType;
		uint32_t clientId;
		uint32_t messageId;
		uint8_t retries;
		char message[512];
		uint16_t bytes;
	};
	typedef queue<Message*> MessageQueue;
	typedef unordered_map<uint32_t, Message*> MessageMapAck;
	Barrier* startUpBarrier;

public:
	// forbid class copy
	FORBID_CLASS_COPY(UDPServerIOThread)

	/**
	 * @brief public constructor should be called in TCPServer
	 * @param id id
	 * @param *server server
	 * @param maxCCU max ccu
	 * @param startUpBarrier start up barrier
	 */
	UDPServerIOThread(const unsigned int id, UDPServer *server, const unsigned int maxCCU, Barrier* startUpBarrier);

	/**
	 * @brief Destructor
	 */
	~UDPServerIOThread();

	/**
	 * @brief thread program
	 */
	virtual void run();

	/**
	 * @brief pushes a message to be send, takes over ownership of frame
	 * @param client client
	 * @param messageType message type
	 * @param messageId message id
	 * @param packet packet to be send
	 * @param safe safe, requires ack and retransmission
	 * @param deletePacket delete packet
	 * @throws tdme::network::udpserver::NetworkServerException
	 */
	void sendMessage(const UDPServerClient* client, const uint8_t messageType, const uint32_t messageId, const UDPPacket* packet, const bool safe, const bool deletePacket);

	/**
	 * @brief Processes an acknowlegdement reception
	 * @param client client
	 * @param messageId message id
	 * @throws tdme::network::udpserver::NetworkServerException
	 */
	void processAckReceived(UDPServerClient* client, const uint32_t messageId);

	/**
	 * @brief Clean up timed out safe messages, reissue messages not beeing acknowlegded from client
	 */
	void processAckMessages();

	//
	unsigned int id;
	UDPServer* server;
	unsigned int maxCCU;
	KernelEventMechanism kem;

	Mutex messageQueueMutex;
	MessageQueue messageQueue;

	Mutex messageMapAckMutex;
	MessageMapAck messageMapAck;

	unique_ptr<UDPSocket> socket;
};


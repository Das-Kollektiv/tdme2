#pragma once

#include <stdint.h>

#include <queue>
#include <map>
#include <set>
#include <utility>

#include <tdme/network/udpserver/fwd-tdme.h>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/network/KernelEventMechanism.h>
#include <tdme/os/network/NIOUDPSocket.h>

#include <tdme/network/udpserver/NIOUDPServer.h>
#include <tdme/network/udpserver/NIOUDPServerClient.h>

using std::queue;
using std::map;

using tdme::os::threading::Thread;
using tdme::os::threading::Mutex;
using tdme::os::network::KernelEventMechanism;
using tdme::os::network::NIOUDPSocket;
using tdme::network::udpserver::NIOUDPServer;
using tdme::network::udpserver::NIOUDPServerClient;

/**
 * NIO network server udp IO thread
 * @author Andreas Drewke
 */
class tdme::network::udpserver::NIOUDPServerIOThread : private Thread {
	friend class NIOUDPServer;
	friend class NIOUDPServerClient;

private:
	const static int MESSAGEACK_RESENDTIMES_TRIES = 7;
	const static uint64_t MESSAGEACK_RESENDTIMES[MESSAGEACK_RESENDTIMES_TRIES];
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
		size_t bytes;
	};
	typedef queue<Message> MessageQueue;
	typedef map<uint32_t, Message> MessageMapAck;

	/**
	 * @brief public constructor should be called in NIOTCPServer
	 * @param id id
	 * @param *server server
	 * @param maxCCU max ccu
	 */
	NIOUDPServerIOThread(const unsigned int id, NIOUDPServer *server, const unsigned int maxCCU);

	/**
	 * @brief thread program
	 */
	virtual void run();

	/**
	 * @brief pushes a message to be send, takes over ownership of frame
	 * @param client client
	 * @param messageType message type
	 * @param messageId message id
	 * @param frame frame to be send
	 * @param safe safe, requires ack and retransmission
	 * @param deleteFrame delete frame
	 * @throws NIONetworkServerException
	 */
	void sendMessage(const NIOUDPServerClient* client, const uint8_t messageType, const uint32_t messageId, stringstream* frame, const bool safe, const bool deleteFrame) throw (NIONetworkServerException);

	/**
	 * @brief Processes an acknowlegdement reception
	 * @param client client
	 * @param messageId message id
	 */
	void processAckReceived(NIOUDPServerClient* client, const uint32_t messageId) throw (NIONetworkServerException);

	/**
	 * @brief Clean up timed out safe messages, reissue messages not beeing acknowlegded from client
	 */
	void processAckMessages();

	//
	unsigned int id;
	NIOUDPServer* server;
	unsigned int maxCCU;
	KernelEventMechanism kem;

	Mutex messageQueueMutex;
	MessageQueue messageQueue;

	Mutex messageMapAckMutex;
	MessageMapAck messageMapAck;

	NIOUDPSocket socket;
};


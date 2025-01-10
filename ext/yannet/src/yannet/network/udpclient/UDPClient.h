#pragma once

#if defined(_WIN32) && defined(_MSC_VER)
	#define ssize_t int
#endif

#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

#include <yannet/yannet.h>
#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpclient/fwd-yannet.h>
#include <yannet/network/udpclient/NetworkClientException.h>
#include <yannet/network/udpclient/UDPClientMessage.h>
#include <yannet/os/network/KernelEventMechanism.h>
#include <yannet/os/network/UDPSocket.h>
#include <yannet/os/threading/Mutex.h>
#include <yannet/os/threading/Thread.h>

using std::unique_ptr;
using std::queue;
using std::string;
using std::unordered_map;

// namespaces
namespace yannet {
namespace network {
namespace udpclient {
	using ::yannet::os::network::KernelEventMechanism;
	using ::yannet::os::network::UDPSocket;
	using ::yannet::os::threading::Mutex;
	using ::yannet::os::threading::Thread;
	using ::yannet::network::udp::UDPPacket;
}
}
}

/**
 * UDP client
 * @author Andreas Drewke
 */
class yannet::network::udpclient::UDPClient final: public Thread {
public:
	struct UDPClient_Statistics {
		int64_t time { -1LL };
		uint32_t received { 0 };
		uint32_t sent { 0 };
		uint32_t errors { 0 };
	};

	/**
	 * Get retry time for given retry count
	 * @param retries retry count
	 * @return approximatly retry time in ms
	 */
	inline static uint64_t getRetryTime(const uint8_t retries) {
		if (retries == 0) return 0L;
		if (retries > UDPClient::MESSAGEACK_RESENDTIMES_TRIES) return 0L;
		return UDPClient::MESSAGEACK_RESENDTIMES[retries - 1];
	}

	// forbid class copy
	FORBID_CLASS_COPY(UDPClient)

	/**
	 * Public constructor
	 * @param ip server ip
	 * @param port server port
	 */
	UDPClient(const string& ip, const uint16_t port);

	/**
	 * Destructor
	 */
	~UDPClient();

	/**
	 * @return initialized
	 */
	inline bool isInitialized() {
		return initialized;
	}

	/**
	 * @return initialized
	 */
	inline bool isConnected() {
		return connected;
	}

	/**
	 * @return server ip
	 */
	inline const string& getIp() {
		return ip;
	}

	/**
	 * @return server port
	 */
	inline const unsigned int getPort() {
		return port;
	}

	/**
	 * @return client key
	 */
	inline const string& getClientKey() {
		return clientKey;
	}

	/**
	 * Set client key
	 * @param clientKey client key
	 */
	inline void setClientKey(const string& clientKey) {
		this->clientKey = clientKey;
	}

	/**
	 * Returns if a message should be processed or already have been processed
	 * @param clientMessage client message
	 * @return if message should be processed or not
	 * @throws tdme::network::udpclient::NetworkClientException
	 */
	bool processSafeMessage(UDPClientMessage* clientMessage);

	/**
	 * Receive message
	 * @return message or nullptr, needs to be deleted after processing
	 */
	UDPClientMessage* receiveMessage();

	/**
	 * Pushes a message to be send, takes over ownership of message
	 * @param clientMessage client message object
	 * @param safe safe
	 * @throws tdme::network::udpclient::NetworkClientException
	 */
	void sendMessage(UDPClientMessage* clientMessage, bool safe);

	/**
	 * Create message
	 * @param packet UDP client packet
	 */
	UDPClientMessage* createMessage(const UDPPacket* packet);

	/**
	 * @returns UDP client statistics
	 */
	const UDPClient_Statistics getStatistics();

private:
	/**
	 * Run thread program
	 */
	virtual void run();

	/**
	 * Processes ack reveived
	 * @param messageId message id
	 * @throws tdme::network::udpclient::NetworkClientException
	 */
	void processAckReceived(const uint32_t messageId);

	/**
	 * Process ack messages
	 */
	void processAckMessages();

	/**
	 * Clean up safe messages
	 */
	void cleanUpSafeMessages();

	//
	bool initialized;
	bool connected;
	string ip;
	uint16_t port;
	uint32_t clientId;
	uint32_t messageCount;
	string clientKey;

	const static int MESSAGEACK_RESENDTIMES_TRIES = 7;
	STATIC_DLL_IMPEXT const static uint64_t MESSAGEACK_RESENDTIMES[MESSAGEACK_RESENDTIMES_TRIES];
	const static int MESSAGEQUEUE_SEND_BATCH_SIZE = 100;
	const static uint64_t MESSAGEACK_KEEPTIME = 5000L;
	struct Message {
		uint64_t time;
		uint8_t messageType;
		uint32_t messageId;
		uint8_t retries;
		char message[512];
		uint16_t bytes;
	};
	typedef queue<Message*> MessageQueue;
	typedef unordered_map<uint32_t, Message*> MessageMapAck;
	typedef queue<UDPClientMessage*> RecvMessageQueue;

	static const uint64_t MESSAGESSAFE_KEEPTIME = 5000L;
	struct SafeMessage {
		uint32_t messageId;
		uint64_t time;
		uint8_t receptions;
	};
	typedef unordered_map<uint32_t, SafeMessage*> MessageMapSafe;


	KernelEventMechanism kem;

	Mutex messageQueueMutex;
	MessageQueue messageQueue;

	Mutex messageMapAckMutex;
	MessageMapAck messageMapAck;

	Mutex recvMessageQueueMutex;
	RecvMessageQueue recvMessageQueue;

	Mutex messageMapSafeMutex;
	MessageMapSafe messageMapSafe;

	unique_ptr<UDPSocket> socket;

	UDPClient_Statistics statistics;
};


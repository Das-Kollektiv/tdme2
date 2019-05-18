#pragma once

#if defined(_WIN32) && defined(_MSC_VER)
	#define ssize_t int
#endif

#include <stdint.h>

#include <queue>
#include <map>

#include <tdme/tdme.h>
#include <tdme/network/udpclient/fwd-tdme.h>
#include <tdme/network/udpclient/NIOClientException.h>
#include <tdme/network/udpclient/NIOUDPClientMessage.h>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/network/KernelEventMechanism.h>
#include <tdme/os/network/NIOUDPSocket.h>

using std::string;
using std::queue;
using std::map;

using tdme::os::threading::Thread;
using tdme::os::threading::Mutex;
using tdme::os::network::KernelEventMechanism;
using tdme::os::network::NIOUDPSocket;

using tdme::network::udpclient::NIOClientException;
using tdme::network::udpclient::NIOUDPClientMessage;

/**
 * NIO UDP client
 * @author Andreas Drewke
 */
class tdme::network::udpclient::NIOUDPClient : public Thread {
public:
	/**
	 * Get retry time for given retry count
	 * @param retries retry count
	 * @return approximatly retry time in ms
	 */
	static uint64_t getRetryTime(const uint8_t retries);

	/**
	 * Public constructor
	 * @param ip server ip
	 * @param port server port
	 */
	NIOUDPClient(const string& ip, const unsigned int port);

	/**
	 * @return initialized
	 */
	bool isInitialized();

	/**
	 * @return initialized
	 */
	bool isConnected();

	/**
	 * @return server ip
	 */
	const string& getIp();

	/**
	 * @return server port
	 */
	const unsigned int getPort();

	/**
	 * @return client key
	 */
	const string& getClientKey();

	/**
	 * Set client key
	 * @param clientKey client key
	 */
	void setClientKey(const string& clientKey);

	/**
	 * Run thread program
	 */
	virtual void run();

	/**
	 * Returns if a message should be processed or already have been processed
	 * @param clientMessage client message
	 * @return if message should be processed or not
	 */
	bool processSafeMessage(NIOUDPClientMessage* clientMessage);

	/**
	 * Receive message
	 * @return message or nullptr, needs to be deleted after processing
	 */
	NIOUDPClientMessage* receiveMessage();

	/**
	 * Pushes a message to be send, takes over ownership of message
	 * @param clientMessage client message object
	 * @param safe safe
	 */
	void sendMessage(NIOUDPClientMessage* clientMessage, bool safe) throw (NIOClientException);

	/**
	 * Create message
	 * @param frame frame content
	 */
	NIOUDPClientMessage* createMessage(stringstream* frame);
private:
	/**
	 * Processes ack reveived
	 * @param messageId message id
	 */
	void processAckReceived(const uint32_t messageId) throw (NIOClientException);

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
	uint32_t port;
	uint32_t clientId;
	uint32_t messageCount;
	string clientKey;

	const static int MESSAGEACK_RESENDTIMES_TRIES = 7;
	const static uint64_t MESSAGEACK_RESENDTIMES[MESSAGEACK_RESENDTIMES_TRIES];
	const static int MESSAGEQUEUE_SEND_BATCH_SIZE = 100;
	const static uint64_t MESSAGEACK_KEEPTIME = 5000L;
	struct Message {
		uint64_t time;
		uint8_t messageType;
		uint32_t messageId;
		uint8_t retries;
		char message[512];
		size_t bytes;
	};
	typedef queue<Message> MessageQueue;
	typedef map<uint32_t, Message> MessageMapAck;
	typedef queue<NIOUDPClientMessage*> RecvMessageQueue;

	static const uint64_t MESSAGESSAFE_KEEPTIME = 5000L;
	struct SafeMessage {
		uint32_t messageId;
		uint64_t time;
		uint8_t receptions;
	};
	typedef map<uint32_t, SafeMessage> MessageMapSafe;


	KernelEventMechanism kem;

	Mutex messageQueueMutex;
	MessageQueue messageQueue;

	Mutex messageMapAckMutex;
	MessageMapAck messageMapAck;

	Mutex recvMessageQueueMutex;
	RecvMessageQueue recvMessageQueue;

	Mutex messageMapSafeMutex;
	MessageMapSafe messageMapSafe;

	NIOUDPSocket socket;
};


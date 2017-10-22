#pragma once

#include <string>
#include <sstream>

#include <tdme.h>
#include <tdme/network/udpclient/fwd-tdme.h>

using std::string;
using std::stringstream;

/**
 * NIO UDP client message
 * @author Andreas Drewke
 */
class tdme::network::udpclient::NIOUDPClientMessage {
	friend NIOUDPClient;

public:
	enum MessageType {
		MESSAGETYPE_NONE,
		MESSAGETYPE_CONNECT,
		MESSAGETYPE_MESSAGE,
		MESSAGETYPE_ACKNOWLEDGEMENT
	};

	/**
	 * Parse
	 * @param message
	 * @param bytes
	 */
	static NIOUDPClientMessage* parse(const char message[512], const size_t bytes);

	/**
	 * Destructor
	 */
	~NIOUDPClientMessage();

	/**
	 * @return time
	 */
	const uint64_t getTime();

	/**
	 * @return message type
	 */
	const MessageType getMessageType();

	/**
	 * @return client id
	 */
	const uint32_t getClientId();

	/**
	 * @return message id
	 */
	const uint32_t getMessageId();

	/**
	 * @return retry count
	 */
	const uint8_t getRetryCount();

	/**
	 * @return frame
	 */
	stringstream* getFrame();

	/**
	 * Generate datagram
	 */
	void generate(char message[512], size_t& bytes);

private:
	/**
	 * Public constructor
	 * @param message type
	 * @param client id
	 * @param message id
	 * @param retries
	 * @param frame
	 */
	NIOUDPClientMessage(const MessageType messageType, const uint32_t clientId, const uint32_t messageId, const uint8_t retries, stringstream* frame);

	//
	long time;
	uint8_t retries;
	MessageType messageType;
	uint32_t clientId;
	uint32_t messageId;
	stringstream* frame;
};

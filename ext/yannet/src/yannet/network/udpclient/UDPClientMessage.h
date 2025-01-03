#pragma once

#include <memory>
#include <string>

#include <yannet/yannet.h>
#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpclient/fwd-yannet.h>
#include <yannet/utilities/Time.h>

using std::string;
using std::unique_ptr;

// namespaces
namespace yannet {
namespace network {
namespace udpclient {
	using ::yannet::network::udp::UDPPacket;
	using ::yannet::utilities::Time;
}
}
}

/**
 * UDP client message
 * @author Andreas Drewke
 */
class yannet::network::udpclient::UDPClientMessage final {
	friend UDPClient;

public:
	enum MessageType {
		MESSAGETYPE_NONE,
		MESSAGETYPE_CONNECT,
		MESSAGETYPE_MESSAGE,
		MESSAGETYPE_ACKNOWLEDGEMENT
	};

	/**
	 * Public destructor
	 */
	inline ~UDPClientMessage() {
	}

	/**
	 * @return time
	 */
	inline const uint64_t getTime() {
		return time;
	}

	/**
	 * @return message type
	 */
	inline const MessageType getMessageType() {
		return messageType;
	}

	/**
	 * @return client id
	 */
	inline const uint32_t getClientId() {
		return clientId;
	}

	/**
	 * @return message id
	 */
	inline const uint32_t getMessageId() {
		return messageId;
	}

	/**
	 * @return retry count
	 */
	inline const uint8_t getRetryCount() {
		return retries;
	}

	/**
	 * @return retry time
	 */
	const int64_t getRetryTime();

	/**
	 * @return udp client packet
	 */
	inline const UDPPacket* getPacket() {
		return packet.get();
	}

private:
	/**
	 * Parse UDP client message
	 * @param message message raw data
	 * @param bytes byte count of message raw data
	 */
	static UDPClientMessage* parse(const char message[512], uint16_t bytes);

	/**
	 * Public constructor
	 * @param messageType message type
	 * @param clientId client id
	 * @param messageId message id
	 * @param retries retries
	 * @param packet packet
	 */
	UDPClientMessage(const MessageType messageType, const uint32_t clientId, const uint32_t messageId, const uint8_t retries, const UDPPacket* packet):
		messageType(messageType),
		clientId(clientId),
		messageId(messageId),
		retries(retries),
		packet(unique_ptr<const UDPPacket>(packet)),
		time(Time::getCurrentMillis())
	{
		// no op
	}

	/**
	 * Generate datagram
	 * @param message message
	 * @param bytes bytes
	 */
	void generate(char message[512], uint16_t& bytes);

	/**
	 * Mark message to be resend with increased retry count
	 */
	inline void retry() {
		retries++;
	}

	//
	long time;
	uint8_t retries;
	MessageType messageType;
	uint32_t clientId;
	uint32_t messageId;
	unique_ptr<const UDPPacket> packet;
};

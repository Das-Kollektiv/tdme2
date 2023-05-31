#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/network/udpserver/fwd-tdme.h>
#include <tdme/network/udpserver/ServerClient.h>

using std::string;

using tdme::network::udp::UDPPacket;

namespace tdme {
namespace network {
namespace udpserver {

class ServerClient;

/**
 * @brief Server request bean
 * @author Andreas Drewke
 */
class ServerRequest final {

public:
	enum RequestType {
		REQUESTTYPE_CLIENT_REQUEST,
		REQUESTTYPE_CLIENT_INIT,
		REQUESTTYPE_CLIENT_CLOSE,
		REQUESTTYPE_CLIENT_CUSTOM,
		REQUESTTYPE_GROUP_INIT,
		REQUESTTYPE_GROUP_CLOSE,
		REQUESTTYPE_GROUP_CUSTOM,
	};
	static const uint32_t MESSAGE_ID_UNSUPPORTED = 0;
	static const uint8_t MESSAGE_RETRIES_NONE = 0;
	static const string EVENT_CUSTOM_NONE;

	/**
	 * @brief Public constructor
	 * @param requestType request type
	 * @param object object
	 * @param custom custom event type if any
	 * @param messagePacket request message packet
	 * @param messageId message id (udp server only)
	 * @param messageRetries message retries (udp server only)
	 */
	inline ServerRequest(const RequestType requestType, void* object, const string& custom = EVENT_CUSTOM_NONE, const UDPPacket* messagePacket = nullptr, const uint32_t messageId = MESSAGE_ID_UNSUPPORTED, const uint8_t messageRetries = MESSAGE_RETRIES_NONE) :
		requestType(requestType), object(object), customEvent(custom), messagePacket(messagePacket), messageId(messageId), messageRetries(messageRetries) {
		//
	}

	/**
	 * @brief Public destructor
	 */
	inline ~ServerRequest() {
	}

	/**
	 * @brief Returns the request type
	 * @return request type
	 */
	inline const RequestType getRequestType() {
		return requestType;
	}

	/**
	 * @brief Returns the associated object
	 * @return client
	 */
	inline void* getObject() {
		return object;
	}

	/**
	 * @return custom event name
	 */
	inline const string& getCustomEvent() {
		return customEvent;
	}

	/**
	 * @brief Returns the associated request message packet
	 * @return UDP server packet
	 */
	inline const UDPPacket* getMessagePacket() {
		return messagePacket;
	}

	/**
	 * @brief Returns associated message id (udp server only)
	 * @return message id
	 */
	inline const uint32_t getMessageId() {
		return messageId;
	}

	/**
	 * @brief Returns number of message retries (udp server only)
	 * @return retries
	 */
	inline const uint8_t getMessageRetries() {
		return messageRetries;
	}

private:
	RequestType requestType;
	void* object;
	string customEvent;
	const UDPPacket* messagePacket;
	uint32_t messageId;
	uint8_t messageRetries;
};

};
};
};

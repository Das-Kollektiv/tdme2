#include <tdme/network/udpclient/NIOUDPClientMessage.h>

#include <string.h>

#include <string>
#include <sstream>

#include <tdme/network/udpclient/NIOUDPClient.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Time.h>
#include <tdme/utils/IntEncDec.h>

using tdme::network::udpclient::NIOUDPClientMessage;

using std::ios_base;
using std::string;
using std::stringstream;

using tdme::network::udpclient::NIOUDPClient;
using tdme::utils::Console;
using tdme::utils::Time;
using tdme::utils::IntEncDec;

NIOUDPClientMessage* NIOUDPClientMessage::parse(const char message[512], const size_t bytes) {
	// decode header
	MessageType messageType = MessageType::MESSAGETYPE_NONE;
	switch(message[0]) {
		case 'A':
			messageType = MessageType::MESSAGETYPE_ACKNOWLEDGEMENT;
			break;
		case 'C':
			messageType = MessageType::MESSAGETYPE_CONNECT;
			break;
		case 'M':
			messageType = MessageType::MESSAGETYPE_MESSAGE;
			break;
		default:
			return nullptr;
	}
	uint32_t clientId;
	uint32_t messageId;
	uint32_t retries;
	IntEncDec::decodeInt(string(&message[1], 6), clientId);
	IntEncDec::decodeInt(string(&message[7], 6), messageId);
	IntEncDec::decodeInt(string(&message[13], 1), retries);
	// decode data
	stringstream* frame = nullptr;
	if (bytes > 14) {
		frame = new stringstream();
		frame->write(&message[14], bytes - 14);
	}
	return new NIOUDPClientMessage(messageType, clientId, messageId, retries, frame);
}

NIOUDPClientMessage::NIOUDPClientMessage(const MessageType messageType, const uint32_t clientId, const uint32_t messageId, const uint8_t retries, stringstream* frame) :
	messageType(messageType),
	clientId(clientId),
	messageId(messageId),
	retries(retries),
	frame(frame)
{
	time = Time::getCurrentMillis();
}

NIOUDPClientMessage::~NIOUDPClientMessage() {
	if (frame != nullptr) delete frame;
}

const uint64_t NIOUDPClientMessage::getTime() {
	return time;
}

const NIOUDPClientMessage::MessageType NIOUDPClientMessage::getMessageType() {
	return messageType;
}

const uint32_t NIOUDPClientMessage::getClientId() {
	return clientId;
}

const uint32_t NIOUDPClientMessage::getMessageId() {
	return messageId;
}

const int64_t NIOUDPClientMessage::getRetryTime() {
	return NIOUDPClient::getRetryTime(retries);
}

const uint8_t NIOUDPClientMessage::getRetryCount() {
	return retries;
}

void NIOUDPClientMessage::retry() {
	retries++;
}

stringstream* NIOUDPClientMessage::getFrame() {
	return frame;
}

void NIOUDPClientMessage::generate(char message[512], size_t& bytes) {
	string datagram;
	switch(messageType) {
		case MESSAGETYPE_ACKNOWLEDGEMENT:
			datagram+= 'A';
			break;
		case MESSAGETYPE_CONNECT:
			datagram+= 'C';
			break;
		case MESSAGETYPE_MESSAGE :
			datagram+= 'M';
			break;
		default:
			// FIXME
			break;
	}
	string retriesEncoded;
	string clientIdEncoded;
	string messageIdEncoded;
	IntEncDec::encodeInt(retries, retriesEncoded);
	IntEncDec::encodeInt(clientId, clientIdEncoded);
	IntEncDec::encodeInt(messageId, messageIdEncoded);
	datagram+= clientIdEncoded;
	datagram+= messageIdEncoded;
	datagram+= retriesEncoded[retriesEncoded.length()];
	if (frame != nullptr) {
		datagram+= frame->str();
	}
	bytes = datagram.size();
	memcpy(message, datagram.c_str(), bytes);
}

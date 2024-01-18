#include <tdme/network/udpclient/UDPClientMessage.h>

#include <cstring>

#include <string>
#include <string_view>

#include <tdme/tdme.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/network/udpclient/UDPClient.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/Time.h>

using tdme::network::udpclient::UDPClientMessage;

using std::memcpy;
using std::string;
using std::string_view;
using std::to_string;

using tdme::network::udp::UDPPacket;
using tdme::network::udpclient::UDPClient;
using tdme::utilities::Console;
using tdme::utilities::Integer;
using tdme::utilities::Time;

UDPClientMessage* UDPClientMessage::parse(const char message[512], uint16_t bytes) {
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
			Console::printLine("UDPClientMessage::parse(): invalid message type: '" + (string() + message[0]) + "' (" + to_string(message[0]) + ")");
			return nullptr;
	}

	//
	auto clientId = Integer::viewDecode(string_view(&message[1], 6));
	auto messageId = Integer::viewDecode(string_view(&message[7], 6));
	auto retries = Integer::viewDecode(string_view(&message[13], 1));

	// decode data
	UDPPacket* packet = nullptr;
	if (bytes > 14) {
		packet = new UDPPacket();
		packet->putBytes((const uint8_t*)&message[14], bytes - 14);
		packet->reset();
	}

	// construct UDP client message
	return new UDPClientMessage(messageType, clientId, messageId, retries, packet);
}

const int64_t UDPClientMessage::getRetryTime() {
	return UDPClient::getRetryTime(retries);
}

void UDPClientMessage::generate(char message[512], uint16_t& bytes) {
	UDPPacket generatedPacket;
	string datagram;
	switch(messageType) {
		case MESSAGETYPE_ACKNOWLEDGEMENT:
			generatedPacket.putByte('A');
			break;
		case MESSAGETYPE_CONNECT:
			generatedPacket.putByte('C');
			break;
		case MESSAGETYPE_MESSAGE :
			generatedPacket.putByte('M');
			break;
		default:
			// FIXME
			break;
	}
	auto clientIdEncoded = Integer::encode(clientId);
	auto messageIdEncoded = Integer::encode(messageId);
	auto retriesEncoded = Integer::encode(retries);
	generatedPacket.putBytes((const uint8_t*)clientIdEncoded.data(), clientIdEncoded.size());
	generatedPacket.putBytes((const uint8_t*)messageIdEncoded.data(), messageIdEncoded.size());
	generatedPacket.putByte(retriesEncoded[retriesEncoded.size() - 1]);
	if (packet != nullptr) generatedPacket.putPacket(packet.get());
	bytes = generatedPacket.getPosition();
	memcpy(message, generatedPacket.getData().data(), bytes);
}

#include <string.h>

#include <memory>
#include <queue>
#include <string>
#include <typeinfo>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/network/udpclient/NetworkClientException.h>
#include <tdme/network/udpclient/UDPClient.h>
#include <tdme/network/udpclient/UDPClientMessage.h>
#include <tdme/os/network/KernelEventMechanism.h>
#include <tdme/os/network/NetworkSocket.h>
#include <tdme/os/network/NIOInterest.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/RTTI.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::queue;
using std::unique_ptr;
using std::unordered_map;
using std::string;

using tdme::network::udp::UDPPacket;
using tdme::network::udpclient::NetworkClientException;
using tdme::network::udpclient::UDPClient;
using tdme::network::udpclient::UDPClientMessage;
using tdme::os::network::KernelEventMechanism;
using tdme::os::network::NetworkSocket;
using tdme::os::network::NIO_INTEREST_NONE;
using tdme::os::network::NIO_INTEREST_READ;
using tdme::os::network::NIO_INTEREST_WRITE;
using tdme::os::network::NIOInterest;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::RTTI;
using tdme::utilities::Time;

const uint64_t UDPClient::MESSAGEACK_RESENDTIMES[UDPClient::MESSAGEACK_RESENDTIMES_TRIES] = {125L, 250L, 500L, 750L, 1000L, 2000L, 5000L};

UDPClient::UDPClient(const string& ip, const uint16_t port) :
	Thread("nioudpclientthread"),
	messageQueueMutex("nioupclientthread_messagequeue"),
	messageMapAckMutex("nioupclientthread_messagequeueack"),
	recvMessageQueueMutex("nioupclientthread_recvmessagequeuemutex"),
	messageMapSafeMutex("nioupclientthread_messagemasafemutex"),
	ip(ip),
	port(port),
	clientId(0),
	messageCount(0),
	initialized(false),
	connected(false) {
	//
}

UDPClient::~UDPClient() {
	//
	messageQueueMutex.lock();
	while (messageQueue.empty() == false) {
		delete messageQueue.front();
		messageQueue.pop();
	}
	messageQueueMutex.unlock();
	//
	messageMapAckMutex.lock();
	for (const auto& [messageId, message]: messageMapAck) delete message;
	messageMapAck.clear();
	messageMapAckMutex.unlock();
	//
	recvMessageQueueMutex.lock();
	while (recvMessageQueue.empty() == false) {
		delete recvMessageQueue.front();
		recvMessageQueue.pop();
	}
	recvMessageQueueMutex.unlock();
	//
	messageMapSafeMutex.lock();
	for (const auto& [messageId, message]: messageMapSafe) delete message;
	messageMapSafe.clear();
	messageMapSafeMutex.unlock();
}

void UDPClient::run() {
	Console::println("UDPClient::run(): start");

	// catch kernel event and server socket exceptions
	try {
		// create client socket
		UDPSocket::createClientSocket(socket, NetworkSocket::determineIpVersion(ip));

		// initialize kernel event mechanismn
		kem.initKernelEventMechanism(1);
		kem.setSocketInterest(socket, NIO_INTEREST_NONE, NIO_INTEREST_READ, nullptr);

		// initialized
		initialized = true;

		// do event loop
		auto lastMessageQueueAckTime = Time::getCurrentMillis();
		auto lastMessageConnectTime = Time::getCurrentMillis();
		auto lastMessageSafeCleanTime = Time::getCurrentMillis();
		while(isStopRequested() == false) {
			auto now = Time::getCurrentMillis();

			// process connect messages every 25ms
			if (connected == false && now >= lastMessageConnectTime + 25L) {
				// send connection message
				sendMessage(new UDPClientMessage(UDPClientMessage::MESSAGETYPE_CONNECT, 0, 0, 0, nullptr), false);
				lastMessageConnectTime = now;
			}

			// process ack messages every 25ms
			if (now >= lastMessageQueueAckTime + 25L) {
				processAckMessages();
				lastMessageQueueAckTime = now;
			}

			// process save messages clean up every 25ms
			if (now >= lastMessageSafeCleanTime + 25L) {
				cleanUpSafeMessages();
				lastMessageQueueAckTime = now;
			}

			// do kernel event mechanism
			int events = kem.doKernelEventMechanism();

			// iterate the event list
			for(unsigned int i = 0; i < (unsigned int)events; i++) {
				NIOInterest keInterest;
				void* nil;

				// decode kernel event
				kem.decodeKernelEvent(i, keInterest, (void*&)nil);

				// interests
				auto hasReadInterest = (keInterest & NIO_INTEREST_READ) == NIO_INTEREST_READ;
				auto hasWriteInterest = (keInterest & NIO_INTEREST_WRITE) == NIO_INTEREST_WRITE;

				// process read interest
				if (hasReadInterest == true) {
					ssize_t bytesReceived;
					string fromIp;
					unsigned int fromPort;
					char message[512];

					// receive datagrams as long as its size > 0 and read would not block
					while ((bytesReceived = socket.read(fromIp, fromPort, (void*)message, sizeof(message))) > 0) {
						//
						statistics.received++;
						//
						auto clientMessage = unique_ptr<UDPClientMessage>(UDPClientMessage::parse(message, bytesReceived));
						try {
							if (clientMessage == nullptr) {
								throw NetworkClientException("invalid message");
							}
							switch(clientMessage->getMessageType()) {
								case UDPClientMessage::MESSAGETYPE_ACKNOWLEDGEMENT:
									{
										processAckReceived(clientMessage->getMessageId());
										//
										break;
									}
								case UDPClientMessage::MESSAGETYPE_CONNECT:
									{
										sendMessage(
											new UDPClientMessage(
												UDPClientMessage::MESSAGETYPE_ACKNOWLEDGEMENT,
												clientMessage->getClientId(),
												clientMessage->getMessageId(),
												clientMessage->getRetryCount() + 1,
												nullptr
											),
											false
										);
										clientId = clientMessage->getClientId();
										// read client key
										auto packet = clientMessage->getPacket();
										clientKey = packet->getString();
										// we are connected
										connected = true;
										//
										break;
									}
								case UDPClientMessage::MESSAGETYPE_MESSAGE:
									{
										//	check if message queue is full
										recvMessageQueueMutex.lock();
										if (recvMessageQueue.size() > 1000) {
											recvMessageQueueMutex.unlock();
											throw NetworkClientException("recv message queue overflow");
										}
										recvMessageQueue.push(clientMessage.release());
										recvMessageQueueMutex.unlock();
										break;
									}
								case UDPClientMessage::MESSAGETYPE_NONE:
									{
										break;
									}
							}
						} catch (Exception &exception) {
							// log
							Console::println(
								"UDPClient::run(): " +
								RTTI::demangle(typeid(exception).name()) +
								": " +
								string(exception.what())
							);

							//
							statistics.errors++;

							// rethrow to quit communication for now
							// TODO: maybe find a better way to handle errors
							//	one layer up should be informed about network client problems somehow
							throw exception;
						}
					}
				}

				// process write interest
				while (hasWriteInterest == true) {
					// fetch batch of messages to be send
					MessageQueue messageQueueBatch;
					messageQueueMutex.lock();
					for (int i = 0; i < MESSAGEQUEUE_SEND_BATCH_SIZE && messageQueue.empty() == false; i++) {
						auto message = messageQueue.front();
						messageQueueBatch.push(message);
						messageQueue.pop();
					}
					messageQueueMutex.unlock();

					// try to send batch
					while (messageQueueBatch.empty() == false) {
						auto message = messageQueueBatch.front();
						if (socket.write(ip, port, (void*)message->message, message->bytes) == -1) {
							// sending would block, stop trying to sendin
							statistics.errors++;
							//
							break;
						} else {
							// success, remove message from message queue batch and continue
							auto message = messageQueueBatch.front();
							delete message;
							messageQueueBatch.pop();
							//
							statistics.sent++;
						}
					}

					// re add messages not sent in batch to message queue
					if (messageQueueBatch.empty() == true) {
						messageQueueMutex.lock();
						if (messageQueue.empty() == true) {
							kem.setSocketInterest(
								socket,
								NIO_INTEREST_READ | NIO_INTEREST_WRITE,
								NIO_INTEREST_READ,
								nullptr
							);

							// no more data to send, so stop the loop
							hasWriteInterest = false;
						}
						messageQueueMutex.unlock();
					} else {
						messageQueueMutex.lock();
						do {
							auto message = messageQueueBatch.front();
							messageQueue.push(message);
							messageQueueBatch.pop();
						} while (messageQueueBatch.empty() == false);
						messageQueueMutex.unlock();

						// we did not send all batched messages, so stop the loop
						hasWriteInterest = false;
					}
				}
			}
		}

	//
	} catch (Exception &exception) {
		// log
		Console::println(
			"UDPClient::run(): " +
			RTTI::demangle(typeid(exception).name()) +
			": " +
			string(exception.what())
		);
	}

	// exit gracefully
	kem.shutdownKernelEventMechanism();
	socket.close();

	// log
	Console::println("UDPClient::run(): done");
}

void UDPClient::sendMessage(UDPClientMessage* clientMessage, bool safe) {
	// create message
	auto clientMessagePtr = unique_ptr<UDPClientMessage>(clientMessage);
	auto message = make_unique<Message>();
	message->time = clientMessagePtr->getTime();
	message->messageType = clientMessagePtr->getMessageType();
	message->messageId = clientMessagePtr->getMessageId();
	message->retries = 0;
	clientMessagePtr->generate(message->message, message->bytes);

	// requires ack and retransmission ?
	if (safe == true) {
		messageMapAckMutex.lock();
		// 	check if message has already be pushed to ack
		auto it = messageMapAck.find(message->messageId);
		if (it != messageMapAck.end()) {
 			// its on ack queue already, so unlock
			messageMapAckMutex.unlock();
			throw NetworkClientException("message already on message queue ack");
		}
		//	check if message queue is full
		if (messageMapAck.size() > 1000) {
			messageMapAckMutex.unlock();
			throw NetworkClientException("message queue ack overflow");
		}
		// 	push to message queue ack
		// 	create message ack
		auto messageAck = new Message();
		*messageAck = *message;
		messageMapAck[message->messageId] = messageAck;
		messageMapAckMutex.unlock();
	}

	// push to message queue
	messageQueueMutex.lock();

	//	check if message queue is full
	if (messageQueue.size() > 1000) {
		messageQueueMutex.unlock();
		throw NetworkClientException("message queue overflow");
	}
	messageQueue.push(message.release());

	// set nio interest
	if (messageQueue.size() == 1) {
		kem.setSocketInterest(
			socket,
			NIO_INTEREST_READ,
			NIO_INTEREST_READ | NIO_INTEREST_WRITE,
			nullptr
		);
	}

	// done
	messageQueueMutex.unlock();
}

void UDPClient::processAckReceived(const uint32_t messageId) {
	auto messageAckValid = true;

	// delete message from message queue ack
	messageMapAckMutex.lock();
	auto it = messageMapAck.find(messageId);
	if (it != messageMapAck.end()) {
		// message ack valid?
		messageAckValid = true; //messageAck->ip == client->ip && messageAck->port == client->port;
		// remove if valid
		if (messageAckValid == true) {
			// remove message from message queue ack
			delete it->second;
			messageMapAck.erase(it);
		}
	}
	messageMapAckMutex.unlock();

	// check if message ack was valid
	if (messageAckValid == false) {
		throw NetworkClientException("message ack invalid");
	}
}

void UDPClient::processAckMessages() {
	MessageQueue messageQueueResend;
	auto now = Time::getCurrentMillis();

	messageMapAckMutex.lock();
	auto it = messageMapAck.begin();
	while (it != messageMapAck.end()) {
		auto messageAck = it->second;
		// message ack timed out?
		//	most likely the client is gone
		if (messageAck->retries == MESSAGEACK_RESENDTIMES_TRIES) {
			// delete from message map ack
			delete it->second;
			messageMapAck.erase(it++);
			// skip
			continue;
		} else
		// message should be resend?
		if (now > (messageAck->time + (MESSAGEACK_RESENDTIMES[messageAck->retries]))) {
			// increase tries
			messageAck->retries++;

			// construct message
			auto message = new Message();
			*message = *messageAck;

			// parse client message from message raw data
			auto clientMessage = unique_ptr<UDPClientMessage>(UDPClientMessage::parse(message->message, message->bytes));

			// increase/set retry
			clientMessage->retry();

			// recreate message
			clientMessage->generate(message->message, message->bytes);

			// and push to be resent
			messageQueueResend.push(message);
		}
		++it;
	}
	messageMapAckMutex.unlock();

	// reissue messages to be resent
	if (messageQueueResend.empty() == false) {
		messageQueueMutex.lock();
		do {
			auto message = messageQueueResend.front();
			messageQueue.push(message);
			messageQueueResend.pop();

			// set nio interest
			if (messageQueue.size() == 1) {
				kem.setSocketInterest(
					socket,
					NIO_INTEREST_READ,
					NIO_INTEREST_READ | NIO_INTEREST_WRITE,
					nullptr
				);
			}
		} while (messageQueueResend.empty() == false);
		messageQueueMutex.unlock();
	}
}

bool UDPClient::processSafeMessage(UDPClientMessage* clientMessage) {
	auto messageProcessed = false;
	auto messageId = clientMessage->getMessageId();

	//
	messageMapSafeMutex.lock();

	// check if message has been already processed
	auto it = messageMapSafe.find(messageId);
	if (it != messageMapSafe.end()) {
		// yep, we did
		messageProcessed = true;
		auto message = it->second;
		message->receptions++;
	} else {
		// nope, just remember message
		auto message = new SafeMessage();
		message->messageId = messageId;
		message->receptions = 1;
		message->time = Time::getCurrentMillis();
		// TODO: check for overflow
		messageMapSafe[messageId] = message;
	}

	//
	messageMapSafeMutex.unlock();

	// always send ack
	sendMessage(
		new UDPClientMessage(
			UDPClientMessage::MESSAGETYPE_ACKNOWLEDGEMENT,
			clientId,
			clientMessage->getMessageId(),
			0,
			nullptr
		),
		false
	);

	// return if message should be processed
	return messageProcessed == true?false:true;
}


void UDPClient::cleanUpSafeMessages() {
	//
	messageMapSafeMutex.lock();

	// check if message has been already processed
	auto now = Time::getCurrentMillis();
	auto it = messageMapSafe.begin();
	while (it != messageMapSafe.end()) {
		SafeMessage* message = it->second;
		if (message->time < now - MESSAGESSAFE_KEEPTIME) {
			delete it->second;
			messageMapSafe.erase(it++);
			continue;
		}
		++it;
	}

	//
	messageMapSafeMutex.unlock();
}

UDPClientMessage* UDPClient::receiveMessage() {
	UDPClientMessage* message = nullptr;
	recvMessageQueueMutex.lock();
	if (recvMessageQueue.empty() == false) {
		message = recvMessageQueue.front();
		recvMessageQueue.pop();
	}
	recvMessageQueueMutex.unlock();
	return message;
}

UDPClientMessage* UDPClient::createMessage(const UDPPacket* packet) {
	return new UDPClientMessage(
		UDPClientMessage::MESSAGETYPE_MESSAGE,
		clientId,
		messageCount++,
		0,
		packet
	);
}

const UDPClient::UDPClient_Statistics UDPClient::getStatistics() {
	auto stats = statistics;
	statistics.time = Time::getCurrentMillis();
	statistics.received = 0;
	statistics.sent = 0;
	statistics.errors = 0;
	return stats;
}

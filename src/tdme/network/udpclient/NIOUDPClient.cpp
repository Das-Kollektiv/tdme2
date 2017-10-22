#include <string.h>

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <typeinfo>

#include <tdme/os/network/KernelEventMechanism.h>
#include <tdme/os/network/NIOInterest.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/RTTI.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/Time.h>
#include <tdme/network/udpclient/NIOUDPClient.h>
#include <tdme/network/udpclient/NIOUDPClientMessage.h>
#include <tdme/network/udpclient/NIOClientException.h>

using std::pair;
using std::ios;
using std::map;
using std::stringstream;
using std::string;
using std::wstring;
using std::to_wstring;

using tdme::os::network::KernelEventMechanism;
using tdme::os::network::NIOInterest;
using tdme::os::network::NIO_INTEREST_NONE;
using tdme::os::network::NIO_INTEREST_READ;
using tdme::os::network::NIO_INTEREST_WRITE;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::RTTI;
using tdme::utils::StringConverter;
using tdme::utils::Time;
using tdme::network::udpclient::NIOUDPClient;
using tdme::network::udpclient::NIOUDPClientMessage;
using tdme::network::udpclient::NIOClientException;

const uint64_t NIOUDPClient::MESSAGEACK_RESENDTIMES[NIOUDPClient::MESSAGEACK_RESENDTIMES_TRIES] = {125L, 250L, 500L, 750L, 1000L, 2000L, 5000L};

NIOUDPClient::NIOUDPClient(const string& ip, const unsigned int port) :
	Thread(L"nioudpclientthread"),
	messageQueueMutex(L"nioupclientthread_messagequeue"),
	messageMapAckMutex(L"nioupclientthread_messagequeueack"),
	recvMessageQueueMutex(L"nioupclientthread_recvmessagequeuemutex"),
	messageMapSafeMutex(L"nioupclientthread_messagemasafemutex"),
	ip(ip),
	port(port),
	clientId(0),
	messageCount(0),
	initialized(false),
	connected(false) {
	//
}

bool NIOUDPClient::isInitialized() {
	return initialized;
}

bool NIOUDPClient::isConnected() {
	return connected;
}

void NIOUDPClient::run() {
	Console::println(L"NIOUDPClient::run(): start");

	// catch kernel event and server socket exceptions
	try {
		// create client socket
		NIOUDPSocket::createClientSocket(socket);

		// initialize kernel event mechanismn
		kem.initKernelEventMechanism(1);
		kem.setSocketInterest(socket, NIO_INTEREST_NONE, NIO_INTEREST_READ, nullptr);

		// initialized
		initialized = true;

		// do event loop
		uint64_t lastMessageQueueAckTime = Time::getCurrentMillis();
		uint64_t lastMessageConnectTime = Time::getCurrentMillis();
		uint64_t lastMessageSafeCleanTime = Time::getCurrentMillis();
		while(isStopRequested() == false) {
			uint64_t now = Time::getCurrentMillis();

			// process connect messages every 25ms
			if (connected == false && now >= lastMessageConnectTime + 25L) {
				// send connection message
				sendMessage(new NIOUDPClientMessage(NIOUDPClientMessage::MESSAGETYPE_CONNECT, 0, 0, 0, nullptr), false);
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
				bool hasReadInterest = (keInterest & NIO_INTEREST_READ) == NIO_INTEREST_READ;
				bool hasWriteInterest = (keInterest & NIO_INTEREST_WRITE) == NIO_INTEREST_WRITE;

				// process read interest
				if (hasReadInterest) {
					ssize_t bytesReceived;
					string fromIp;
					unsigned int fromPort;
					char message[512];

					// receive datagrams as long as its size > 0 and read would not block
					while ((bytesReceived = socket.read(fromIp, fromPort, (void*)message, sizeof(message))) > 0) {
						stringstream* frame = NULL;
						NIOUDPClientMessage* clientMessage = NIOUDPClientMessage::parse(message, bytesReceived);
						// Console::println("Got message: " + string(message, bytesReceived));
						switch(clientMessage->getMessageType()) {
							case NIOUDPClientMessage::MESSAGETYPE_ACKNOWLEDGEMENT:
								processAckReceived(clientMessage->getMessageId());
								delete clientMessage;
								break;
							case NIOUDPClientMessage::MESSAGETYPE_CONNECT:
								sendMessage(
									new NIOUDPClientMessage(
										NIOUDPClientMessage::MESSAGETYPE_ACKNOWLEDGEMENT,
										clientMessage->getClientId(),
										clientMessage->getMessageId(),
										clientMessage->getRetryCount() + 1,
										nullptr
									),
									false
								);
								clientId = clientMessage->getClientId();
								connected = true;
								delete clientMessage;
								break;
							case NIOUDPClientMessage::MESSAGETYPE_MESSAGE:
								recvMessageQueueMutex.lock();
								recvMessageQueue.push(clientMessage);
								recvMessageQueueMutex.unlock();
								break;
							case NIOUDPClientMessage::MESSAGETYPE_NONE:
								break;
						}
					}
				}

				// process write interest
				while (hasWriteInterest) {
					// fetch batch of messages to be send
					MessageQueue messageQueueBatch;
					messageQueueMutex.lock();
					for (int i = 0; i < MESSAGEQUEUE_SEND_BATCH_SIZE && messageQueue.empty() == false; i++) {
						Message* message = &messageQueue.front();
						messageQueueBatch.push(*message);
						messageQueue.pop();
					}
					messageQueueMutex.unlock();

					// try to send batch
					while (messageQueueBatch.empty() == false) {
						Message* message = &messageQueueBatch.front();
						if (socket.write(ip, port, (void*)message->message, message->bytes) == -1) {
							// sending would block, stop trying to sendin
							break;
						} else {
							// success, remove message from message queue batch and continue
							messageQueueBatch.pop();
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
								NULL
							);

							// no more data to send, so stop the loop
							hasWriteInterest = false;
						}
						messageQueueMutex.unlock();
					} else {
						messageQueueMutex.lock();
						do {
							Message* message = &messageQueueBatch.front();
							messageQueue.push(*message);
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
			L"NIOUDPClientThread::run(): " +
			StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
			L": " +
			StringConverter::toWideString(exception.what())
		);
	}

	// exit gracefully
	kem.shutdownKernelEventMechanism();
	socket.close();

	// log
	Console::println(L"NIOUDPClientThread::run(): done");
}

void NIOUDPClient::sendMessage(NIOUDPClientMessage* clientMessage, bool safe) throw (NIOClientException) {
	// create message
	Message message;
	message.time = clientMessage->getTime();
	message.messageType = clientMessage->getMessageType();
	message.messageId = clientMessage->getMessageId();
	message.retries = 0;
	clientMessage->generate(message.message, message.bytes);
	delete clientMessage;

	// requires ack and retransmission ?
	if (safe == true) {
		// 	create message ack
		Message messageAck;
		messageAck = message;

		messageMapAckMutex.lock();
		MessageMapAck::iterator it;
		// 	check if message has already be pushed to ack
		it = messageMapAck.find(message.messageId);
		if (it != messageMapAck.end()) {
 			// its on ack queue already, so unlock
			messageMapAckMutex.unlock();
			throw NIOClientException("message already on message queue ack");
		}
		//	check if message queue is full
		if (messageMapAck.size() > 20) {
			messageMapAckMutex.unlock();
			throw NIOClientException("message queue ack overflow");
		}
		// 	push to message queue ack
		messageMapAck.insert(it, pair<uint32_t, Message>(message.messageId, messageAck));
		messageMapAckMutex.unlock();
	}

	// push to message queue
	messageQueueMutex.lock();

	//	check if message queue is full
	if (messageQueue.size() > 20) {
		messageQueueMutex.unlock();
		throw NIOClientException("message queue overflow");
	}
	messageQueue.push(message);

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

void NIOUDPClient::processAckReceived(const uint32_t messageId) throw (NIOClientException) {
	bool messageAckValid = true;
	MessageMapAck::iterator iterator;

	// delete message from message queue ack
	messageMapAckMutex.lock();
	iterator = messageMapAck.find(messageId);
	if (iterator != messageMapAck.end()) {
		// message exists
		Message* messageAck = &iterator->second;
		// message ack valid?
		messageAckValid = true; //messageAck->ip == client->ip && messageAck->port == client->port;
		// remove if valid
		if (messageAckValid == true) {
			// remove message from message queue ack
			messageMapAck.erase(iterator);
		}
	}
	messageMapAckMutex.unlock();

	// check if message ack was valid
	if (messageAckValid == false) {
		throw NIOClientException("message ack invalid");
	}
}

void NIOUDPClient::processAckMessages() {
	MessageQueue messageQueueResend;
	uint64_t now = Time::getCurrentMillis();

	messageMapAckMutex.lock();
	MessageMapAck::iterator it = messageMapAck.begin();
	while (it != messageMapAck.end()) {
		Message* messageAck = &it->second;
		// message ack timed out?
		//	most likely the client is gone
		if (messageAck->retries == MESSAGEACK_RESENDTIMES_TRIES) {
			// delete from message map ack
			messageMapAck.erase(it++);
			// skip
			continue;
		} else
		// message should be resend?
		if (now > (messageAck->time + (MESSAGEACK_RESENDTIMES[messageAck->retries]))) {
			// increase tries
			messageAck->retries++;

			// construct message
			Message message = *messageAck;

			// parse client message from message raw data
			NIOUDPClientMessage* clientMessage = NIOUDPClientMessage::parse(message.message, message.bytes);

			// TODO: increase/set retry

			// recreate message
			clientMessage->generate(message.message, message.bytes);

			// delete client message
			delete clientMessage;

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
			Message* message = &messageQueueResend.front();
			messageQueue.push(*message);
			messageQueueResend.pop();

			// set nio interest
			if (messageQueue.size() == 1) {
				kem.setSocketInterest(
					socket,
					NIO_INTEREST_READ,
					NIO_INTEREST_READ | NIO_INTEREST_WRITE,
					NULL
				);
			}
		} while (messageQueueResend.empty() == false);
		messageQueueMutex.unlock();
	}
}

bool NIOUDPClient::processSafeMessage(NIOUDPClientMessage* clientMessage) {
	bool messageProcessed = false;
	MessageMapSafe::iterator it;
	auto messageId = clientMessage->getMessageId();

	//
	messageMapSafeMutex.lock();

	// check if message has been already processed
	it = messageMapSafe.find(messageId);
	if (it != messageMapSafe.end()) {
		// yep, we did
		messageProcessed = true;
		SafeMessage& message = it->second;
		message.receptions++;
	} else {
		// nope, just remember message
		SafeMessage message;
		message.messageId = messageId;
		message.receptions = 1;
		message.time = Time::getCurrentMillis();
		// TODO: check for overflow
		messageMapSafe.insert(it, pair<uint32_t, SafeMessage>(messageId, message));
	}

	//
	messageMapSafeMutex.unlock();

	// always send ack
	sendMessage(
		new NIOUDPClientMessage(
			NIOUDPClientMessage::MESSAGETYPE_ACKNOWLEDGEMENT,
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


void NIOUDPClient::cleanUpSafeMessages() {
	//
	messageMapSafeMutex.lock();

	// check if message has been already processed
	uint64_t now = Time::getCurrentMillis();
	MessageMapSafe::iterator it = messageMapSafe.begin();
	while (it != messageMapSafe.end()) {
		SafeMessage& message = it->second;
		if (message.time < now - MESSAGESSAFE_KEEPTIME) {
			messageMapSafe.erase(it++);
			continue;
		}
		++it;
	}

	//
	messageMapSafeMutex.unlock();
}

uint64_t NIOUDPClient::getRetryTime(const uint8_t retries) {
	if (retries == 0) return 0L;
	if (retries > NIOUDPClient::MESSAGEACK_RESENDTIMES_TRIES) return 0L;
	return NIOUDPClient::MESSAGEACK_RESENDTIMES[retries - 1];
}

NIOUDPClientMessage* NIOUDPClient::receiveMessage() {
	NIOUDPClientMessage* message = nullptr;
	recvMessageQueueMutex.lock();
	if (recvMessageQueue.empty() == false) {
		message = recvMessageQueue.front();
		recvMessageQueue.pop();
	}
	recvMessageQueueMutex.unlock();
	return message;
}

NIOUDPClientMessage* NIOUDPClient::createMessage(stringstream* frame) {
	return new NIOUDPClientMessage(
		NIOUDPClientMessage::MESSAGETYPE_MESSAGE,
		clientId,
		messageCount++,
		0,
		frame
	);
}

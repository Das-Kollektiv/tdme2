#include <string.h>

#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/network/udpserver/ServerRequest.h>
#include <tdme/network/udpserver/UDPServerIOThread.h>
#include <tdme/os/network/KernelEventMechanism.h>
#include <tdme/os/network/NIOInterest.h>
#include <tdme/os/threading/AtomicOperations.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/RTTI.h>
#include <tdme/utilities/Time.h>

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;

using tdme::network::udp::UDPPacket;
using tdme::network::udpserver::ServerRequest;
using tdme::network::udpserver::UDPServerIOThread;
using tdme::os::network::KernelEventMechanism;
using tdme::os::network::NIO_INTEREST_NONE;
using tdme::os::network::NIO_INTEREST_READ;
using tdme::os::network::NIO_INTEREST_WRITE;
using tdme::os::network::NIOInterest;
using tdme::os::threading::AtomicOperations;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::RTTI;
using tdme::utilities::Time;

const uint64_t UDPServerIOThread::MESSAGEACK_RESENDTIMES[UDPServerIOThread::MESSAGEACK_RESENDTIMES_TRIES] = {125L, 250L, 500L, 750L, 1000L, 2000L, 5000L};

UDPServerIOThread::UDPServerIOThread(const unsigned int id, UDPServer *server, const unsigned int maxCCU, Barrier* startUpBarrier) :
	Thread("nioudpserveriothread"),
	id(id),
	server(server),
	maxCCU(maxCCU),
	startUpBarrier(startUpBarrier),
	messageQueueMutex("nioupserveriothread_messagequeue"),
	messageMapAckMutex("nioupserveriothread_messagequeueack") {
	//
}

UDPServerIOThread::~UDPServerIOThread() {
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
}

void UDPServerIOThread::run() {
	Console::printLine("UDPServerIOThread[" + to_string(id) + "]::run(): start");

	// wait on startup barrier
	startUpBarrier->wait();
	startUpBarrier = nullptr;

	// catch kernel event and server socket exceptions
	try {
		// create server socket
		socket = unique_ptr<UDPSocket>(UDPSocket::createServerSocket(server->host, server->port));

		// initialize kernel event mechanismn
		kem.initKernelEventMechanism(1);
		kem.setSocketInterest(socket.get(), NIO_INTEREST_NONE, NIO_INTEREST_READ, nullptr);

		// do event loop
		auto lastMessageQueueAckTime = Time::getCurrentMillis();
		while (isStopRequested() == false) {
			auto now = Time::getCurrentMillis();

			// process ack messages every 25ms
			if (now >= lastMessageQueueAckTime + 25L) {
				processAckMessages();
				lastMessageQueueAckTime = now;
			}

			// do kernel event mechanism
			auto events = kem.doKernelEventMechanism();

			// iterate the event list
			for (auto i = 0; i < events; i++) {
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
					string ip;
					unsigned int port;
					char message[512];

					// receive datagrams as long as its size > 0 and read would not block
					while ((bytesReceived = socket->read(ip, port, (void*)message, sizeof(message))) > 0) {
						//
						AtomicOperations::increment(server->statistics.received);

						// process event, catch and handle client related exceptions
						UDPServerClient* client = nullptr;
						UDPServerClient* clientNew = nullptr;
						try {
							// transfer buffer to string stream
							auto packet = make_unique<UDPPacket>();
							packet->putBytes((const uint8_t*)message, bytesReceived);
							packet->reset();

							// validate datagram
							server->validate(packet.get());

							// identify datagram
							UDPServer::MessageType messageType;
							uint32_t clientId;
							uint32_t messageId;
							uint8_t retries;
							server->identify(packet.get(), messageType, clientId, messageId, retries);

							// process message depending on messageType
							switch(messageType) {
								case(UDPServer::MESSAGETYPE_CONNECT):
									{
										//
										AtomicOperations::increment(server->statistics.accepts);

										// check if client is connected already
										client = server->getClientByIp(ip, port);
										if (client != nullptr) {
											// delete packet
											client->sendConnected();
											client->releaseReference();
											// we are done
											break;
										}

										// create client
										clientNew = server->accept(
											server->allocateClientId(),
											ip,
											port
										);

										// assign server
										clientNew->server = server;

										// add client to server
										server->addClient(clientNew);

										// switch from client new to client
										client = clientNew;
										clientNew = nullptr;

										// send connected ack
										client->sendConnected();

										// set/register client in Server
										if (client->setKey(client->getKey()) == false) {
											throw NetworkServerException("Client key is already in use");
										}

										// fire on init
										client->init();

										// we are done
										break;
									}
								case(UDPServer::MESSAGETYPE_MESSAGE):
									{
										// look up client
										client = server->lookupClient(clientId);
										// check if client ip, port matches datagram ip and prt
										if (client->ip != ip || client->port != port) {
											//
											client->releaseReference();
											throw NetworkServerException("message invalid");
										}
										// delegate
										client->onPacketReceived(packet.release(), messageId, retries);
										break;
									}
								case(UDPServer::MESSAGETYPE_ACKNOWLEDGEMENT):
									{
										client = server->lookupClient(clientId);
										server->processAckReceived(client, messageId);
										break;
									}
								default:
									throw NetworkServerException("Invalid message type");
							}
						} catch(Exception& exception) {
							// log
							Console::printLine(
								"UDPServerIOThread[" +
								to_string(id) +
								"]::run(): " +
								(RTTI::demangle(typeid(exception).name())) +
								": " +
								(exception.what())
							);

							if (clientNew != nullptr) {
								delete clientNew;
							}
							// in case it was a client related exception
							if (client != nullptr) {
								// otherwise shut down client
								client->shutdown();
							}
							//
							AtomicOperations::increment(server->statistics.errors);
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
						if (socket->write(message->ip, message->port, (void*)message->message, message->bytes) == -1) {
							// sending would block, stop trying to sendin
							AtomicOperations::increment(server->statistics.errors);
							break;
						} else {
							// success, remove message from message queue batch and continue
							delete message;
							messageQueueBatch.pop();
							//
							AtomicOperations::increment(server->statistics.sent);
						}
					}

					// re add messages not sent in batch to message queue
					if (messageQueueBatch.empty() == true) {
						messageQueueMutex.lock();
						if (messageQueue.empty() == true) {
							kem.setSocketInterest(
								socket.get(),
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
		Console::printLine(
			"UDPServerIOThread[" +
			to_string(id) +
			"]::run(): " +
			(RTTI::demangle(typeid(exception).name())) +
			": " +
			(exception.what())
		);
	}

	// exit gracefully
	kem.shutdownKernelEventMechanism();
	socket->close();

	// log
	Console::printLine("UDPServerIOThread[" + to_string(id) + "]::run(): done");
}

void UDPServerIOThread::sendMessage(const UDPServerClient* client, const uint8_t messageType, const uint32_t messageId, const UDPPacket* packet, const bool safe, const bool deletePacket) {
	// create message
	auto message = make_unique<Message>();
	message->ip = client->ip;
	message->port = client->port;
	message->time = Time::getCurrentMillis();
	message->messageType = messageType;
	message->clientId = client->clientId;
	message->messageId = messageId;
	message->retries = 0;
	message->bytes = packet->getSize();

	// store current position which should be end of packet
	auto position = packet->getPosition();
	// reset position to be able to write header
	packet->reset();
	packet->getBytes((uint8_t*)message->message, message->bytes);
	// restore position to end of stream
	packet->setPosition(position);

	// delete packet if requested
	if (deletePacket == true) delete packet;

	// requires ack and retransmission ?
	if (safe == true) {
		messageMapAckMutex.lock();
		// 	check if message has already be pushed to ack
		auto it = messageMapAck.find(messageId);
		if (it != messageMapAck.end()) {
 			// its on ack queue already, so unlock
			messageMapAckMutex.unlock();
			throw NetworkServerException("message already on message queue ack");
		}
		//	check if message queue is full
		if (messageMapAck.size() > maxCCU * 20) {
			messageMapAckMutex.unlock();
			throw NetworkServerException("message queue ack overflow");
		}
		// 	push to message queue ack
		// 	create message ack
		auto messageAck = new Message();
		*messageAck = *message;
		messageMapAck[messageId] = messageAck;
		messageMapAckMutex.unlock();
	}

	// push to message queue
	messageQueueMutex.lock();

	//	check if message queue is full
	if (messageQueue.size() > maxCCU * 20) {
		messageQueueMutex.unlock();
		throw NetworkServerException("message queue overflow");
	}
	messageQueue.push(message.release());

	// set nio interest
	if (messageQueue.size() == 1) {
		kem.setSocketInterest(
			socket.get(),
			NIO_INTEREST_READ,
			NIO_INTEREST_READ | NIO_INTEREST_WRITE,
			nullptr
		);
	}

	// done
	messageQueueMutex.unlock();
}

void UDPServerIOThread::processAckReceived(UDPServerClient* client, const uint32_t messageId) {
	bool messageAckValid = true;

	// delete message from message queue ack
	messageMapAckMutex.lock();
	auto it = messageMapAck.find(messageId);
	if (it != messageMapAck.end()) {
		// message exists
		auto messageAck = it->second;
		// message ack valid?
		messageAckValid = messageAck->ip == client->ip && messageAck->port == client->port;
		// remove if valid
		if (messageAckValid == true) {
			// remove message from message queue ack
			delete it->second;
			messageMapAck.erase(it);
		}
	}
	messageMapAckMutex.unlock();

	//
	client->releaseReference();

	// check if message ack was valid
	if (messageAckValid == false) {
		throw NetworkServerException("message ack invalid");
	}
}

void UDPServerIOThread::processAckMessages() {
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

			// recreate packet header with updated hash and retries
			UDPPacket packet;
			packet.putBytes((const uint8_t*)message->message, message->bytes);
			packet.reset();
			server->writeHeader(&packet, (UDPServer::MessageType)message->messageType, message->clientId, message->messageId, message->retries);
			packet.getBytes((uint8_t*)message->message, message->bytes);

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
					socket.get(),
					NIO_INTEREST_READ,
					NIO_INTEREST_READ | NIO_INTEREST_WRITE,
					nullptr
				);
			}
		} while (messageQueueResend.empty() == false);
		messageQueueMutex.unlock();
	}
}

#include <string.h>

#include <map>
#include <string>
#include <typeinfo>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/ServerRequest.h>
#include <tdme/network/udpserver/UDPServerIOThread.h>
#include <tdme/network/udpserver/UDPServerPacket.h>
#include <tdme/os/network/KernelEventMechanism.h>
#include <tdme/os/network/NIOInterest.h>
#include <tdme/os/threading/AtomicOperations.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/RTTI.h>
#include <tdme/utilities/Time.h>

using std::ios_base;
using std::map;
using std::pair;
using std::string;
using std::to_string;

using tdme::network::udpserver::ServerRequest;
using tdme::network::udpserver::UDPServerIOThread;
using tdme::network::udpserver::UDPServerPacket;
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

UDPServerIOThread::UDPServerIOThread(const unsigned int id, UDPServer *server, const unsigned int maxCCU) :
	Thread("nioudpserveriothread"),
	id(id),
	server(server),
	maxCCU(maxCCU),
	messageQueueMutex("nioupserveriothread_messagequeue"),
	messageMapAckMutex("nioupserveriothread_messagequeueack") {
	//
}

void UDPServerIOThread::run() {
	Console::println("UDPServerIOThread[" + to_string(id) + "]::run(): start");

	// wait on startup barrier
	server->startUpBarrier->wait();

	// catch kernel event and server socket exceptions
	try {
		// create server socket
		UDPSocket::createServerSocket(socket, server->host, server->port);

		// initialize kernel event mechanismn
		kem.initKernelEventMechanism(1);
		kem.setSocketInterest(socket, NIO_INTEREST_NONE, NIO_INTEREST_READ, nullptr);

		// do event loop
		uint64_t lastMessageQueueAckTime = Time::getCurrentMillis();
		while(isStopRequested() == false) {
			uint64_t now = Time::getCurrentMillis();

			// process ack messages every 25ms
			if (now >= lastMessageQueueAckTime + 25L) {
				processAckMessages();
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
					string ip;
					unsigned int port;
					char message[512];

					// receive datagrams as long as its size > 0 and read would not block
					while ((bytesReceived = socket.read(ip, port, (void*)message, sizeof(message))) > 0) {
						//
						AtomicOperations::increment(server->statistics.received);

						// process event, catch and handle client related exceptions
						UDPServerClient* client = nullptr;
						UDPServerClient* clientNew = nullptr;
						UDPServerPacket* packet = nullptr;
						try {
							// transfer buffer to string stream
							packet = new UDPServerPacket();
							packet->putBytes((const uint8_t*)message, bytesReceived);
							packet->reset();

							// validate datagram
							server->validate(packet);

							// identify datagram
							UDPServer::MessageType messageType;
							uint32_t clientId;
							uint32_t messageId;
							uint8_t retries;
							server->identify(packet, messageType, clientId, messageId, retries);

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
											delete packet;
											packet = nullptr;
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

										// delete packet
										delete packet;
										packet = nullptr;

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
										client->onFrameReceived(packet, messageId, retries);
										break;
									}
								case(UDPServer::MESSAGETYPE_ACKNOWLEDGEMENT):
									{
										client = server->lookupClient(clientId);
										server->processAckReceived(client, messageId);
										delete packet;
										packet = nullptr;
										break;
									}
								default:
									throw NetworkServerException("Invalid message type");
							}
						} catch(Exception& exception) {
							// delete packet
							if (packet != nullptr) delete packet;

							// log
							Console::println(
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
				while (hasWriteInterest) {
					// fetch batch of messages to be send
					MessageQueue messageQueueBatch;
					messageQueueMutex.lock();
					for (int i = 0; i < MESSAGEQUEUE_SEND_BATCH_SIZE && messageQueue.empty() == false; i++) {
						Message* message = messageQueue.front();
						messageQueueBatch.push(message);
						messageQueue.pop();
					}
					messageQueueMutex.unlock();

					// try to send batch
					while (messageQueueBatch.empty() == false) {
						Message* message = messageQueueBatch.front();
						if (socket.write(message->ip, message->port, (void*)message->message, message->bytes) == -1) {
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
							Message* message = messageQueueBatch.front();
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
	socket.close();

	// log
	Console::println("UDPServerIOThread[" + to_string(id) + "]::run(): done");
}

void UDPServerIOThread::sendMessage(const UDPServerClient* client, const uint8_t messageType, const uint32_t messageId, const UDPServerPacket* packet, const bool safe, const bool deleteFrame) {
	// FIXME:
	//	We could use lock free queues here
	//	For now, we will go with plain mutexes

	// create message
	Message* message = new Message();
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
	if (deleteFrame == true) delete packet;

	// requires ack and retransmission ?
	if (safe == true) {
		messageMapAckMutex.lock();
		MessageMapAck::iterator it;
		// 	check if message has already be pushed to ack
		it = messageMapAck.find(messageId);
		if (it != messageMapAck.end()) {
 			// its on ack queue already, so unlock
			messageMapAckMutex.unlock();
			delete message;
			throw NetworkServerException("message already on message queue ack");
		}
		//	check if message queue is full
		if (messageMapAck.size() > maxCCU * 20) {
			messageMapAckMutex.unlock();
			delete message;
			throw NetworkServerException("message queue ack overflow");
		}
		// 	push to message queue ack
		// 	create message ack
		Message* messageAck = new Message();
		*messageAck = *message;
		messageMapAck.insert(it, pair<uint32_t, Message*>(messageId, messageAck));
		messageMapAckMutex.unlock();
	}

	// push to message queue
	messageQueueMutex.lock();

	//	check if message queue is full
	if (messageQueue.size() > maxCCU * 20) {
		messageQueueMutex.unlock();
		delete message;
		throw NetworkServerException("message queue overflow");
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

void UDPServerIOThread::processAckReceived(UDPServerClient* client, const uint32_t messageId) {
	bool messageAckValid = true;
	MessageMapAck::iterator iterator;

	// delete message from message queue ack
	messageMapAckMutex.lock();
	iterator = messageMapAck.find(messageId);
	if (iterator != messageMapAck.end()) {
		// message exists
		Message* messageAck = iterator->second;
		// message ack valid?
		messageAckValid = messageAck->ip == client->ip && messageAck->port == client->port;
		// remove if valid
		if (messageAckValid == true) {
			// remove message from message queue ack
			delete iterator->second;
			messageMapAck.erase(iterator);
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
	uint64_t now = Time::getCurrentMillis();

	messageMapAckMutex.lock();
	MessageMapAck::iterator it = messageMapAck.begin();
	while (it != messageMapAck.end()) {
		Message* messageAck = it->second;
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
			Message* message = new Message();
			*message = *messageAck;

			// recreate packet header with updated hash and retries
			UDPServerPacket packet;
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
			Message* message = messageQueueResend.front();
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

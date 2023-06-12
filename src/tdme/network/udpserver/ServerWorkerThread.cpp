#include <exception>
#include <string>
#include <typeinfo>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/ServerClient.h>
#include <tdme/network/udpserver/ServerGroup.h>
#include <tdme/network/udpserver/ServerWorkerThread.h>
#include <tdme/network/udpserver/ServerWorkerThreadPool.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/RTTI.h>

using std::string;
using std::to_string;

using tdme::network::udpserver::ServerClient;
using tdme::network::udpserver::ServerGroup;
using tdme::network::udpserver::ServerWorkerThread;
using tdme::network::udpserver::ServerWorkerThreadPool;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::RTTI;

ServerWorkerThread::ServerWorkerThread(const unsigned int id, ServerWorkerThreadPool* threadPool) :
	Thread("nioworkerthread"),
	id(id),
	threadPool(threadPool) {
	//
}

ServerWorkerThread::~ServerWorkerThread() {
}

void ServerWorkerThread::run() {
	Console::println("ServerWorkerThread[" + to_string(id) + "]::run(): start");

	// wait on startup barrier
	threadPool->startUpBarrier->wait();

	ServerRequest* request;
	while ((request = threadPool->getElement()) != nullptr) {
		// get request parameter
		auto requestType = request->getRequestType();
		ServerClient* client = nullptr;
		ServerGroupBase* group = nullptr;

		// handle request types
		switch(requestType) {
			case(ServerRequest::REQUESTTYPE_CLIENT_REQUEST): {
				client = static_cast<ServerClient*>(request->getObject());
				auto packet = request->getMessagePacket();
				auto messageId = request->getMessageId();
				auto retries = request->getMessageRetries();

				// handle request
				try {
					client->onRequest(packet, messageId, retries);
				} catch(Exception& exception) {
					Console::println(
						"ServerWorkerThread[" +
						to_string(id) +
						"]::run(): client: request: " +
						(RTTI::demangle(typeid(exception).name())) +
						": " +
						(exception.what())
					);

					// unhandled exception, so shutdown the client
					client->shutdown();
				}

				// delete stream
				delete packet;

				//
				break;
			}
			case(ServerRequest::REQUESTTYPE_CLIENT_INIT): {
				client = static_cast<ServerClient*>(request->getObject());
				// handle close
				try {
					client->onInit();
				} catch(Exception& exception) {
					Console::println(
						"ServerWorkerThread[" +
						to_string(id) +
						"]::run(): client: init: " +
						(RTTI::demangle(typeid(exception).name())) +
						": " +
						(exception.what())
					);
				}
				break;
			}
			case(ServerRequest::REQUESTTYPE_CLIENT_CLOSE): {
				client = static_cast<ServerClient*>(request->getObject());
				// handle close
				try {
					client->onClose();
				} catch(Exception& exception) {
					Console::println(
						"ServerWorkerThread[" +
						to_string(id) +
						"]::run(): client: close: " +
						(RTTI::demangle(typeid(exception).name())) +
						": " +
						(exception.what())
					);
				}
				break;
			}
			case(ServerRequest::REQUESTTYPE_CLIENT_CUSTOM): {
				client = static_cast<ServerClient*>(request->getObject());
				// handle close
				try {
					client->onCustom(request->getCustomEvent());
				} catch(Exception& exception) {
					Console::println(
						"ServerWorkerThread[" +
						to_string(id) +
						"]::run(): client: custom: " +
						(RTTI::demangle(typeid(exception).name())) +
						": " +
						(exception.what())
					);
				}
				break;
			}
			case(ServerRequest::REQUESTTYPE_GROUP_INIT): {
				group = static_cast<ServerGroupBase*>(request->getObject());
				// handle close
				try {
					group->onInit();
				} catch(Exception& exception) {
					Console::println(
						"ServerWorkerThread[" +
						to_string(id) +
						"]::run(): group: init: " +
						(RTTI::demangle(typeid(exception).name())) +
						": " +
						(exception.what())
					);
				}
				break;
			}
			case(ServerRequest::REQUESTTYPE_GROUP_CLOSE): {
				group = static_cast<ServerGroupBase*>(request->getObject());
				// handle close
				try {
					group->onClose();
				} catch(Exception& exception) {
					Console::println(
						"ServerWorkerThread[" +
						to_string(id) +
						"]::run(): group: close: " +
						(RTTI::demangle(typeid(exception).name())) +
						": " +
						(exception.what())
					);
				}
				break;
			}
			case(ServerRequest::REQUESTTYPE_GROUP_CUSTOM): {
				group = static_cast<ServerGroupBase*>(request->getObject());
				// handle close
				try {
					group->onCustomEvent(request->getCustomEvent());
				} catch(Exception& exception) {
					Console::println(
						"ServerWorkerThread[" +
						to_string(id) +
						"]::run(): group: custom: " +
						(RTTI::demangle(typeid(exception).name())) +
						": " +
						(exception.what())
					);
				}
				break;
			}
		}

		// release reference
		if (client != nullptr) client->releaseReference();
		if (group != nullptr) group->releaseReference();

		// delete request
		delete(request);
	}

	//
	Console::println("ServerWorkerThread[" + to_string(id) + "]::run(): done");
}

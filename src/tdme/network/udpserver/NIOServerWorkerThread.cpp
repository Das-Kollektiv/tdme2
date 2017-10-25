#include <exception>
#include <typeinfo>
#include <string>

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/RTTI.h>
#include <tdme/network/udpserver/fwd-tdme.h>
#include <tdme/network/udpserver/NIOServerClient.h>
#include <tdme/network/udpserver/NIOServerGroup.h>
#include <tdme/network/udpserver/NIOServerWorkerThread.h>

using std::string;
using std::to_string;

using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::RTTI;
using tdme::network::udpserver::NIOServerClient;
using tdme::network::udpserver::NIOServerGroup;
using tdme::network::udpserver::NIOServerWorkerThread;

NIOServerWorkerThread::NIOServerWorkerThread(const unsigned int id, NIOServerWorkerThreadPool* threadPool) :
	Thread("nioworkerthread"),
	id(id),
	threadPool(threadPool) {
	//
}

NIOServerWorkerThread::~NIOServerWorkerThread() {
}

void NIOServerWorkerThread::run() {
	Console::println("ServerWorkerThread[" + to_string(id) + "]::run(): start");

	// wait on startup barrier
	threadPool->startUpBarrier->wait();

	NIOServerRequest* request;
	while((request = threadPool->getElement()) != NULL) {
		// get request parameter
		NIOServerRequest::RequestType requestType = request->getRequestType();
		NIOServerClient* client = NULL;
		NIOServerGroupBase* group = NULL;

		// handle request types
		switch(requestType) {
			case(NIOServerRequest::REQUESTTYPE_CLIENT_REQUEST): {
				client = (NIOServerClient*)request->getObject();
				stringstream* frame = request->getMessageFrame();
				uint32_t messageId = request->getMessageId();
				uint8_t retries = request->getMessageRetries();

				// handle request
				try {
					client->onRequest(frame, messageId, retries);
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
				delete frame;

				//
				break;
			}
			case(NIOServerRequest::REQUESTTYPE_CLIENT_INIT): {
				client = (NIOServerClient*)request->getObject();
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
			case(NIOServerRequest::REQUESTTYPE_CLIENT_CLOSE): {
				client = (NIOServerClient*)request->getObject();
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
			case(NIOServerRequest::REQUESTTYPE_CLIENT_CUSTOM): {
				client = (NIOServerClient*)request->getObject();
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
			case(NIOServerRequest::REQUESTTYPE_GROUP_INIT): {
				group = (NIOServerGroupBase*)request->getObject();
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
			case(NIOServerRequest::REQUESTTYPE_GROUP_CLOSE): {
				group = (NIOServerGroupBase*)request->getObject();
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
			case(NIOServerRequest::REQUESTTYPE_GROUP_CUSTOM): {
				group = (NIOServerGroupBase*)request->getObject();
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
		if (client != NULL) client->releaseReference();
		if (group != NULL) group->releaseReference();

		// delete request
		delete(request);
	}

	//
	Console::println("ServerWorkerThread[" + to_string(id) + "]::run(): done");
}

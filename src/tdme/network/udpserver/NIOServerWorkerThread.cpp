#include <exception>
#include <typeinfo>
#include <string>

#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/RTTI.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/network/udpserver/fwd-tdme.h>
#include <tdme/network/udpserver/NIOServerClient.h>
#include <tdme/network/udpserver/NIOServerGroup.h>
#include <tdme/network/udpserver/NIOServerWorkerThread.h>

using std::wstring;
using std::to_wstring;

using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::RTTI;
using tdme::utils::StringConverter;
using tdme::network::udpserver::NIOServerClient;
using tdme::network::udpserver::NIOServerGroup;
using tdme::network::udpserver::NIOServerWorkerThread;

NIOServerWorkerThread::NIOServerWorkerThread(const unsigned int id, NIOServerWorkerThreadPool* threadPool) :
	Thread(L"nioworkerthread"),
	id(id),
	threadPool(threadPool) {
	//
}

NIOServerWorkerThread::~NIOServerWorkerThread() {
}

void NIOServerWorkerThread::run() {
	Console::println(L"ServerWorkerThread[" + to_wstring(id) + L"]::run(): start");

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
						L"ServerWorkerThread[" +
						to_wstring(id) +
						L"]::run(): client: request: " +
						StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
						L": " +
						StringConverter::toWideString(exception.what())
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
						L"ServerWorkerThread[" +
						to_wstring(id) +
						L"]::run(): client: init: " +
						StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
						L": " +
						StringConverter::toWideString(exception.what())
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
						L"ServerWorkerThread[" +
						to_wstring(id) +
						L"]::run(): client: close: " +
						StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
						L": " +
						StringConverter::toWideString(exception.what())
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
						L"ServerWorkerThread[" +
						to_wstring(id) +
						L"]::run(): client: custom: " +
						StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
						L": " +
						StringConverter::toWideString(exception.what())
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
						L"ServerWorkerThread[" +
						to_wstring(id) +
						L"]::run(): group: init: " +
						StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
						L": " +
						StringConverter::toWideString(exception.what())
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
						L"ServerWorkerThread[" +
						to_wstring(id) +
						L"]::run(): group: close: " +
						StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
						L": " +
						StringConverter::toWideString(exception.what())
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
						L"ServerWorkerThread[" +
						to_wstring(id) +
						L"]::run(): group: custom: " +
						StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
						L": " +
						StringConverter::toWideString(exception.what())
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
	Console::println(L"ServerWorkerThread[" + to_wstring(id) + L"]::run(): done");
}

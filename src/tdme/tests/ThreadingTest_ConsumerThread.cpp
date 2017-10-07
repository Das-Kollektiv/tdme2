#include "ThreadingTest_ConsumerThread.h"

#include <string>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/utils/Console.h>

using std::wstring;
using std::to_wstring;

using tdme::os::threading::Thread;
using tdme::os::threading::Queue;
using tdme::utils::Console;

ConsumerThread::ConsumerThread(int id, Queue<int>* queue) : Thread(L"consumer"), id(id), queue(queue) {
}

void ConsumerThread::run() {
	Console::println(L"ConsumerThread[" + to_wstring(id) + L"]::init()");
	while(isStopRequested() == false) {
		int* element = queue->getElement();
		if (element == NULL) {
			break;
		}
		Console::println(L"ConsumerThread[" + to_wstring(id) + L"]: got " + to_wstring(*element) + L" from queue");
		delete element;
		Thread::sleep(100);
	}
	Console::println(L"ConsumerThread[" + to_wstring(id) + L"]::done()");
}

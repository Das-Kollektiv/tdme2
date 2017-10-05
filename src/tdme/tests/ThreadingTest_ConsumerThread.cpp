#include "ThreadingTest_ConsumerThread.h"

#include <string>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/utils/_Console.h>

using std::wstring;
using std::to_wstring;

using tdme::os::threading::Thread;
using tdme::os::threading::Queue;
using tdme::utils::_Console;

ConsumerThread::ConsumerThread(int id, Queue<int>* queue) : Thread(L"consumer"), id(id), queue(queue) {
}

void ConsumerThread::run() {
	_Console::println(L"ConsumerThread[" + to_wstring(id) + L"]::init()");
	while(isStopRequested() == false) {
		int* element = queue->getElement();
		if (element == NULL) {
			break;
		}
		_Console::println(L"ConsumerThread[" + to_wstring(id) + L"]: got " + to_wstring(*element) + L" from queue");
		delete element;
		Thread::sleep(100);
	}
	_Console::println(L"ConsumerThread[" + to_wstring(id) + L"]::done()");
}

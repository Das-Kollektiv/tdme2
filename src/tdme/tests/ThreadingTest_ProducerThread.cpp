#include "ThreadingTest_ProducerThread.h"

#include <string>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/utils/Console.h>

using std::wstring;
using std::to_wstring;

using tdme::os::threading::Thread;
using tdme::os::threading::Queue;
using tdme::utils::Console;

ProducerThread::ProducerThread(int id, Queue<int>* queue) : Thread(L"producer"), id(id), queue(queue) {
}

void ProducerThread::run() {
	Console::println(L"ProducerThread[" + to_wstring(id) + L"]::init()");
	for(int i = 0; isStopRequested() == false; i++) {
		int* element = new int;
		*element = i;
		queue->addElement(element, false);
		Console::println(L"ProducerThread[" + to_wstring(id) + L"]: added " + to_wstring(i) + L" to queue");
		Thread::sleep(50);
	}
	Console::println(L"ProducerThread[" + to_wstring(id) + L"]::done()");
}

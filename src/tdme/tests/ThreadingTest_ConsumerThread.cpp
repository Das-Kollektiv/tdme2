#include "ThreadingTest_ConsumerThread.h"

#include <memory>
#include <string>

#include <tdme/tdme.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::unique_ptr;

using tdme::os::threading::Queue;
using tdme::os::threading::Thread;
using tdme::utilities::Console;

ConsumerThread::ConsumerThread(int id, Queue<int>* queue) : Thread("consumer"), id(id), queue(queue) {
}

void ConsumerThread::run() {
	Console::printLine("ConsumerThread[" + to_string(id) + "]::init()");
	while(isStopRequested() == false) {
		auto element = unique_ptr<int>(queue->getElement());
		if (element == nullptr) break;
		Console::printLine("ConsumerThread[" + to_string(id) + "]: got " + to_string(*element) + " from queue");
		Thread::sleep(100);
	}
	Console::printLine("ConsumerThread[" + to_string(id) + "]::done()");
}

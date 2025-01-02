#include "ThreadingTest_ConsumerThread.h"

#include <memory>
#include <string>

#include <yannet/yannet.h>
#include <yannet/os/threading/Queue.h>
#include <yannet/os/threading/Thread.h>
#include <yannet/utilities/Console.h>

using std::string;
using std::to_string;
using std::unique_ptr;

using yannet::os::threading::Queue;
using yannet::os::threading::Thread;
using yannet::utilities::Console;

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

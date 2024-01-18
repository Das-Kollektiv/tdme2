#include "ThreadingTest_ProducerThread.h"

#include <string>

#include <tdme/tdme.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;

using tdme::os::threading::Queue;
using tdme::os::threading::Thread;
using tdme::utilities::Console;

ProducerThread::ProducerThread(int id, Queue<int>* queue) : Thread("producer"), id(id), queue(queue) {
}

void ProducerThread::run() {
	Console::printLine("ProducerThread[" + to_string(id) + "]::init()");
	for(int i = 0; isStopRequested() == false; i++) {
		auto element = new int;
		*element = i;
		queue->addElement(element, false);
		Console::printLine("ProducerThread[" + to_string(id) + "]: added " + to_string(i) + " to queue");
		Thread::sleep(50);
	}
	Console::printLine("ProducerThread[" + to_string(id) + "]::done()");
}

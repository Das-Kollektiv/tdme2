#include "ThreadingTest_ProducerThread.h"

#include <stdio.h>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Queue.h>

using tdme::os::threading::Thread;
using tdme::os::threading::Queue;

ProducerThread::ProducerThread(int id, Queue<int>* queue) : Thread(L"producer"), id(id), queue(queue) {
}

void ProducerThread::run() {
	printf("ProducerThread[%i]::run()\n", id);
	for(int i = 0; isStopRequested() == false; i++) {
		int* element = new int;
		*element = i;
		queue->addElement(element, false);
		printf("ProducerThread[%i]: added %i to queue\n", id, i);
		Thread::sleep(50);
	}
	printf("ProducerThread[%i]::done()\n", id);
}

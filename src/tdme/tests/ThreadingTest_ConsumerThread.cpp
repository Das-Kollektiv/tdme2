#include "ThreadingTest_ConsumerThread.h"

#include <stdio.h>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Queue.h>

using tdme::os::threading::Thread;
using tdme::os::threading::Queue;

ConsumerThread::ConsumerThread(int id, Queue<int>* queue) : Thread(L"consumer"), id(id), queue(queue) {
}

void ConsumerThread::run() {
	printf("ConsumerThread[%i]::run()\n", id);
	while(isStopRequested() == false) {
		int* element = queue->getElement();
		if (element == NULL) {
			break;
		}
		printf("ConsumerThread[%i]: got %i from queue\n", id, *element);
		Thread::sleep(100);
	}
	printf("ConsumerThread[%i]::done()\n", id);
}

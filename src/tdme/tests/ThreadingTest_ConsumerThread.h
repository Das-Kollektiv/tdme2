#pragma once

#include <tdme/tdme.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>

using tdme::os::threading::Queue;
using tdme::os::threading::Thread;

class ConsumerThread: public Thread {
public:
	// forbid class copy
	FORBID_CLASS_COPY(ConsumerThread)

	//
	ConsumerThread(int id, Queue<int> *queue);

private:
	int id;
	Queue<int> *queue;

	void run();
};

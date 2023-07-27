#pragma once

#include <tdme/tdme.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>

using tdme::os::threading::Queue;
using tdme::os::threading::Thread;

class ProducerThread: public Thread {
public:
	// forbid class copy
	CLASS_FORBID_COPY(ProducerThread)

	//
	ProducerThread(int id, Queue<int> *queue);

private:
	int id;
	Queue<int> *queue;

	void run();
};

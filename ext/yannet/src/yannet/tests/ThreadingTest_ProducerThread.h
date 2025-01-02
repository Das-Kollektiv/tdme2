#pragma once

#include <yannet/yannet.h>
#include <yannet/os/threading/Queue.h>
#include <yannet/os/threading/Thread.h>

using yannet::os::threading::Queue;
using yannet::os::threading::Thread;

class ProducerThread: public Thread {
public:
	// forbid class copy
	FORBID_CLASS_COPY(ProducerThread)

	//
	ProducerThread(int id, Queue<int> *queue);

private:
	int id;
	Queue<int> *queue;

	void run();
};

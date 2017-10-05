#pragma once

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Queue.h>

using tdme::os::threading::Thread;
using tdme::os::threading::Queue;

class ProducerThread: public Thread {
public:
	ProducerThread(int id, Queue<int> *queue);
	void run();

private:
	int id;
	Queue<int> *queue;

};

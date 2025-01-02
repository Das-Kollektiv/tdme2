#include <memory>
#include <string>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/os/threading/AtomicOperations.h>
#include <yannet/os/threading/Queue.h>
#include <yannet/os/threading/Thread.h>
#include <yannet/utilities/Console.h>

#include "ThreadingTest_ConsumerThread.h"
#include "ThreadingTest_ProducerThread.h"
#include "ThreadingTest_SharedData.h"
#include "ThreadingTest_TestThread.h"

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using yannet::os::threading::AtomicOperations;
using yannet::os::threading::Queue;
using yannet::os::threading::Thread;
using yannet::utilities::Console;

#define TESTTHREAD_THREADS_COUNT	4

void testthread_test() {
	// basic thread test
	SharedData data;
	Console::printLine("Hallo World!");
	vector<unique_ptr<TestThread>> tt(TESTTHREAD_THREADS_COUNT);
	// start threads
	for(int i = 0; i < TESTTHREAD_THREADS_COUNT; i++) {
		tt[i] = make_unique<TestThread>(i, &data);
		tt[i]->start();
	}
	// wait until threads are finished
	for(int i = 0; i < TESTTHREAD_THREADS_COUNT; i++) {
		tt[i]->join();
	}
}

void pc_test() {
	// producer, consumer test
	Queue<int> queue(128);
	ProducerThread p(0, &queue);
	ConsumerThread c0(0, &queue);
	ConsumerThread c1(1, &queue);

	Console::printLine("starting consumer threads");
	c0.start();
	c1.start();
	Thread::sleep(500);

	Console::printLine("starting producer thread");
	p.start();

	Console::printLine("waiting 10 seconds");
	Thread::sleep(2000);

	Console::printLine("stopping producer");
	p.stop();
	p.join();

	Thread::sleep(500);
	Console::printLine("stopping consumer and queue");
	c0.stop();
	c1.stop();
	queue.stop();

	c0.join();
	c1.join();
}

void atomic_test() {
	volatile uint32_t intValue = 0;
	// 5 atomic adds
	for(int i = 0; i < 5; i++) {
		Console::printLine("atomic add, result " + to_string(AtomicOperations::increment(intValue)));
	}
	// 5 atomic subs
	for(int i = 0; i < 5; i++) {
		Console::printLine("atomic sub, result " + to_string(AtomicOperations::decrement(intValue)));
	}
}

int main(int argc, char *argv[]) {
	testthread_test();
	pc_test();
	atomic_test();
	//
	Console::shutdown();
	return 0;
}

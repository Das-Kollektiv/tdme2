#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/os/threading/AtomicOperations.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/utilities/Console.h>

#include "ThreadingTest_ConsumerThread.h"
#include "ThreadingTest_ProducerThread.h"
#include "ThreadingTest_SharedData.h"
#include "ThreadingTest_TestThread.h"

using std::make_unique;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using tdme::os::threading::AtomicOperations;
using tdme::os::threading::Queue;
using tdme::os::threading::Thread;
using tdme::utilities::Console;

#define TESTTHREAD_THREADS_COUNT	4

void testthread_test() {
	// basic thread test
	SharedData data;
	Console::println("Hallo World!");
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

	Console::println("starting consumer threads");
	c0.start();
	c1.start();
	Thread::sleep(500);

	Console::println("starting producer thread");
	p.start();

	Console::println("waiting 10 seconds");
	Thread::sleep(2000);

	Console::println("stopping producer");
	p.stop();
	p.join();

	Thread::sleep(500);
	Console::println("stopping consumer and queue");
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
		Console::println("atomic add, result " + to_string(AtomicOperations::increment(intValue)));
	}
	// 5 atomic subs
	for(int i = 0; i < 5; i++) {
		Console::println("atomic sub, result " + to_string(AtomicOperations::decrement(intValue)));
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

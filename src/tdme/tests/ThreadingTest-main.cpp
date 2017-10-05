/**
 * @version $Id: 92052ab3ac232a8ca84ce8f59c9982199a735ca8 $
 */

#include <stdio.h>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Queue.h>
#include "ThreadingTest_ConsumerThread.h"
#include "ThreadingTest_ProducerThread.h"
#include "ThreadingTest_SharedData.h"
#include "ThreadingTest_TestThread.h"

using tdme::os::threading::Thread;
using tdme::os::threading::Queue;

#define TESTTHREAD_THREADS_COUNT	4

void testthread_test() {
	// basic thread test
	SharedData data;
	printf("Hallo World!\n");
	TestThread* tt[TESTTHREAD_THREADS_COUNT];
	// start threads
	for(int i = 0; i < TESTTHREAD_THREADS_COUNT; i++) {
		tt[i] = new TestThread(i, &data);
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

	printf("starting consumer threads\n");
	c0.start();
	c1.start();
	Thread::sleep(500);

	printf("starting producer thread\n");
	p.start();

	printf("waiting 10 seconds\n");
	Thread::sleep(2000);

	printf("stopping producer\n");
	p.stop();
	p.join();

	Thread::sleep(500);
	printf("stopping consumer and queue\n");
	c0.stop();
	c1.stop();
	queue.stop();

	c0.join();
	c1.join();
}

void atomic_test() {
	int intValue = 0;
	// 5 atomic adds
	for(int i = 0; i < 5; i++) {
		printf("atomic add, result %i\n", __sync_add_and_fetch(&intValue,1));
	}
	// 5 atomic subs
	for(int i = 0; i < 5; i++) {
		printf("atomic sub, result %i\n", __sync_sub_and_fetch(&intValue,1));
	}
}

int main(int argc, char *argv[]) {
	testthread_test();
	pc_test();
	atomic_test();
}

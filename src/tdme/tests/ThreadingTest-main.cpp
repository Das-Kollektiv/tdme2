#include <string>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Queue.h>
#include <tdme/utils/_Console.h>

#include "ThreadingTest_ConsumerThread.h"
#include "ThreadingTest_ProducerThread.h"
#include "ThreadingTest_SharedData.h"
#include "ThreadingTest_TestThread.h"

using std::wstring;
using std::to_wstring;

using tdme::os::threading::Thread;
using tdme::os::threading::Queue;
using tdme::utils::_Console;

#define TESTTHREAD_THREADS_COUNT	4

void testthread_test() {
	// basic thread test
	SharedData data;
	_Console::println(L"Hallo World!");
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

	_Console::println(L"starting consumer threads");
	c0.start();
	c1.start();
	Thread::sleep(500);

	_Console::println(L"starting producer thread");
	p.start();

	_Console::println(L"waiting 10 seconds");
	Thread::sleep(2000);

	_Console::println(L"stopping producer");
	p.stop();
	p.join();

	Thread::sleep(500);
	_Console::println(L"stopping consumer and queue");
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
		_Console::println(L"atomic add, result " + to_wstring(__sync_add_and_fetch(&intValue,1)));
	}
	// 5 atomic subs
	for(int i = 0; i < 5; i++) {
		_Console::println(L"atomic sub, result " + to_wstring(__sync_sub_and_fetch(&intValue,1)));
	}
}

int main(int argc, char *argv[]) {
	testthread_test();
	pc_test();
	atomic_test();
}

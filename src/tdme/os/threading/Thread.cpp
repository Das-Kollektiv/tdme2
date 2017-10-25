/**
 * @version $Id: aa3465de5134eac90f5c600a66a33e052df4613d $
 */

#include <unistd.h>
#include <string>
#include <iostream>

#include "Thread.h"
#include "ThreadingError.h"

using std::string;

using tdme::os::threading::Thread;

Thread::Thread(const string& name): name(name), pThreadCreated(false), stopRequested(false) {
}

Thread::~Thread() {
}

void Thread::sleep(const uint64_t milliseconds) {
	uint64_t secondsWaited = 0L;
	while (milliseconds - (secondsWaited * 1000L) >= 1000L) {
		::sleep(1);
		secondsWaited++;
	}
	usleep((milliseconds - (secondsWaited * 1000L)) * 1000L);
}

void Thread::join() {
	void* status;
	int result = pthread_join(pThread, &status);
	PTHREAD_CHECK_ERROR(name, "Could not join pthread", "pthread_join");
}

void Thread::start() {
	// set up thread attributes
	pthread_attr_t pThreadAttr;
	pthread_attr_init(&pThreadAttr);
	// joinable state
	pthread_attr_setdetachstate(&pThreadAttr, PTHREAD_CREATE_JOINABLE);

	// create thread
	int result = pthread_create(&pThread, &pThreadAttr, &pThreadRun, (void*)this);
	PTHREAD_CHECK_ERROR(name, "Could not create pthread", "pthread_create");
}

void *Thread::pThreadRun(void *thread) {
	static_cast<Thread*>(thread)->run();
	pthread_exit(NULL);
	return NULL;
}

void Thread::stop() {
	stopRequested = true;
}

bool Thread::isStopRequested() {
	return stopRequested;
} 


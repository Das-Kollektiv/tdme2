/**
 * @version $Id: dc7188d5dbac05e6d033576a7a08e8eef01785b3 $
 */

#include "Condition.h"
#include "ThreadingError.h"

using std::string;
using tdme::os::threading::Condition;
using tdme::os::threading::Mutex;

Condition::Condition(const string& name) {
	this->name = name;
	int result = pthread_cond_init (&pThreadCond, NULL);
	PTHREAD_CHECK_ERROR(name, "Could not init condition", "pthread_cond_init");
}

Condition::~Condition() {
	int result = pthread_cond_destroy(&pThreadCond);
	PTHREAD_CHECK_ERROR(name, "Could not destroy condition", "pthread_cond_destroy");
}

void Condition::signal() {
	int result = pthread_cond_signal(&pThreadCond);
	PTHREAD_CHECK_ERROR(name, "Could not signal condition", "pthread_cond_signal");
}

void Condition::broadcast() {
	int result = pthread_cond_broadcast(&pThreadCond);
	PTHREAD_CHECK_ERROR(name, "Could not broadcast condition", "pthread_cond_broadcast");
}

void Condition::wait(Mutex &mutex) {
	int result = pthread_cond_wait(&pThreadCond, &(mutex.pThreadMutex));
	PTHREAD_CHECK_ERROR(name, "Could not wait on condition", "pthread_cond_wait");
}

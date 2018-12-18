/**
 * @version $Id: 1a286d86b29cabf8420205519e524a885c74a8d7 $
 */

#include <errno.h>

#include "Mutex.h"
#include "ThreadingError.h"

using tdme::os::threading::Mutex;

Mutex::Mutex(const string& name) {
	this->name = name;
	int result = pthread_mutex_init(&pThreadMutex, NULL);
	PTHREAD_CHECK_ERROR(name, "Could not init mutex", "pthread_mutex_init");
}

Mutex::~Mutex() {
	int result = pthread_mutex_destroy(&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, "Could not destroy mutex", "pthread_mutex_destroy");
}

bool Mutex::tryLock() {
	int result = pthread_mutex_trylock(&pThreadMutex);
	if (result != EBUSY) {
		PTHREAD_CHECK_ERROR(name, "Could not try lock mutex", "pthread_mutex_trylock");
	}
	return result == 0;
}

void Mutex::lock() {
	int result = pthread_mutex_lock(&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, "Could not lock mutex", "pthread_mutex_lock");
}

void Mutex::unlock() {
	int result = pthread_mutex_unlock (&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, "Could not unlock mutex", "pthread_mutex_unlock");
}

/**
 * @version $Id: 1a286d86b29cabf8420205519e524a885c74a8d7 $
 */

#include "Mutex.h"
#include "ThreadingError.h"

using tdme::os::threading::Mutex;

Mutex::Mutex(const wstring& name) {
	this->name = name;
	int result = pthread_mutex_init(&pThreadMutex, NULL);
	PTHREAD_CHECK_ERROR(name, L"Could not init mutex", L"pthread_mutex_init");
}

Mutex::~Mutex() {
	int result = pthread_mutex_destroy(&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, L"Could not destroy mutex", L"pthread_mutex_destroy");
}

void Mutex::lock() {
	int result = pthread_mutex_lock(&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, L"Could not lock mutex", L"pthread_mutex_lock");
}

void Mutex::unlock() {
	int result = pthread_mutex_unlock (&pThreadMutex);
	PTHREAD_CHECK_ERROR(name, L"Could not unlock mutex", L"pthread_mutex_unlock");
}

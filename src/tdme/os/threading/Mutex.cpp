#include <tdme/os/threading/Mutex.h>

#include <errno.h>

#include <tdme/tdme.h>
#include <tdme/os/threading/ThreadingError.h>

using tdme::os::threading::Mutex;

Mutex::Mutex(const string& name) {
	this->name = name;
	#if defined(CPPTHREADS)
	#else
		auto result = pthread_mutex_init(&pThreadMutex, NULL);
		PTHREAD_CHECK_ERROR(name, "Could not init mutex", "pthread_mutex_init");
	#endif
}

Mutex::~Mutex() {
	#if defined(CPPTHREADS)
	#else
		auto result = pthread_mutex_destroy(&pThreadMutex);
		PTHREAD_CHECK_ERROR(name, "Could not destroy mutex", "pthread_mutex_destroy");
	#endif
}

bool Mutex::tryLock() {
	#if defined(CPPTHREADS)
		return mutex.try_lock();
	#else
		auto result = pthread_mutex_trylock(&pThreadMutex);
		if (result != EBUSY) {
			PTHREAD_CHECK_ERROR(name, "Could not try lock mutex", "pthread_mutex_trylock");
		}
		return result == 0;
	#endif
}

void Mutex::lock() {
	#if defined(CPPTHREADS)
		mutex.lock();
	#else
		auto result = pthread_mutex_lock(&pThreadMutex);
		PTHREAD_CHECK_ERROR(name, "Could not lock mutex", "pthread_mutex_lock");
	#endif
}

void Mutex::unlock() {
	#if defined(CPPTHREADS)
		mutex.unlock();
	#else
		auto result = pthread_mutex_unlock (&pThreadMutex);
		PTHREAD_CHECK_ERROR(name, "Could not unlock mutex", "pthread_mutex_unlock");
	#endif
}

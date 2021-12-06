#include <tdme/os/threading/ReadWriteLock.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/os/threading/ThreadingError.h>

using std::string;

using tdme::os::threading::ReadWriteLock;

ReadWriteLock::ReadWriteLock(const string& name) {
	this->name = name;
	#if defined(CPPTHREADS)
	#else
		auto result = pthread_rwlock_init(&pReadWriteLock, NULL);
		PTHREAD_CHECK_ERROR(name, "Could not init read write lock", "pthread_rwlock_init");
	#endif
}

ReadWriteLock::~ReadWriteLock() {
	#if defined(CPPTHREADS)
	#else
		auto result = pthread_rwlock_destroy(&pReadWriteLock);
		PTHREAD_CHECK_ERROR(name, "Could not destroy read write lock", "pthread_rwlock_destroy");
	#endif
}

void ReadWriteLock::readLock() {
	#if defined(CPPTHREADS)
		sharedMutex.lock_shared();
	#else
		auto result = pthread_rwlock_rdlock(&pReadWriteLock);
		PTHREAD_CHECK_ERROR(name, "Could not issue read lock", "pthread_rwlock_rdlock");
	#endif
}

void ReadWriteLock::writeLock() {
	#if defined(CPPTHREADS)
		sharedMutex.lock();
	#else
		auto result = pthread_rwlock_wrlock(&pReadWriteLock);
		PTHREAD_CHECK_ERROR(name, "Could not issue write lock", "pthread_rwlock_wrlock");
	#endif
}

void ReadWriteLock::unlock() {
	#if defined(CPPTHREADS)
		sharedMutex.unlock();
	#else
		auto result = pthread_rwlock_unlock(&pReadWriteLock);
		PTHREAD_CHECK_ERROR(name, "Could not unlock read write lock", "pthread_rwlock_unlock");
	#endif
}

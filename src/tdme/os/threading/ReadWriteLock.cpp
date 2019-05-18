/**
 * @version $Id: 76eca42568d4a04693701f88bbd6ec6670ba738c $
 */

#include <string>

#include "ReadWriteLock.h"
#include "ThreadingError.h"

using std::string;

using tdme::os::threading::ReadWriteLock;

ReadWriteLock::ReadWriteLock(const string& name) {
	this->name = name;
	#if defined(CPPTHREADS)
	#else
		int result = pthread_rwlock_init(&pReadWriteLock, NULL);
		PTHREAD_CHECK_ERROR(name, "Could not init read write lock", "pthread_rwlock_init");
	#endif
}

ReadWriteLock::~ReadWriteLock() {
	#if defined(CPPTHREADS)
	#else
		int result = pthread_rwlock_destroy(&pReadWriteLock);
		PTHREAD_CHECK_ERROR(name, "Could not destroy read write lock", "pthread_rwlock_destroy");
	#endif
}

void ReadWriteLock::readLock() {
	#if defined(CPPTHREADS)
		sharedMutex.lock_shared();
	#else
		int result = pthread_rwlock_rdlock(&pReadWriteLock);
		PTHREAD_CHECK_ERROR(name, "Could not issue read lock", "pthread_rwlock_rdlock");
	#endif
}

void ReadWriteLock::writeLock() {
	#if defined(CPPTHREADS)
		sharedMutex.lock();
	#else
		int result = pthread_rwlock_wrlock(&pReadWriteLock);
		PTHREAD_CHECK_ERROR(name, "Could not issue write lock", "pthread_rwlock_wrlock");
	#endif
}

void ReadWriteLock::unlock() {
	#if defined(CPPTHREADS)
		sharedMutex.unlock();
	#else
		int result = pthread_rwlock_unlock(&pReadWriteLock);
		PTHREAD_CHECK_ERROR(name, "Could not unlock read write lock", "pthread_rwlock_unlock");
	#endif
}

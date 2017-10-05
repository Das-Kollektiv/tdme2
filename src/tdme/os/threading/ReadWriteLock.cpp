/**
 * @version $Id: 76eca42568d4a04693701f88bbd6ec6670ba738c $
 */

#include <string>

#include "ReadWriteLock.h"
#include "ThreadingError.h"

using std::wstring;

using tdme::os::threading::ReadWriteLock;

ReadWriteLock::ReadWriteLock(const wstring& name) {
	this->name = name;
	int result = pthread_rwlock_init(&pReadWriteLock, NULL);
	PTHREAD_CHECK_ERROR(name, L"Could not init read write lock", L"pthread_rwlock_init");
}

ReadWriteLock::~ReadWriteLock() {
	int result = pthread_rwlock_destroy(&pReadWriteLock);
	PTHREAD_CHECK_ERROR(name, L"Could not destroy read write lock", L"pthread_rwlock_destroy");
}

void ReadWriteLock::readLock() {
	int result = pthread_rwlock_rdlock(&pReadWriteLock);
	PTHREAD_CHECK_ERROR(name, L"Could not issue read lock", L"pthread_rwlock_rdlock");
}

void ReadWriteLock::writeLock() {
	int result = pthread_rwlock_wrlock(&pReadWriteLock);
	PTHREAD_CHECK_ERROR(name, L"Could not issue write lock", L"pthread_rwlock_wrlock");
}

void ReadWriteLock::unlock() {
	int result = pthread_rwlock_unlock(&pReadWriteLock);
	PTHREAD_CHECK_ERROR(name, L"Could not unlock read write lock", L"pthread_rwlock_unlock");
}

/**
 * @version $Id: 1a286d86b29cabf8420205519e524a885c74a8d7 $
 */

#include <errno.h>

#include "SpinLock.h"
#include "ThreadingError.h"

using tdme::os::threading::SpinLock;

SpinLock::SpinLock(const string& name) {
	this->name = name;
	auto result = pthread_spin_init(&pThreadSpinLock, PTHREAD_PROCESS_PRIVATE);
	PTHREAD_CHECK_ERROR(name, "Could not init spinlock", "pthread_spinlock_init");
}

SpinLock::~SpinLock() {
	auto result = pthread_spin_destroy(&pThreadSpinLock);
	PTHREAD_CHECK_ERROR(name, "Could not destroy spinlock", "pthread_spinlock_destroy");
}

bool SpinLock::tryLock() {
	auto result = pthread_spin_trylock(&pThreadSpinLock);
	if (result != EBUSY) {
		PTHREAD_CHECK_ERROR(name, "Could not try lock spinlock", "pthread_spinlock_trylock");
	}
	return result == 0;
}

void SpinLock::lock() {
	auto result = pthread_spin_lock(&pThreadSpinLock);
	PTHREAD_CHECK_ERROR(name, "Could not lock spinlock", "pthread_spinlock_lock");
}

void SpinLock::unlock() {
	auto result = pthread_spin_unlock (&pThreadSpinLock);
	PTHREAD_CHECK_ERROR(name, "Could not unlock spinlock", "pthread_spinlock_unlock");
}

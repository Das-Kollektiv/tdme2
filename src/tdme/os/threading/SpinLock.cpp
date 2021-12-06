#include <tdme/os/threading/SpinLock.h>

#include <errno.h>

#include <atomic>

#include <tdme/tdme.h>

using tdme::os::threading::SpinLock;

using std::atomic_flag;

SpinLock::SpinLock(const string& name) {
	this->name = name;
}

SpinLock::~SpinLock() {
}

bool SpinLock::tryLock() {
	if (locked.test_and_set(std::memory_order_acquire) == false) return true;
	return false;
}

void SpinLock::lock() {
	while (locked.test_and_set(std::memory_order_acquire));
}

void SpinLock::unlock() {
	locked.clear(std::memory_order_release);
}

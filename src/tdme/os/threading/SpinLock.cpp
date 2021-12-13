#include <tdme/os/threading/SpinLock.h>

#include <atomic>

#include <tdme/tdme.h>

using tdme::os::threading::SpinLock;

using std::atomic_flag;

SpinLock::SpinLock(const string& name) {
	this->name = name;
}

SpinLock::~SpinLock() {
}

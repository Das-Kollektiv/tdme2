#include <agui/os/threading/Barrier.h>

#include <agui/agui.h>
#include <agui/os/threading/AtomicOperations.h>
#include <agui/os/threading/Mutex.h>

using std::string;

using agui::os::threading::Barrier;

using agui::os::threading::AtomicOperations;
using agui::os::threading::Mutex;

Barrier::~Barrier() {
	// wait until all threads entered the barrier
	m.lock();
	while (entered < count) {
		c.wait(m);
	}
	m.unlock();

	// spin until all exited
	while (exited < count) {
		//
	}
}

bool Barrier::wait() {
	m.lock();

	// one thread entered the barrier
	AtomicOperations::increment(entered);

	// did we reach barrier?
	if (entered == count) {
		// broadcast all threads waiting on condition
		c.broadcast();
		m.unlock();

		// notify exited thread
		AtomicOperations::increment(exited);

		// exit
		return true;
	} else {
		// wait until barrier is reached
		while (entered < count) {
			c.wait(m);
		}
		m.unlock();

		// notify exited thread
		AtomicOperations::increment(exited);

		//
		return false;
	}
}

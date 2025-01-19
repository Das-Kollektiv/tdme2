#pragma once

#include <agui/os/threading/fwd-agui.h>

#include <agui/agui.h>

#include <atomic>
#include <string>

using std::atomic_flag;
using std::string;

/**
 * Spin Lock implementation.
 * @author Andreas Drewke
 */
class agui::os::threading::SpinLock {
public:
	// forbid class copy
	FORBID_CLASS_COPY(SpinLock)

	/**
	 * @brief Public constructor
	 * @param name name
	 */
	inline SpinLock(const string& name): name(name) {}

	/**
	 * @brief Destroys the spin lock
	 */
	inline ~SpinLock() {}

	/**
	 * @brief Tries to locks the spin lock
	 */
	inline bool tryLock() {
		if (locked.test_and_set(std::memory_order_acquire) == false) return true;
		return false;
	}

	/**
	 * @brief Locks the spin lock, additionally spin lock locks will block until other locks have been unlocked.
	 */
	inline void lock() {
		while (locked.test_and_set(std::memory_order_acquire));
	}

	/**
	 * @brief Unlocks this spin lock
	 */
	inline void unlock() {
		locked.clear(std::memory_order_release);
	}

private:
	string name;
	atomic_flag locked = ATOMIC_FLAG_INIT;
};

#pragma once

#include <tdme/os/threading/fwd-tdme.h>

#include <tdme/tdme.h>

#include <mutex>
#include <string>

using std::mutex;
using std::string;

/**
 * Mutex implementation.
 * Mutexes are used to ensure that only one process can run a critical section,
 * which is e.g. modifying shared data between thread.
 * @author Andreas Drewke
 */
class tdme::os::threading::Mutex {
	friend class Condition;

public:
	/**
	 * @brief Public constructor
	 * @param name name
	 */
	inline Mutex(const string& name): name(name) {};

	/**
	 * @brief Destroys the mutex
	 */
	inline ~Mutex() {}

	/**
	 * @brief Tries to locks the mutex
	 */
	inline bool tryLock() {
		return mutex.try_lock();
	}

	/**
	 * @brief Locks the mutex, additionally mutex locks will block until other locks have been unlocked.
	 */
	inline void lock() {
		mutex.lock();
	}

	/**
	 * @brief Unlocks this mutex
	 */
	inline void unlock() {
		mutex.unlock();
	}

private:
	string name;
	mutex mutex;
};

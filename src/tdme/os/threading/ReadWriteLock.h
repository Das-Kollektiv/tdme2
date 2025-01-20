#pragma once

#include <tdme/tdme.h>
#include <tdme/os/threading/fwd-tdme.h>


#include <shared_mutex>
#include <string>

using std::shared_mutex;
using std::string;

/**
 * Implementation for read/write lock
 * @author Andreas Drewke
 */
class tdme::os::threading::ReadWriteLock {
public:
	// forbid class copy
	FORBID_CLASS_COPY(ReadWriteLock)

	/**
	 * @brief Public constructor
	 * @param name name
	 */
	inline ReadWriteLock(const string& name): name(name) {}

	/**
	 * @brief Destroys the read write lock
	 */
	inline ~ReadWriteLock() {}

	/**
	 * @brief Locks for reading / shared lock
	 */
	inline void readLock() {
		stlSharedMutex.lock_shared();
	}

	/**
	 * @brief Locks for writing / exclusive lock
	 */
	inline void writeLock() {
		stlSharedMutex.lock();
	}

	/**
	 * @brief Unlocks this read write lock
	 */
	inline void unlock() {
		stlSharedMutex.unlock();
	}

private:
	string name;
	shared_mutex stlSharedMutex;
};

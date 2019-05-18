#pragma once

#include "fwd-tdme.h"

#if defined(CPPTHREADS)
	#include <shared_mutex>
	using std::shared_mutex;
#else
	#include <pthread.h>
#endif

#include <string>

using std::string;

/**
 * Implementation for read/write lock
 * @author Andreas Drewke
 */
class tdme::os::threading::ReadWriteLock {
public:
	/**
	 * @brief Public constructor
	 * @param name name
	 */
	ReadWriteLock(const string& name);

	/**
	 * @brief Destroys the read write lock
	 */
	~ReadWriteLock();

	/**
	 * @brief Locks for reading / shared lock
	 */
	void readLock();

	/**
	 * @brief Locks for writing / exclusive lock
	 */
	void writeLock();

	/**
	 * @brief Unlocks this read write lock
	 */
	void unlock();
private:
	string name;
	#if defined(CPPTHREADS)
		shared_mutex sharedMutex;
	#else
		pthread_rwlock_t pReadWriteLock;
	#endif
};

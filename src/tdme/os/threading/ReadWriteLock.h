#pragma once

#include "fwd-tdme.h"

#include <pthread.h>

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
	 * @param name
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
	pthread_rwlock_t pReadWriteLock;
};

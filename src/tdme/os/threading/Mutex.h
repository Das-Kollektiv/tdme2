#pragma once

#include "fwd-tdme.h"

#include <pthread.h>

#include <string>

#include "Condition.h"

using std::wstring;

using tdme::os::threading::Condition;

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
	 * @param name
	 */
	Mutex(const wstring& name);

	/**
	 * @brief Destroys the mutex
	 */
	~Mutex();

	/**
	 * @brief Locks the mutex, additionally mutex locks will block until other locks have been unlocked.
	 */
	void lock();

	/**
	 * @brief Unlocks this mutex
	 */
	void unlock();

private:
	wstring name;
	pthread_mutex_t pThreadMutex;

};

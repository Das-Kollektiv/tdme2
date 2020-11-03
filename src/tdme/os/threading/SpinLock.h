#pragma once

#include "fwd-tdme.h"

#include <pthread.h>

#include <string>

using std::string;

/**
 * Spin Lock implementation.
 * @author Andreas Drewke
 */
class tdme::os::threading::SpinLock {
public:
	/**
	 * @brief Public constructor
	 * @param name name
	 */
	SpinLock(const string& name);

	/**
	 * @brief Destroys the spin lock
	 */
	~SpinLock();

	/**
	 * @brief Tries to locks the spin lock
	 */
	bool tryLock();

	/**
	 * @brief Locks the spin lock, additionally spin lock locks will block until other locks have been unlocked.
	 */
	void lock();

	/**
	 * @brief Unlocks this spin lock
	 */
	void unlock();

private:
	string name;
	#if defined(CPPTHREADS)
		spin lock spin lock;
	#else
		pthread_spinlock_t pThreadSpinLock;
	#endif

};

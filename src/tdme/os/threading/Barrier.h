#pragma once

#include "fwd-tdme.h"

#include <pthread.h>
#include <string>

#include "Mutex.h"
#include "Condition.h"

using std::string;

using tdme::os::threading::Mutex;
using tdme::os::threading::Condition;

/**
 * Barrier implementation.
 * @author Andreas Drewke
 */
class tdme::os::threading::Barrier {
public:
	/**
	 * @brief Public constructor
	 * @param name name
	 * @param count Number of threads that need to "wait" on barrier to complete barrier
	 */
	Barrier(const string& name, const unsigned int count);

	/**
	 * @brief Destroys the barrier
	 */
	~Barrier();

	/**
	 * @brief Waits on barrier
	 * @return bool if caller thread is selected for updating shared data
	 */
	bool wait();

private:
	string name;
	unsigned int count;
	unsigned int entered;
	volatile unsigned int exited;
	Mutex m;
	Condition c;
};

#pragma once

#include "fwd-tdme.h"

#include <pthread.h>
#include <string>

#include "Mutex.h"
#include "Condition.h"

using std::wstring;

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
	 * @param name
	 * @param Number of threads that need to "wait" on barrier to complete barrier
	 */
	Barrier(const wstring& name, const unsigned int count);

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
	wstring name;
	unsigned int count;
	unsigned int entered;
	volatile unsigned int exited;
	Mutex m;
	Condition c;
};

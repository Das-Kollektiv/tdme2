#pragma once

#include <tdme/os/threading/fwd-tdme.h>

#include <tdme/tdme.h>

#include <string>

#include <tdme/os/threading/Condition.h>
#include <tdme/os/threading/Mutex.h>

using std::string;

using tdme::os::threading::Condition;
using tdme::os::threading::Mutex;

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
	inline Barrier(const string& name, const unsigned int count): name(name), count(count), entered(0), exited(0), m("barrier_mutex"), c("barrier_condition") {}

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
	volatile unsigned int entered;
	volatile unsigned int exited;
	Mutex m;
	Condition c;
};

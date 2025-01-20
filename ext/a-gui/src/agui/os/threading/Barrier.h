#pragma once

#include <agui/os/threading/fwd-agui.h>

#include <agui/agui.h>

#include <string>

#include <agui/os/threading/Condition.h>
#include <agui/os/threading/Mutex.h>

using std::string;

/**
 * Barrier implementation.
 * @author Andreas Drewke
 */
class agui::os::threading::Barrier {
public:
	// forbid class copy
	FORBID_CLASS_COPY(Barrier)

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
	 * @returns bool if caller thread is selected for updating shared data
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

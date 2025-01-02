#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/os/threading/fwd-yannet.h>
#include <yannet/os/threading/Condition.h>
#include <yannet/os/threading/Mutex.h>

using std::string;

// name spaces
namespace yannet {
namespace os {
namespace threading {
	using yannet::os::threading::Condition;
	using yannet::os::threading::Mutex;
}
}
}

/**
 * Barrier implementation.
 * @author Andreas Drewke
 */
class yannet::os::threading::Barrier {
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

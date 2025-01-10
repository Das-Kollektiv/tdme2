#pragma once

#include <yannet/yannet.h>
#include <yannet/os/threading/fwd-yannet.h>

#include <condition_variable>
#include <mutex>
#include <string>

#include <yannet/os/threading/Mutex.h>

using std::condition_variable_any;
using std::mutex;
using std::string;

/**
* Threading condition variable implementation
* @author Andreas Drewke
*/
class yannet::os::threading::Condition {
public:
	// forbid class copy
	FORBID_CLASS_COPY(Condition)

	/**
	 * @brief Public constructor, creates condition variable
	 * @param name string
	 */
	inline Condition(const string& name): name(name) {}

	/**
	 * @brief Destructor, removes condition variable
	 */
	inline ~Condition() {}

	/**
	 * @brief wake ups a waiting thread on this condition, associated mutex should protect signal
	 */
	inline void signal() {
		stlCondition.notify_one();
	}

	/**
	 * @brief wake ups all waiting threads on this condition, associated mutex should protect broadcast
	 */
	inline void broadcast() {
		stlCondition.notify_all();
	}

	/**
	 * @brief Blocks current thread until signaled/broadcasted, associated mutex should protect wait
	 */
	inline void wait(Mutex &mutex) {
		stlCondition.wait(mutex.stlMutex);
	}

private:
	string name;
	condition_variable_any stlCondition;
};

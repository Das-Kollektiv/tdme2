#pragma once

#include <tdme/os/threading/fwd-tdme.h>

#include <tdme/tdme.h>

#include <condition_variable>
#include <mutex>
#include <string>

#include <tdme/os/threading/Mutex.h>

using std::condition_variable_any;
using std::mutex;
using std::string;

using tdme::os::threading::Mutex;

/**
* Threading condition variable implementation
* @author Andreas Drewke
*/
class tdme::os::threading::Condition {
public:
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
		condition.notify_one();
	}

	/**
	 * @brief wake ups all waiting threads on this condition, associated mutex should protect broadcast
	 */
	inline void broadcast() {
		condition.notify_all();
	}

	/**
	 * @brief Blocks current thread until signaled/broadcasted, associated mutex should protect wait
	 */
	inline void wait(Mutex &mutex) {
		condition.wait(mutex.mutex);
	}

private:
	string name;
	condition_variable_any condition;
};

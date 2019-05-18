#pragma once

#include "fwd-tdme.h"

#if defined(CPPTHREADS)
	#include <condition_variable>
	#include <mutex>
	using std::condition_variable_any;
	using std::mutex;
#else
	#include <pthread.h>
#endif

#include <string>

#include "fwd-tdme.h"
#include "Mutex.h"

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
	Condition(const string& name);

	/**
	 * @brief Destructor, removes condition variable
	 */
	~Condition();

	/**
	 * @brief wake ups a waiting thread on this condition, associated mutex should protect signal
	 */
	void signal();

	/**
	 * @brief wake ups all waiting threads on this condition, associated mutex should protect broadcast
	 */
	void broadcast();

	/**
	 * @brief Blocks current thread until signaled/broadcasted, associated mutex should protect wait
	 */
	void wait(Mutex &mutex);

private:
	string name;
	#if defined(CPPTHREADS)
		condition_variable_any condition;
	#else
		pthread_cond_t pThreadCond;
	#endif
};

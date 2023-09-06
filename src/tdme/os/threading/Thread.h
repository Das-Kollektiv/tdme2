#pragma once

#include <tdme/os/threading/fwd-tdme.h>

#include <tdme/tdme.h>

#include <chrono>
#include <memory>
#include <thread>
#include <string>

using std::string;
using std::thread;
using std::unique_ptr;

/**
 * Base class for threads.
 * @author Andreas Drewke
 */
class tdme::os::threading::Thread {
public:
	// forbid class copy
	FORBID_CLASS_COPY(Thread)

	/**
	 * @brief Public constructor
	 * @param name name
	 */
	inline Thread(const string& name): name(name), stopRequested(false) {}

	/**
	 * @brief Public destructor
	 */
	inline virtual ~Thread() {}

	/**
	 * @return hardware thread count
	 */
	inline static int getHardwareThreadCount() {
		return std::thread::hardware_concurrency();
	}

	/**
	 * @brief sleeps current thread for given time in milliseconds
	 * @param milliseconds milliseconds to wait
	 */
	inline static void sleep(const uint64_t milliseconds) {
		std::this_thread::sleep_for(std::chrono::duration<uint64_t, std::milli>(milliseconds));
	}

	/**
	 * @brief Blocks caller thread until this thread has been terminated
	 */
	inline void join() {
		stlThread->join();
	}

	/**
	 * @brief Starts this objects thread
	 */
	inline virtual void start() {
		stlThread = make_unique<thread>(thread(threadRun, (void*)this));
	}

	/**
	 * @brief Requests that this thread should be stopped
	 */
	inline virtual void stop() {
		stopRequested = true;
	}

	/**
	 * @brief Returns if stop has been requested
	 * @return bool
	 */
	inline bool isStopRequested() {
		return stopRequested;
	}

protected:
	/**
	 * @brief Abstract run() method, should be implemented by subclassed class, will be called after spawn by start()
	 */
	virtual void run() = 0;

private:
	inline static void threadRun(void *thread) {
		static_cast<Thread*>(thread)->run();
	}

	string name;
	unique_ptr<thread> stlThread;
	volatile bool stopRequested;
};

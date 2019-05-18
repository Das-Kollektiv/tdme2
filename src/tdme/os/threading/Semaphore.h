#pragma once

#if defined(CPPTHREADS)
	#include "Condition.h"
	#include "Mutex.h"
	using tdme::os::threading::Condition;
	using tdme::os::threading::Mutex;
#else
	#include <semaphore.h>
#endif

#include "fwd-tdme.h"
#include <string>

using std::string;

/**
 * Semaphore implementation.
 * @author Andreas Drewke
 */
class tdme::os::threading::Semaphore {
public:
	/**
	 * @brief Public constructor
	 * @param name name
	 * @param value initial value
	 */
	Semaphore(const string& name, int value);

	/**
	 * @brief Destroys the semaphore
	 */
	~Semaphore();

	/**
	 * @brief Waits on this semaphore
	 * @param count count of wait calls
	 */
	void wait(int count = 1);

	/**
	 * @brief Increments on this semaphore
	 * @param count count to increment semaphore to
	 */
	void increment(int count = 1);

	/**
	 * @brief Returns current value of semaphore
	 * @return current value of semaphore
	 */
	int getValue();

private:
	string name;
	#if defined(CPPTHREADS)
		Condition c;
		Mutex m;
		volatile int value;
	#else
		sem_t semaphore;
	#endif

};

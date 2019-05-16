#pragma once

#include "fwd-tdme.h"

#include <semaphore.h>

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
	 * @param value
	 */
	Semaphore(const string& name, int value);

	/**
	 * @brief Destroys the mutex
	 */
	~Semaphore();

	/**
	 * @brief Waits on this semaphore
	 */
	bool wait();

	/**
	 * @brief Increments on this semaphore
	 */
	void increment();

	/**
	 * @brief Unlocks this mutex
	 */
	int getValue();

private:
	string name;
	sem_t semaphore;

};

#pragma once

#include <tdme/tdme.h>
#include <tdme/os/threading/AtomicOperations.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::os::threading::AtomicOperations;

/**
 * Reference counter implementation to be used with inheritance
 * @author Andreas Drewke
 */
class tdme::utilities::Reference {
public:
	// forbid class copy
	FORBID_CLASS_COPY(Reference)

	/**
	 * @brief Public constructor
	 */
	inline Reference(): referenceCounter(0) {}

	/**
	 * @brief destructor
	 */
	inline virtual ~Reference() {}

	/**
	 * @brief acquires a reference, incrementing the counter
	 */
	inline void acquireReference() {
		AtomicOperations::increment(referenceCounter);
	}

	/**
	 * @brief releases a reference, thus decrementing the counter and delete it if reference counter is zero
	 */
	inline void releaseReference() {
		if (AtomicOperations::decrement(referenceCounter) <= 0) {
			onDelete();
			delete this;
		}
	}

	/**
	 * Callback method to be overridden, will be called if object will be deleted
	 */
	virtual void onDelete() {}

private:
	unsigned int referenceCounter;
};

#pragma once

#include <yannet/yannet.h>
#include <yannet/os/threading/AtomicOperations.h>
#include <yannet/utilities/fwd-yannet.h>

// name spaces
namespace yannet {
namespace utilities {
	using yannet::os::threading::AtomicOperations;
}
}

/**
 * Reference counter implementation to be used with inheritance
 * @author Andreas Drewke
 */
class yannet::utilities::Reference {

public:
	// forbid class copy
	FORBID_CLASS_COPY(Reference)

	/**
	 * @brief Public constructor
	 */
	inline Reference(): referenceCounter(0) {}

	/**
	 * @brief Destructor
	 */
	inline virtual ~Reference() {}

	/**
	 * @brief Acquires a reference, incrementing the counter
	 */
	virtual inline void acquireReference() {
		AtomicOperations::increment(referenceCounter);
	}

	/**
	 * @brief Releases a reference, thus decrementing the counter and delete it if reference counter is zero
	 */
	virtual inline void releaseReference() {
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

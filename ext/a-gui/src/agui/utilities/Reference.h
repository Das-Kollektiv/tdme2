#pragma once

#include <agui/agui.h>
#include <agui/os/threading/AtomicOperations.h>
#include <agui/utilities/fwd-agui.h>

// namespaces
namespace agui {
namespace utilities {
	using ::agui::os::threading::AtomicOperations;
}
}

/**
 * Reference counter implementation to be used with inheritance
 * @author Andreas Drewke
 */
class agui::utilities::Reference {
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

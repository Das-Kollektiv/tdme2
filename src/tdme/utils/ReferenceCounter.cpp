#include <tdme/utils/ReferenceCounter.h>

using tdme::utils::ReferenceCounter;

ReferenceCounter::ReferenceCounter() : referenceCounter(0) {
}

ReferenceCounter::~ReferenceCounter() {
}

void ReferenceCounter::acquireReference() {
	// atomic add
	__sync_add_and_fetch(&referenceCounter, 1);
}

void ReferenceCounter::releaseReference() {
	// atomic dec and check if zero
	if (__sync_sub_and_fetch(&referenceCounter, 1) == 0) {
		// yep, no more references, delete object
		delete this;
	}
}

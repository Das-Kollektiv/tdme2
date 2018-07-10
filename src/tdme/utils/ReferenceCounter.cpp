#include <tdme/utils/ReferenceCounter.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#include <windows.h>
#endif

using tdme::utils::ReferenceCounter;

ReferenceCounter::ReferenceCounter() : referenceCounter(0) {
}

ReferenceCounter::~ReferenceCounter() {
}

void ReferenceCounter::acquireReference() {
	// atomic add
	#if defined(_WIN32) && defined(_MSC_VER)
		InterlockedIncrement(&referenceCounter);
	#else
		__sync_add_and_fetch(&referenceCounter, 1);
	#endif
}

void ReferenceCounter::releaseReference() {
	// atomic dec and check if zero and delete
	#if defined(_WIN32) && defined(_MSC_VER)
		if (InterlockedDecrement(&referenceCounter) == 0) {
			delete this;
		}
	#else
		if (__sync_sub_and_fetch(&referenceCounter, 1) == 0) {
			delete this;
		}
	#endif
}

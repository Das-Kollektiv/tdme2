#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::vector;

namespace tdme {
namespace utilities {

/**
 * Pool template class
 * @author Andreas Drewke
 * @param<E>
 */
template<typename T>
class Pool
{
private:
	vector<T*> freeElements;
	vector<T*> usedElements;

protected:
	/**
	 * Instantiate element
	 * @returns instantiates a new element
	 */
	virtual T* instantiate() = 0;

public:
	// forbid class copy
	FORBID_CLASS_COPY(Pool)

	/**
	 * Public constructor
	 */
	Pool() {
	}

	virtual ~Pool() {
		for (auto element: usedElements) {
			delete element;
		}
		for (auto element: freeElements) {
			delete element;
		}
	}

	/**
	 * Allocate a new element from pool
	 * @returns element
	 */
	T* allocate() {
		if (freeElements.empty() == false) {
			auto element = freeElements[freeElements.size() - 1];
			freeElements.erase(freeElements.begin() + freeElements.size() - 1);
			usedElements.push_back(element);
			return element;
		}
		auto element = instantiate();
		usedElements.push_back(element);
		return element;
	}

	/**
	 * Release element in pool for being reused
	 * @param element element
	 */
	void release(T* element) {
		for (auto i = 0; i < usedElements.size(); i++) {
			if (usedElements[i] == element) {
				usedElements.erase(usedElements.begin() + i);
				freeElements.push_back(element);
				return;
			}
		}
	}

	/**
	 * @returns element capacity
	 */
	int32_t capacity() {
		return usedElements.size() + freeElements.size();
	}

	/**
	 * @returns elements in use
	 */
	int32_t size() {
		return usedElements.size();
	}

	/**
	 * Reset this pool
	 */
	void reset() {
		for (auto i = 0; i < usedElements.size(); i++) {
			freeElements.push_back(usedElements[i]);
		}
		usedElements.clear();
	}

};

};
};

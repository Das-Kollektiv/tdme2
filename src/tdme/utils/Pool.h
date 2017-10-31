
#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;

/** 
 * Pool 
 * @author Andreas Drewke
 * @version $Id$
 * @param<E>
 */
namespace tdme {
namespace utils {

/**
 * Array list iterator for multiple array lists
 * @author Andreas Drewke
 * @version $Id$
 */
template<typename T>
class Pool
{
private:
	vector<T> freeElements;
	vector<T> usedElements;
public:

	/** 
	 * Allocate a new element from pool
	 * @return element
	 */
	T allocate() {
		if (freeElements.empty() == false) {
			T element = freeElements.at(freeElements.size() - 1);
			freeElements.erase(freeElements.begin() + freeElements.size() - 1);
			usedElements.push_back(element);
			return element;
		}
		T element = instantiate();
		usedElements.push_back(element);
		return element;
	}

public: /* protected */

	/** 
	 * Instantiate element
	 */
	virtual T instantiate() = 0;

public:

	/** 
	 * Release element in pool for being reused
	 * @param element
	 */
	void release(T element) {
		for (auto i = 0; i < usedElements.size(); i++) {
			if (usedElements.at(i) == element) {
				usedElements.erase(usedElements.begin() + i);
				freeElements.push_back(element);
				return;
			}
		}
	}

	/** 
	 * @return element capacity
	 */
	int32_t capacity() {
		return usedElements.size() + freeElements.size();
	}

	/** 
	 * @return elements in use
	 */
	int32_t size() {
		return usedElements.size();
	}

	/** 
	 * Reset this pool
	 */
	void reset() {
		for (auto i = 0; i < usedElements.size(); i++) {
			freeElements.push_back(usedElements.at(i));
		}
		usedElements.clear();
	}

	/**
	 * Public constructor
	 */
	Pool() {
	}

	~Pool() {
		for (auto element: usedElements) {
			delete element;
		}
		for (auto element: freeElements) {
			delete element;
		}
	}

};

};
};

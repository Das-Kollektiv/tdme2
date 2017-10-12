
#pragma once

#include <vector>
#include <algorithm>

#include <tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;
using std::find;

namespace tdme {
namespace utils {

/** 
 * Array list iterator for multiple array lists
 * @author Andreas Drewke
 * @version $Id$
 */
template<typename T>
class ArrayListIteratorMultiple final
{
private:
	int32_t vectorIdx {  0 };
	int32_t elementIdx {  0 };
	int32_t length { 0  };
	vector<vector<T>*> arrayLists {  };

public:

	/** 
	 * Clears list of array lists to iterate
	 */
	void clear() {
		arrayLists.clear();
	}

	/** 
	 * Adds array lists to iterate
	 * @param array list
	 */
	void addArrayList(vector<T>* _arrayList) {
		if (find(arrayLists.begin(), arrayLists.end(), _arrayList) != arrayLists.end()) return;
		arrayLists.push_back(_arrayList);
	}

	/** 
	 * resets vector iterator for iterating
	 * @return this vector iterator
	 */
	ArrayListIteratorMultiple<T>* reset() {
		this->vectorIdx = 0;
		this->elementIdx = 0;
		this->length = 0;
		for (auto i = 0; i < arrayLists.size(); i++) {
			this->length += arrayLists.at(i)->size();
		}
		return this;
	}

	bool hasNext() {
		auto hasNext = arrayLists.size() > 0 && (vectorIdx < arrayLists.size() - 1) || (vectorIdx == arrayLists.size() - 1 && elementIdx < arrayLists.at(vectorIdx)->size());
		return hasNext;
	}

	T next() {
		auto element = arrayLists.at(vectorIdx)->at(elementIdx++);
		if (elementIdx == arrayLists.at(vectorIdx)->size()) {
			elementIdx = 0;
			vectorIdx++;
		}
		return element;
	}

	void remove() {

	}

	ArrayListIteratorMultiple* iterator() {
		reset();
		return this;
	}

	/** 
	 * Clones this iterator
	 */
	ArrayListIteratorMultiple<T>* clone() {
		return new ArrayListIteratorMultiple<T>(arrayLists);
	}

	// Generated
	ArrayListIteratorMultiple() {
		reset();
	}

	/**
	 * Adds array lists to iterate
	 * @param array list
	 */
	ArrayListIteratorMultiple(vector<vector<T>*>& arrayLists) {
		this->arrayLists = arrayLists;
		reset();
	}

};

};
};

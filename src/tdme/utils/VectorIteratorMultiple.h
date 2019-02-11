#pragma once

#include <vector>
#include <algorithm>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::vector;
using std::find;

namespace tdme {
namespace utils {

/** 
 * Vector iterator template to be used to iterate multiple vectors at a single invocation
 * @author Andreas Drewke
 * @version $Id$
 */
template<typename T>
class VectorIteratorMultiple final
{
private:
	int32_t vectorIdx {  0 };
	int32_t elementIdx {  0 };
	vector<vector<T>*> vectorList {  };

public:

	/** 
	 * Clears list of array lists to iterate
	 */
	void clear() {
		vectorList.clear();
	}

	/** 
	 * Adds vector to iterator
	 * @param vector vector
	 */
	void addVector(vector<T>* vector) {
		if (find(vectorList.begin(), vectorList.end(), vector) != vectorList.end()) return;
		vectorList.push_back(vector);
	}

	/** 
	 * Resets vector iterator for iterating
	 * @return this vector iterator
	 */
	VectorIteratorMultiple<T>* reset() {
		this->vectorIdx = 0;
		this->elementIdx = 0;
		return this;
	}

	/**
	 * Determines if next element is available
	 * @return bool if next element available
	 */
	bool hasNext() {
		if (vectorList.size() == 0) return false;
		while (true == true) {
			if (vectorList[vectorIdx]->size() == 0 || elementIdx == vectorList[vectorIdx]->size()) {
				vectorIdx++;
				elementIdx = 0;
				if (vectorIdx == vectorList.size()) return false;
			} else {
				return true;
			}
		}
	}

	/**
	 * Retrieves next element, hasNext must have been called before
	 */
	T next() {
		return (*vectorList[vectorIdx])[elementIdx++];
	}

	/**
	 * @return iterator
	 */
	VectorIteratorMultiple* iterator() {
		reset();
		return this;
	}

	/** 
	 * Clones this iterator
	 */
	VectorIteratorMultiple<T>* clone() {
		return new VectorIteratorMultiple<T>(vectorList);
	}

	/**
	 * Publoic constructor
	 */
	VectorIteratorMultiple() {
		reset();
	}

	/**
	 * Public constructor
	 * @param vectorList vector list
	 */
	VectorIteratorMultiple(vector<vector<T>*>& vectorList) {
		this->vectorList = vectorList;
		reset();
	}

};

};
};

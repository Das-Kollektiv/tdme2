#pragma once

#include <algorithm>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::find;
using std::vector;

namespace tdme {
namespace utilities {

/**
 * Object deleter
 * @author Andreas Drewke
 */
template<typename T>
class ObjectDeleter final
{
private:
	vector<T*> objects;

public:
	// forbid class copy
	CLASS_FORBID_COPY(ObjectDeleter)

	/**
	 * Public constructor
	 */
	ObjectDeleter() {
	}

	/**
	 * Public destructor
	 */
	~ObjectDeleter() {
		for (auto object: objects) delete object;
		objects.clear();
	}

	/**
	 * Adds object
	 * @param object object
	 */
	T* add(T* object) {
		if (find(objects.begin(), objects.end(), object) != objects.end()) return object;
		objects.push_back(object);
		return object;
	}

};

};
};

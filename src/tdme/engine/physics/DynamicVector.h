// Generated from /tdme/src/tdme/engine/physics/DynamicVector.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>

using std::vector;

/** 
 * Dynamic Vector
 * @author Andreas Drewke
 * @versioN $Id$
 */
class tdme::engine::physics::DynamicVector final
{
public: /* protected */
	vector<float> data {  };

public: /* protected */

	/** 
	 * Change size
	 * @param size
	 */
	inline void setSize(int32_t size) {
		data.resize(size);
	}

	/** 
	 * Set value
	 * @param idx
	 * @param value
	 */
	inline void setValue(int32_t idx, float value) {
		data[idx] = value;
	}

	/** 
	 * Retrieves value
	 * @param idx
	 * @return value
	 */
	inline float getValue(int32_t idx) {
		return data[idx];
	}

	/** 
	 * Scales this vector with given value into dest vector
	 * @param value
	 * @param dest
	 */
	inline void scale(float value, DynamicVector* dest) {
		if (data.size() != dest->data.size()) {
			dest->setSize(data.size());
		}
		for (auto i = 0; i < data.size(); i++) {
			dest->data[i] = data[i] * value;
		}
	}

	/**
	 * Constructor
	 */
	inline DynamicVector() {
	}

	/**
	 * Constructor
	 * @param size
	 */
	inline DynamicVector(int32_t size) {
		data.resize(size);
	}
};

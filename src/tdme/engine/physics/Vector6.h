// Generated from /tdme/src/tdme/engine/physics/Vector6.java

#pragma once

#include <algorithm>
#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/Vector6.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using std::array;
using std::begin;
using std::copy;
using std::end;

using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

/** 
 * Vector6
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::Vector6 final
{
public: /* protected */
	array<float, 6> data {  };

public: /* protected */

	/** 
	 * Fills the Vector with given value
	 * @param value
	 */
	inline void fill(float value) {
		data.fill(value);
	}

	/** 
	 * Set up vector from vector
	 * @param vector 6
	 * @return this vector
	 */
	inline Vector6* set(Vector6* vector6) {
		copy(begin(*vector6->getArray()), end(*vector6->getArray()), begin(data));
		return this;
	}

	/** 
	 * Set up matrix value at given idx
	 * @param idx
	 * @param value
	 */
	inline void setValue(int32_t idx, float value) {
		data[idx] = value;
	}

	/** 
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	inline void setValue(int32_t startIdx, Vector3* vector3) {
		auto vector3XYZ = vector3->getArray();
		data[startIdx + 0] = (*vector3XYZ)[0];
		data[startIdx + 1] = (*vector3XYZ)[1];
		data[startIdx + 2] = (*vector3XYZ)[2];
	}

	/** 
	 * Adds this vector to given vector6 into dest vector6
	 * @param vector 6
	 * @param this vector 6
	 */
	inline Vector6* add(Vector6* vector6) {
		data[0] += vector6->data[0];
		data[1] += vector6->data[1];
		data[2] += vector6->data[2];
		data[3] += vector6->data[3];
		data[4] += vector6->data[4];
		data[5] += vector6->data[5];
		return this;
	}

	/** 
	 * Subtracts given vector 6 from this vector 6
	 * @param vector 6
	 * @param this vector 6
	 */
	inline Vector6* sub(Vector6* vector6) {
		data[0] -= vector6->data[0];
		data[1] -= vector6->data[1];
		data[2] -= vector6->data[2];
		data[3] -= vector6->data[3];
		data[4] -= vector6->data[4];
		data[5] -= vector6->data[5];
		return this;
	}

	/** 
	 * Scales this vector6 with given float value
	 * @param value
	 * @return this vector 6 
	 */
	inline Vector6* scale(float value) {
		data[0] *= value;
		data[1] *= value;
		data[2] *= value;
		data[3] *= value;
		data[4] *= value;
		data[5] *= value;
		return this;
	}

	/** 
	 * @return data array
	 */
	inline array<float, 6>* getArray() {
		return &data;
	}

	/**
	 * Public constructor
	 */
	inline Vector6() {
		data.fill(0.0f);
	}

};

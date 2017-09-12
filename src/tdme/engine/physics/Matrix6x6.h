// Generated from /tdme/src/tdme/engine/physics/Matrix6x6.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/Vector6.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using std::array;

using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

/** 
 * Matrix 6x6
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::Matrix6x6 final
{
public: /* protected */
	array<float, 36> data {  };

public: /* protected */

	/** 
	 * Fills the Vector with given value
	 * @param value
	 */
	inline void fill(float value) {
		data.fill(value);
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
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	inline void setValue(int32_t i, int32_t j, float value) {
		data[i * 6 + j] = value;
	}

	/** 
	 * @return data array
	 */
	inline array<float, 36>* getArray() {
		return &data;
	}

	/** 
	 * Multiplies this matrix 6x6 with given vector 6
	 * @param vector 6
	 * @param destination vector
	 * @return destination vector
	 */
	inline Vector6* multiply(Vector6* vector6, Vector6* dest) {
		auto vector6Array = vector6->getArray();
		dest->data[0] = data[0 * 6 + 0] * (*vector6Array)[0] + data[0 * 6 + 1] * (*vector6Array)[1] + data[0 * 6 + 2] * (*vector6Array)[2] + data[0 * 6 + 3] * (*vector6Array)[3] + data[0 * 6 + 4] * (*vector6Array)[4] + data[0 * 6 + 5] * (*vector6Array)[5];
		dest->data[1] = data[1 * 6 + 0] * (*vector6Array)[0] + data[1 * 6 + 1] * (*vector6Array)[1] + data[1 * 6 + 2] * (*vector6Array)[2] + data[1 * 6 + 3] * (*vector6Array)[3] + data[1 * 6 + 4] * (*vector6Array)[4] + data[1 * 6 + 5] * (*vector6Array)[5];
		dest->data[2] = data[2 * 6 + 0] * (*vector6Array)[0] + data[2 * 6 + 1] * (*vector6Array)[1] + data[2 * 6 + 2] * (*vector6Array)[2] + data[2 * 6 + 3] * (*vector6Array)[3] + data[2 * 6 + 4] * (*vector6Array)[4] + data[2 * 6 + 5] * (*vector6Array)[5];
		dest->data[3] = data[3 * 6 + 0] * (*vector6Array)[0] + data[3 * 6 + 1] * (*vector6Array)[1] + data[3 * 6 + 2] * (*vector6Array)[2] + data[3 * 6 + 3] * (*vector6Array)[3] + data[3 * 6 + 4] * (*vector6Array)[4] + data[3 * 6 + 5] * (*vector6Array)[5];
		dest->data[4] = data[4 * 6 + 0] * (*vector6Array)[0] + data[4 * 6 + 1] * (*vector6Array)[1] + data[4 * 6 + 2] * (*vector6Array)[2] + data[4 * 6 + 3] * (*vector6Array)[3] + data[4 * 6 + 4] * (*vector6Array)[4] + data[4 * 6 + 5] * (*vector6Array)[5];
		dest->data[5] = data[5 * 6 + 0] * (*vector6Array)[0] + data[5 * 6 + 1] * (*vector6Array)[1] + data[5 * 6 + 2] * (*vector6Array)[2] + data[5 * 6 + 3] * (*vector6Array)[3] + data[5 * 6 + 4] * (*vector6Array)[4] + data[5 * 6 + 5] * (*vector6Array)[5];
		return dest;
	}

public: /* protected */
	/**
	 * Public constructor
	 */
	inline Matrix6x6() {
		data.fill(0.0f);
	}
};

/*********************************************************************************
 * This source code is based on                                                  *
 * ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
 * Copyright (c) 2010-2015 Daniel Chappuis                                       *
 *********************************************************************************
 *                                                                               *
 * This software is provided 'as-is', without any express or implied warranty.   *
 * In no event will the authors be held liable for any damages arising from the  *
 * use of this software.                                                         *
 *                                                                               *
 * Permission is granted to anyone to use this software for any purpose,         *
 * including commercial applications, and to alter it and redistribute it        *
 * freely, subject to the following restrictions:                                *
 *                                                                               *
 * 1. The origin of this software must not be misrepresented; you must not claim *
 *    that you wrote the original software. If you use this software in a        *
 *    product, an acknowledgment in the product documentation would be           *
 *    appreciated but is not required.                                           *
 *                                                                               *
 * 2. Altered source versions must be plainly marked as such, and must not be    *
 *    misrepresented as being the original software.                             *
 *                                                                               *
 * 3. This notice may not be removed or altered from any source distribution.    *
 *                                                                               *
 ********************************************************************************/

#pragma once

#include <array>

#include <algorithm>
#include <array>

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/Matrix6x6.h>
#include <tdme/engine/physics/Vector6.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using std::array;
using std::begin;
using std::copy;
using std::end;

using tdme::engine::physics::Matrix1x6;
using tdme::engine::physics::Matrix6x6;
using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

/** 
 * Matrix 1x6
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::Matrix1x6 final {
private:
	array<float, 6> data {  };

public:

	/** 
	 * Set up matrix values
	 * @param value0
	 * @param value1
	 * @param value2
	 * @param value3
	 * @param value4
	 * @param value5
	 */
	inline Matrix1x6& setValue(float value0, float value1, float value2, float value3, float value4, float value5) {
		data[0] = value0;
		data[1] = value1;
		data[2] = value2;
		data[3] = value3;
		data[4] = value4;
		data[5] = value5;
		return *this;
	}

	/** 
	 * Set up matrix value at given idx
	 * @param idx
	 * @param value
	 */
	inline Matrix1x6& setValue(int32_t idx, float value) {
		data[idx] = value;
		return *this;
	}

	/** 
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	inline Matrix1x6& setValue(int32_t startIdx, const Vector3& vector3) {
		auto& vector3XYZ = vector3.getArray();
		data[startIdx + 0] = vector3XYZ[0];
		data[startIdx + 1] = vector3XYZ[1];
		data[startIdx + 2] = vector3XYZ[2];
		return *this;
	}

	/** 
	 * Multiplies this matrix 1x6 with given vector 6
	 * @param vector
	 * @return scalar product
	 */
	inline float multiply(const Vector6& vector) const {
		auto& vector6Array = vector.getArray();
		return data[0] * vector6Array[0] + data[1] * vector6Array[1] + data[2] * vector6Array[2] + data[3] * vector6Array[3] + data[4] * vector6Array[4] + data[5] * vector6Array[5];
	}

	/** 
	 * Multiplies this 1x6 matrix with given matrix 6x6 into destination matrix
	 * @param matrix6x6 6x6
	 * @param destination
	 * @return destination matrix 1x6
	 */
	inline Matrix1x6& multiply(const Matrix6x6& matrix6x6, Matrix1x6& dest) const {
		auto& matrix6x6Data = matrix6x6.getArray();
		dest.data[0] = data[0] * matrix6x6Data[0 * 6 + 0] + data[1] * matrix6x6Data[1 * 6 + 0] + data[2] * matrix6x6Data[2 * 6 + 0] + data[3] * matrix6x6Data[3 * 6 + 0] + data[4] * matrix6x6Data[4 * 6 + 0] + data[5] * matrix6x6Data[5 * 6 + 0];
		dest.data[1] = data[0] * matrix6x6Data[0 * 6 + 1] + data[1] * matrix6x6Data[1 * 6 + 1] + data[2] * matrix6x6Data[2 * 6 + 1] + data[3] * matrix6x6Data[3 * 6 + 1] + data[4] * matrix6x6Data[4 * 6 + 1] + data[5] * matrix6x6Data[5 * 6 + 1];
		dest.data[2] = data[0] * matrix6x6Data[0 * 6 + 2] + data[1] * matrix6x6Data[1 * 6 + 2] + data[2] * matrix6x6Data[2 * 6 + 2] + data[3] * matrix6x6Data[3 * 6 + 2] + data[4] * matrix6x6Data[4 * 6 + 2] + data[5] * matrix6x6Data[5 * 6 + 2];
		dest.data[3] = data[0] * matrix6x6Data[0 * 6 + 3] + data[1] * matrix6x6Data[1 * 6 + 3] + data[2] * matrix6x6Data[2 * 6 + 3] + data[3] * matrix6x6Data[3 * 6 + 3] + data[4] * matrix6x6Data[4 * 6 + 3] + data[5] * matrix6x6Data[5 * 6 + 3];
		dest.data[4] = data[0] * matrix6x6Data[0 * 6 + 4] + data[1] * matrix6x6Data[1 * 6 + 4] + data[2] * matrix6x6Data[2 * 6 + 4] + data[3] * matrix6x6Data[3 * 6 + 4] + data[4] * matrix6x6Data[4 * 6 + 4] + data[5] * matrix6x6Data[5 * 6 + 4];
		dest.data[5] = data[0] * matrix6x6Data[0 * 6 + 5] + data[1] * matrix6x6Data[1 * 6 + 5] + data[2] * matrix6x6Data[2 * 6 + 5] + data[3] * matrix6x6Data[3 * 6 + 5] + data[4] * matrix6x6Data[4 * 6 + 5] + data[5] * matrix6x6Data[5 * 6 + 5];
		return dest;
	}

	/** 
	 * Get transpose
	 * @param destination vector 6
	 * @return destination vector 6
	 */
	inline Vector6& getTranspose(Vector6& dest) const {
		copy(begin(data), end(data), begin(dest.data));
		return dest;
	}

	/**
	 * Public constructor
	 */
	inline Matrix1x6() {
		data.fill(0.0f);
	}
};

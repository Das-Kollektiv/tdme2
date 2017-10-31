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

#include <tdme/tdme.h>
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
	inline Matrix6x6& fill(float value) {
		data.fill(value);
		return *this;
	}

	/** 
	 * Set up matrix value at given idx
	 * @param idx
	 * @param value
	 */
	inline Matrix6x6& setValue(int32_t idx, float value) {
		data[idx] = value;
		return *this;
	}

	/** 
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	inline Matrix6x6& setValue(int32_t startIdx, const Vector3& vector3) {
		auto& vector3XYZ = vector3.getArray();
		data[startIdx + 0] = vector3XYZ[0];
		data[startIdx + 1] = vector3XYZ[1];
		data[startIdx + 2] = vector3XYZ[2];
		return *this;
	}

	/** 
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	inline Matrix6x6& setValue(int32_t i, int32_t j, float value) {
		data[i * 6 + j] = value;
		return *this;
	}

	/** 
	 * @return data array
	 */
	inline array<float, 36>& getArray() const {
		return (array<float, 36>&)data;
	}

	/** 
	 * Multiplies this matrix 6x6 with given vector 6
	 * @param vector 6
	 * @param destination vector
	 * @return destination vector
	 */
	inline Vector6& multiply(const Vector6& vector6, Vector6& dest) const {
		auto& vector6Array = vector6.getArray();
		dest.data[0] = data[0 * 6 + 0] * vector6Array[0] + data[0 * 6 + 1] * vector6Array[1] + data[0 * 6 + 2] * vector6Array[2] + data[0 * 6 + 3] * vector6Array[3] + data[0 * 6 + 4] * vector6Array[4] + data[0 * 6 + 5] * vector6Array[5];
		dest.data[1] = data[1 * 6 + 0] * vector6Array[0] + data[1 * 6 + 1] * vector6Array[1] + data[1 * 6 + 2] * vector6Array[2] + data[1 * 6 + 3] * vector6Array[3] + data[1 * 6 + 4] * vector6Array[4] + data[1 * 6 + 5] * vector6Array[5];
		dest.data[2] = data[2 * 6 + 0] * vector6Array[0] + data[2 * 6 + 1] * vector6Array[1] + data[2 * 6 + 2] * vector6Array[2] + data[2 * 6 + 3] * vector6Array[3] + data[2 * 6 + 4] * vector6Array[4] + data[2 * 6 + 5] * vector6Array[5];
		dest.data[3] = data[3 * 6 + 0] * vector6Array[0] + data[3 * 6 + 1] * vector6Array[1] + data[3 * 6 + 2] * vector6Array[2] + data[3 * 6 + 3] * vector6Array[3] + data[3 * 6 + 4] * vector6Array[4] + data[3 * 6 + 5] * vector6Array[5];
		dest.data[4] = data[4 * 6 + 0] * vector6Array[0] + data[4 * 6 + 1] * vector6Array[1] + data[4 * 6 + 2] * vector6Array[2] + data[4 * 6 + 3] * vector6Array[3] + data[4 * 6 + 4] * vector6Array[4] + data[4 * 6 + 5] * vector6Array[5];
		dest.data[5] = data[5 * 6 + 0] * vector6Array[0] + data[5 * 6 + 1] * vector6Array[1] + data[5 * 6 + 2] * vector6Array[2] + data[5 * 6 + 3] * vector6Array[3] + data[5 * 6 + 4] * vector6Array[4] + data[5 * 6 + 5] * vector6Array[5];
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

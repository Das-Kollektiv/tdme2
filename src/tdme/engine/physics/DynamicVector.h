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

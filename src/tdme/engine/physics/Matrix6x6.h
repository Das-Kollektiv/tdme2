// Generated from /tdme/src/tdme/engine/physics/Matrix6x6.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

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
	void fill(float value);

	/** 
	 * Set up matrix value at given idx
	 * @param idx
	 * @param value
	 */
	void setValue(int32_t idx, float value);

	/** 
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	void setValue(int32_t startIdx, Vector3* vector3);

	/** 
	 * Set up vector as value
	 * @param this matrix start idx
	 * @param vector 3
	 */
	void setValue(int32_t i, int32_t j, float value);

	/** 
	 * @return data array
	 */
	array<float, 36>* getArray();

	/** 
	 * Multiplies this matrix 6x6 with given vector 6
	 * @param vector 6
	 * @param destination vector
	 * @return destination vector
	 */
	Vector6* multiply(Vector6* vector6, Vector6* dest);

public: /* protected */
	/**
	 * Public constructor
	 */
	Matrix6x6();
};

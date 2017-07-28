// Generated from /tdme/src/tdme/engine/physics/Matrix1x6.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using std::array;

using tdme::engine::physics::Matrix6x6;
using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

/** 
 * Matrix 1x6
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::Matrix1x6 final {
public: /* protected */
	array<float, 6> data {  };

public: /* protected */

	/** 
	 * Set up matrix values
	 * @param value0
	 * @param value1
	 * @param value2
	 * @param value3
	 * @param value4
	 * @param value5
	 */
	void setValue(float value0, float value1, float value2, float value3, float value4, float value5);

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
	 * Multiplies this matrix 1x6 with given vector 6
	 * @param vector
	 * @return scalar product
	 */
	float multiply(Vector6* vector);

	/** 
	 * Multiplies this 1x6 matrix with given matrix 6x6 into destination matrix
	 * @param matrix6x6 6x6
	 * @param destination
	 * @return destination matrix 1x6
	 */
	Matrix1x6* multiply(Matrix6x6* matrix6x6, Matrix1x6* dest);

	/** 
	 * Get transpose
	 * @param destination vector 6
	 * @return destination vector 6
	 */
	Vector6* getTranspose(Vector6* dest);
public:

	/**
	 * Public constructor
	 */
	Matrix1x6();
};

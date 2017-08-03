// Generated from /tdme/src/tdme/engine/Rotation.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Quaternion.h>

using tdme::math::Quaternion;
using tdme::math::Vector3;

/** 
 * Rotation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Rotation final
{

public:
	static Vector3 X_AXIS;
	static Vector3 Y_AXIS;
	static Vector3 Z_AXIS;

private:
	float angle {  };
	Vector3 axis {  };
	Quaternion quaternion {  };

public:

	/** 
	 * @return angle
	 */
	float getAngle();

	/** 
	 * @param angle
	 */
	void setAngle(float angle);

	/** 
	 * @return axis
	 */
	Vector3* getAxix();

	/** 
	 * @return quaternion
	 */
	Quaternion* getQuaternion();

	/** 
	 * Sets up this rotation from another rotation
	 * @param rotation
	 */
	void fromRotation(Rotation* rotation);

	/** 
	 * Sets up this rotation from quaternion, current quaternion will be lost, needs to get updated
	 * @param q
	 */
	void fromQuaternion(Quaternion* q);

	/** 
	 * Computes rotation matrix
	 */
	void update();

	/**
	 * Public constructor
	 */
	Rotation();

	/**
	 * Public constructor
	 * @param angle
	 * @param axis
	 */
	Rotation(float angle, Vector3* axis);
};

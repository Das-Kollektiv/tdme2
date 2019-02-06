#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Quaternion.h>

using tdme::math::Quaternion;
using tdme::math::Vector3;

/** 
 * Rotation representation
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
	inline const float getAngle() const {
		return angle;
	}

	/** 
	 * @param angle angle
	 */
	inline void setAngle(const float angle) {
		this->angle = angle;
	}

	/** 
	 * @return axis
	 */
	inline const Vector3& getAxis() const {
		return axis;
	}

	/**
	 * Set axis
	 * @param axis axis
	 */
	inline void setAxis(const Vector3& axis) {
		this->axis.set(axis);
	}

	/**
	 * @return quaternion
	 */
	const Quaternion& getQuaternion() const {
		return quaternion;
	}

	/** 
	 * Sets up this rotation from another rotation
	 * @param rotation rotation
	 */
	void fromRotation(const Rotation& rotation);

	/** 
	 * Sets up this rotation from quaternion, current quaternion will be lost, needs to get updated
	 * @param q q
	 */
	void fromQuaternion(const Quaternion& q);

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
	 * @param angle angle
	 * @param axis axis
	 */
	Rotation(float angle, const Vector3& axis);
};

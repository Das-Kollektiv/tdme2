#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using tdme::math::Quaternion;
using tdme::math::Vector3;

/**
 * Rotation representation
 * @author Andreas Drewke
 */
class tdme::engine::Rotation final
{

public:
	STATIC_DLL_IMPEXT static Vector3 X_AXIS;
	STATIC_DLL_IMPEXT static Vector3 Y_AXIS;
	STATIC_DLL_IMPEXT static Vector3 Z_AXIS;

private:
	float angle;
	Vector3 axis;
	Quaternion quaternion;

public:
	/**
	 * Public constructor
	 */
	Rotation();

	/**
	 * Public constructor
	 * @param axis axis
	 * @param angle angle
	 */
	Rotation(const Vector3& axis, float angle);

	/**
	 * Interpolate from given rotation to target rotation taking time passed in seconds and rotation degrees per second into account
	 * @param currentAngle current angle
	 * @param targetAngle target angle
	 * @param timePassedSeconds time passed in seconds
	 * @param degreesPerSeconds deegrees per seconds
	 * @param interpolatedAngle interpolated angle
	 * @return rotation is finished
	 */
	static bool interpolate(float currentAngle, float targetAngle, float timePassedSeconds, float degreesPerSeconds, float& interpolatedAngle);

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

};

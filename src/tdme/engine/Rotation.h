#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using tdme::math::Math;
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
	Vector3 axis;
	float angle;
	Quaternion quaternion;

public:
	/**
	 * Public constructor
	 */
	inline Rotation(): axis(Vector3(0.0f, 0.0f, 0.0f)), angle(0.0f) {
		quaternion.identity();
	}

	/**
	 * Public constructor
	 * @param axis axis
	 * @param angle angle
	 */
	inline Rotation(const Vector3& axis, float angle): axis(axis), angle(angle) {
		update();
	}

	/**
	 * Interpolate from given rotation to target rotation taking time passed in seconds and rotation degrees per second into account
	 * @param currentAngle current angle
	 * @param targetAngle target angle
	 * @param timePassedSeconds time passed in seconds
	 * @param degreesPerSeconds deegrees per seconds
	 * @param interpolatedAngle interpolated angle
	 * @returns rotation is finished
	 */
	inline static bool interpolate(float currentAngle, float targetAngle, float timePassedSeconds, float degreesPerSeconds, float& interpolatedAngle) {
		currentAngle = Math::absmod(currentAngle, 360.0f);
		targetAngle = Math::absmod(targetAngle, 360.0f);
		auto targetRotationAngleA = targetAngle;
		auto targetRotationAngleB = targetAngle - 360.0f;
		auto targetRotationAngleC = targetAngle + 360.0f;
		if (Math::abs(targetRotationAngleA - currentAngle) < Math::abs(targetRotationAngleB - currentAngle) &&
			Math::abs(targetRotationAngleA - currentAngle) < Math::abs(targetRotationAngleC - currentAngle)) {
			targetAngle = targetRotationAngleA;
		} else
		if (Math::abs(targetRotationAngleB - currentAngle) < Math::abs(targetRotationAngleA - currentAngle) &&
			Math::abs(targetRotationAngleB - currentAngle) < Math::abs(targetRotationAngleC - currentAngle)) {
			targetAngle = targetRotationAngleB;
		} else
		if (Math::abs(targetRotationAngleC - currentAngle) < Math::abs(targetRotationAngleA - currentAngle) &&
			Math::abs(targetRotationAngleC - currentAngle) < Math::abs(targetRotationAngleB - currentAngle)) {
			targetAngle = targetRotationAngleC;
		}
		if (Math::abs(Math::absmod(currentAngle, 360.0f) - Math::absmod(targetAngle, 360.0f)) < 0.49f) {
			interpolatedAngle = targetAngle;
			return true;
		} else {
			auto rotationAdd = timePassedSeconds * degreesPerSeconds * Math::sign(targetAngle - currentAngle);
			if (currentAngle < targetAngle && currentAngle + rotationAdd > targetAngle) {
				currentAngle = targetAngle;
			} else
			if (currentAngle > targetAngle && currentAngle + rotationAdd < targetAngle) {
				currentAngle = targetAngle;
			} else {
				currentAngle+= rotationAdd;
			}
			interpolatedAngle = currentAngle;
			return false;
		}
	}

	/**
	 * @returns angle
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
	 * @returns axis
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
	 * @returns quaternion
	 */
	inline const Quaternion& getQuaternion() const {
		return quaternion;
	}

	/**
	 * From rotation
	 */
	inline void fromRotation(const Rotation& rotation) {
		this->axis = rotation.axis;
		this->angle = rotation.angle;
		this->quaternion = rotation.quaternion;
	}

	/**
	 * Returns rotation from a quaternion
	 * @param quaternion quaternion
	 * @returns rotation
	 */
	inline static const Rotation fromQuaternion(const Quaternion& quaternion) {
		auto q = quaternion.clone().normalize();
		// compute angle
		auto angle = 2.0f * Math::acos(q[3]) / 3.1415927f * 180.0f;
		// compute axis
		Vector3 axis;
		auto s = Math::sqrt(1.0f - q[3] * q[3]);
		if (s < 0.0010f) {
			axis.set(q[0], q[1], q[2]);
		} else {
			axis.set(q[0] / s, q[1] / s, q[2] / s);
		}
		//
		return Rotation(axis, angle);
	}

	/**
	 * Computes rotation matrix
	 */
	inline void update() {
		quaternion.rotate(axis, angle);
	}

};

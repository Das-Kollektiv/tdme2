#include <tdme/engine/Rotation.h>

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Rotation;
using tdme::math::Math;
using tdme::math::Quaternion;
using tdme::math::Vector3;

Rotation::Rotation()
{
	this->angle = 0.0f;
	this->axis.set(0.0f, 0.0f, 0.0f);
	this->quaternion.identity();
}

Rotation::Rotation(const Vector3& axis, float angle)
{
	this->angle = angle;
	this->axis.set(axis);
	this->quaternion.identity();
}

Vector3 Rotation::X_AXIS(1.0f, 0.0f, 0.0f);

Vector3 Rotation::Y_AXIS(0.0f, 1.0f, 0.0f);

Vector3 Rotation::Z_AXIS(0.0f, 0.0f, 1.0f);

void Rotation::fromRotation(const Rotation& rotation)
{
	angle = rotation.angle;
	axis.set(rotation.axis);
	quaternion.set(rotation.quaternion);
}

void Rotation::fromQuaternion(const Quaternion& q)
{
	quaternion.set(q);
	quaternion.normalize();
	auto& quaterionXYZ = quaternion.getArray();
	this->angle = 2.0f * Math::acos(quaterionXYZ[3]) / 3.1415927f * 180.0f;
	auto s = Math::sqrt(1.0f - quaterionXYZ[3] * quaterionXYZ[3]);
	if (s < 0.0010f) {
		this->axis.set(quaterionXYZ[0], quaterionXYZ[1], quaterionXYZ[2]);
	} else {
		this->axis.set(quaterionXYZ[0] / s, quaterionXYZ[1] / s, quaterionXYZ[2] / s);
	}
}

void Rotation::update()
{
	quaternion.identity();
	quaternion.rotate(axis, angle);
}

bool Rotation::interpolate(float currentAngle, float targetAngle, float timePassedSeconds, float deegreesPerSeconds, float& interpolatedAngle) {
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
		auto rotationAdd = timePassedSeconds * deegreesPerSeconds * Math::sign(targetAngle - currentAngle);
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

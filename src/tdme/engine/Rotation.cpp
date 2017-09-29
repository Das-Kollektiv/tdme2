#include <tdme/engine/Rotation.h>

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

Rotation::Rotation(float angle, Vector3* axis) 
{
	this->angle = angle;
	this->axis.set(*axis);
	this->quaternion.identity();
}

Vector3 Rotation::X_AXIS(1.0f, 0.0f, 0.0f);

Vector3 Rotation::Y_AXIS(1.0f, 0.0f, 0.0f);

Vector3 Rotation::Z_AXIS(1.0f, 0.0f, 0.0f);

float Rotation::getAngle()
{
	return angle;
}

void Rotation::setAngle(float angle)
{
	this->angle = angle;
}

Vector3* Rotation::getAxix()
{
	return &axis;
}

Quaternion* Rotation::getQuaternion()
{
	return &quaternion;
}

void Rotation::fromRotation(Rotation* rotation)
{
	angle = rotation->angle;
	axis.set(rotation->axis);
	quaternion.set(rotation->quaternion);
}

void Rotation::fromQuaternion(Quaternion* q)
{
	quaternion.set(*q);
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
	quaternion.rotate(angle, axis);
}

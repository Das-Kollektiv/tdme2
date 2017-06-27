// Generated from /tdme/src/tdme/engine/Rotation.java
#include <tdme/engine/Rotation.h>

#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::Rotation;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::math::Quaternion;
using tdme::math::Vector3;

Rotation::Rotation(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Rotation::Rotation() 
	: Rotation(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Rotation::Rotation(float angle, Vector3* axis) 
	: Rotation(*static_cast< ::default_init_tag* >(0))
{
	ctor(angle,axis);
}

Vector3* Rotation::X_AXIS;

Vector3* Rotation::Y_AXIS;

Vector3* Rotation::Z_AXIS;

void Rotation::ctor()
{
	super::ctor();
	this->angle = 0.0f;
	this->axis = new Vector3(0.0f, 0.0f, 0.0f);
	this->quaternion = (new Quaternion())->identity();
}

void Rotation::ctor(float angle, Vector3* axis)
{
	super::ctor();
	this->angle = angle;
	this->axis = axis;
	this->quaternion = (new Quaternion())->identity();
}

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
	return axis;
}

Quaternion* Rotation::getQuaternion()
{
	return quaternion;
}

void Rotation::fromRotation(Rotation* rotation)
{
	angle = rotation->angle;
	axis->set(rotation->axis);
	quaternion->set(rotation->quaternion);
}

void Rotation::fromQuaternion(Quaternion* q)
{
	quaternion->set(q);
	quaternion->normalize();
	auto quaterionXYZ = quaternion->getArray();
	this->angle = 2.0f * static_cast< float >(Math::acos((*quaterionXYZ)[3])) / 3.1415927f * 180.0f;
	auto s = static_cast< float >(Math::sqrt(1.0f - (*quaterionXYZ)[3] * (*quaterionXYZ)[3]));
	if (s < 0.0010f) {
		this->axis->set((*quaterionXYZ)[0], (*quaterionXYZ)[1], (*quaterionXYZ)[2]);
	} else {
		this->axis->set((*quaterionXYZ)[0] / s, (*quaterionXYZ)[1] / s, (*quaterionXYZ)[2] / s);
	}
}

void Rotation::update()
{
	quaternion->identity();
	quaternion->rotate(angle, axis);
}

String* Rotation::toString()
{
	return ::java::lang::StringBuilder().append(u"Rotation [angle="_j)->append(angle)
		->append(u", axis="_j)
		->append(static_cast< Object* >(axis))
		->append(u", quaternion="_j)
		->append(static_cast< Object* >(quaternion))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Rotation::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.Rotation", 20);
    return c;
}

void Rotation::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		X_AXIS = new Vector3(1.0f, 0.0f, 0.0f);
		Y_AXIS = new Vector3(0.0f, 1.0f, 0.0f);
		Z_AXIS = new Vector3(0.0f, 0.0f, 1.0f);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* Rotation::getClass0()
{
	return class_();
}


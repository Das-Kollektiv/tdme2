// Generated from /tdme/src/tdme/math/Vector3.java
#include <tdme/math/Vector3.h>

#include <java/lang/Float.h>
#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/math/MathTools.h>
#include <Array.h>
#include <cmath>

using tdme::math::Vector3;
using java::lang::Float;
using java::lang::Math;
using java::lang::String;
using java::lang::System;
using java::util::Arrays;
using tdme::math::MathTools;

Vector3::Vector3(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Vector3::Vector3() 
	: Vector3(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Vector3::Vector3(float x, float y, float z) 
	: Vector3(*static_cast< ::default_init_tag* >(0))
{
	ctor(x,y,z);
}

Vector3::Vector3(floatArray* v) 
	: Vector3(*static_cast< ::default_init_tag* >(0))
{
	ctor(v);
}

Vector3::Vector3(Vector3* v) 
	: Vector3(*static_cast< ::default_init_tag* >(0))
{
	ctor(v);
}

void Vector3::ctor()
{
	super::ctor();
	data = new floatArray(3);
	Arrays::fill(data, 0.0f);
}

void Vector3::ctor(float x, float y, float z)
{
	super::ctor();
	data = new floatArray(3);
	(*data)[0] = x;
	(*data)[1] = y;
	(*data)[2] = z;
}

void Vector3::ctor(floatArray* v)
{
	super::ctor();
	data = new floatArray(3);
	System::arraycopy(v, 0, data, 0, Math::min(v->length, data->length));
}

void Vector3::ctor(Vector3* v)
{
	super::ctor();
	data = new floatArray(3);
	System::arraycopy(v->data, 0, data, 0, Math::min(v->data->length, data->length));
}

Vector3* Vector3::set(float x, float y, float z)
{
	(*data)[0] = x;
	(*data)[1] = y;
	(*data)[2] = z;
	return this;
}

Vector3* Vector3::set(floatArray* v)
{
	System::arraycopy(v, 0, data, 0, Math::min(v->length, data->length));
	return this;
}

Vector3* Vector3::set(Vector3* v)
{
	System::arraycopy(v->data, 0, data, 0, data->length);
	return this;
}

float Vector3::getX()
{
	return (*data)[0];
}

void Vector3::setX(float x)
{
	(*data)[0] = x;
}

Vector3* Vector3::addX(float x)
{
	(*data)[0] += x;
	return this;
}

Vector3* Vector3::subX(float x)
{
	(*data)[0] -= x;
	return this;
}

float Vector3::getY()
{
	return (*data)[1];
}

Vector3* Vector3::setY(float y)
{
	(*data)[1] = y;
	return this;
}

Vector3* Vector3::addY(float y)
{
	(*data)[1] += y;
	return this;
}

Vector3* Vector3::subY(float y)
{
	(*data)[1] -= y;
	return this;
}

float Vector3::getZ()
{
	return (*data)[2];
}

Vector3* Vector3::setZ(float z)
{
	(*data)[2] = z;
	return this;
}

Vector3* Vector3::addZ(float z)
{
	(*data)[2] += z;
	return this;
}

Vector3* Vector3::subZ(float z)
{
	(*data)[2] -= z;
	return this;
}

floatArray* Vector3::getArray()
{
	return data;
}

Vector3* Vector3::computeCrossProduct(Vector3* v1, Vector3* v2)
{
	clinit();
	return new Vector3(((*v1->data)[1] * (*v2->data)[2]) - ((*v1->data)[2] * (*v2->data)[1]), ((*v1->data)[2] * (*v2->data)[0]) - ((*v1->data)[0] * (*v2->data)[2]), ((*v1->data)[0] * (*v2->data)[1]) - ((*v1->data)[1] * (*v2->data)[0]));
}

Vector3* Vector3::computeCrossProduct(Vector3* v1, Vector3* v2, Vector3* dest)
{
	clinit();
	dest->set(((*v1->data)[1] * (*v2->data)[2]) - ((*v1->data)[2] * (*v2->data)[1]), ((*v1->data)[2] * (*v2->data)[0]) - ((*v1->data)[0] * (*v2->data)[2]), ((*v1->data)[0] * (*v2->data)[1]) - ((*v1->data)[1] * (*v2->data)[0]));
	return dest;
}

float Vector3::computeDotProduct(Vector3* v1, Vector3* v2)
{
	clinit();
	return ((*v1->data)[0] * (*v2->data)[0]) + ((*v1->data)[1] * (*v2->data)[1]) + ((*v1->data)[2] * (*v2->data)[2]);
}

float Vector3::computeLength()
{
	return static_cast< float >(Math::sqrt(((*data)[0] * (*data)[0]) + ((*data)[1] * (*data)[1]) + ((*data)[2] * (*data)[2])));
}

float Vector3::computeVolume()
{
	return (*data)[0] * (*data)[1] * (*data)[2];
}

float Vector3::computeLengthSquared()
{
	return ((*data)[0] * (*data)[0]) + ((*data)[1] * (*data)[1]) + ((*data)[2] * (*data)[2]);
}

float Vector3::computeAngle(Vector3* a, Vector3* b)
{
	clinit();
	return static_cast< float >((180.0 / Math::PI * Math::acos(Vector3::computeDotProduct(a, b))));
}

float Vector3::computeAngle(Vector3* a, Vector3* b, Vector3* n)
{
	clinit();
	auto angle = Vector3::computeAngle(a, b);
	auto sign = MathTools::sign(Vector3::computeDotProduct(n, Vector3::computeCrossProduct(a, b)));
	if (Float::isNaN(sign) == true)
		sign = 1.0f;

	return std::fmod(((angle * sign) + 360.0f), 360.0f);
}

Vector3* Vector3::normalize()
{
	auto length = computeLength();
	(*data)[0] /= length;
	(*data)[1] /= length;
	(*data)[2] /= length;
	return this;
}

Vector3* Vector3::computeOrthogonalVector(Vector3* dest)
{
	if (Math::abs((*data)[0]) > MathTools::EPSILON) {
		(*dest->data)[1] = (*data)[0];
		(*dest->data)[2] = ((-2 * (*data)[0] * (*data)[1]* (*data)[2] + 2 * (*data)[0] * (*data)[2]) / (2 * ((*data)[2] * (*data)[2] + (*data)[0] * (*data)[0])));
		(*dest->data)[0] = ((-(*data)[0] * (*data)[1] - (*data)[2] * (*dest->data)[2]) / (*data)[0]);
	} else if (Math::abs((*data)[1]) > MathTools::EPSILON) {
		(*dest->data)[2] = (*data)[1];
		(*dest->data)[0] = ((-2 * (*data)[0] * (*data)[1]* (*data)[2] + 2 * (*data)[0] * (*data)[1]) / (2 * ((*data)[1] * (*data)[1] + (*data)[0] * (*data)[0])));
		(*dest->data)[1] = ((-(*data)[2] * (*data)[1] - (*data)[0] * (*dest->data)[0]) / (*data)[1]);
	} else if (Math::abs((*data)[2]) > MathTools::EPSILON) {
		(*dest->data)[0] = (*data)[2];
		(*dest->data)[1] = ((-2 * (*data)[0] * (*data)[1]* (*data)[2] + 2 * (*data)[1] * (*data)[2]) / (2 * ((*data)[2] * (*data)[2] + (*data)[1] * (*data)[1])));
		(*dest->data)[2] = ((-(*data)[0] * (*data)[2] - (*data)[1] * (*dest->data)[1]) / (*data)[2]);
	}
	return dest;
}

Vector3* Vector3::add(Vector3* v)
{
	(*data)[0] += (*v->data)[0];
	(*data)[1] += (*v->data)[1];
	(*data)[2] += (*v->data)[2];
	return this;
}

Vector3* Vector3::add(float value)
{
	(*data)[0] += value;
	(*data)[1] += value;
	(*data)[2] += value;
	return this;
}

Vector3* Vector3::sub(Vector3* v)
{
	(*data)[0] -= (*v->data)[0];
	(*data)[1] -= (*v->data)[1];
	(*data)[2] -= (*v->data)[2];
	return this;
}

Vector3* Vector3::sub(float value)
{
	(*data)[0] -= value;
	(*data)[1] -= value;
	(*data)[2] -= value;
	return this;
}

Vector3* Vector3::scale(float scale)
{
	(*data)[0] *= scale;
	(*data)[1] *= scale;
	(*data)[2] *= scale;
	return this;
}

Vector3* Vector3::scale(Vector3* scale)
{
	(*data)[0] *= (*scale->data)[0];
	(*data)[1] *= (*scale->data)[1];
	(*data)[2] *= (*scale->data)[2];
	return this;
}

Vector3* Vector3::clone()
{
	return new Vector3(data);
}

bool Vector3::equals(Vector3* v)
{
	return (this == v) || (Math::abs((*data)[0] - (*v->data)[0]) < MathTools::EPSILON && Math::abs((*data)[1] - (*v->data)[1]) < MathTools::EPSILON && Math::abs((*data)[2] - (*v->data)[2]) < MathTools::EPSILON);
}

bool Vector3::equals(Vector3* v, float tolerance)
{
	return (this == v) || (Math::abs((*data)[0] - (*v->data)[0]) < tolerance && Math::abs((*data)[1] - (*v->data)[1]) < tolerance && Math::abs((*data)[2] - (*v->data)[2]) < tolerance);
}

String* Vector3::toString()
{
	return Arrays::toString(data);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Vector3::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.math.Vector3", 17);
    return c;
}

bool Vector3::equals(Object* obj)
{
	return super::equals(obj);
}

java::lang::Class* Vector3::getClass0()
{
	return class_();
}


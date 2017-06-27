// Generated from /tdme/src/tdme/math/Quaternion.java
#include <tdme/math/Quaternion.h>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::math::Quaternion;
using java::lang::Math;
using java::lang::String;
using java::lang::System;
using java::util::Arrays;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Quaternion::Quaternion(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Quaternion::Quaternion() 
	: Quaternion(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Quaternion::Quaternion(Quaternion* q) 
	: Quaternion(*static_cast< ::default_init_tag* >(0))
{
	ctor(q);
}

Quaternion::Quaternion(float x, float y, float z, float w) 
	: Quaternion(*static_cast< ::default_init_tag* >(0))
{
	ctor(x,y,z,w);
}

Quaternion::Quaternion(Vector3* v, float w) 
	: Quaternion(*static_cast< ::default_init_tag* >(0))
{
	ctor(v,w);
}

void Quaternion::ctor()
{
	super::ctor();
	data = new floatArray(4);
	Arrays::fill(data, 0.0f);
	_data = new floatArray(4);
	t = new Vector3();
	q = new Vector3();
	qxt = new Vector3();
}

void Quaternion::ctor(Quaternion* q)
{
	super::ctor();
	data = new floatArray(4);
	_data = new floatArray(4);
	t = new Vector3();
	this->q = new Vector3();
	qxt = new Vector3();
	System::arraycopy(q->data, 0, data, 0, data->length);
}

void Quaternion::ctor(float x, float y, float z, float w)
{
	super::ctor();
	data = new floatArray(4);
	(*data)[0] = x;
	(*data)[1] = y;
	(*data)[2] = z;
	(*data)[3] = w;
}

Quaternion* Quaternion::set(float x, float y, float z, float w)
{
	(*data)[0] = x;
	(*data)[1] = y;
	(*data)[2] = z;
	(*data)[3] = w;
	return this;
}

void Quaternion::ctor(Vector3* v, float w)
{
	super::ctor();
	auto vectorXYZ = v->getArray();
	data = new floatArray(4);
	(*data)[0] = (*vectorXYZ)[0];
	(*data)[1] = (*vectorXYZ)[1];
	(*data)[2] = (*vectorXYZ)[2];
	(*data)[3] = w;
}

Quaternion* Quaternion::set(Quaternion* q)
{
	System::arraycopy(q->data, 0, data, 0, data->length);
	return this;
}

Quaternion* Quaternion::set(Vector3* v, float w)
{
	auto vectorXYZ = v->getArray();
	(*data)[0] = (*vectorXYZ)[0];
	(*data)[1] = (*vectorXYZ)[1];
	(*data)[2] = (*vectorXYZ)[2];
	(*data)[3] = w;
	return this;
}

Quaternion* Quaternion::identity()
{
	(*data)[0] = 0.0f;
	(*data)[1] = 0.0f;
	(*data)[2] = 0.0f;
	(*data)[3] = 1.0f;
	return this;
}

Quaternion* Quaternion::invert()
{
	(*data)[0] *= -1.0f;
	(*data)[1] *= -1.0f;
	(*data)[2] *= -1.0f;
	return this;
}

Quaternion* Quaternion::rotate(float angle, Vector3* v)
{
	auto radians = angle * 3.1415927f / 180.0f;
	auto sin = static_cast< float >(Math::sin(radians * 0.5));
	auto cos = static_cast< float >(Math::cos(radians * 0.5));
	auto axisXYZ = v->getArray();
	(*data)[0] = (*axisXYZ)[0] * sin;
	(*data)[1] = (*axisXYZ)[1] * sin;
	(*data)[2] = (*axisXYZ)[2] * sin;
	(*data)[3] = cos;
	return this;
}

Quaternion* Quaternion::normalize()
{
	auto magnitude = static_cast< float >(Math::sqrt((*data)[0] * (*data)[0] + (*data)[1] * (*data)[1] + (*data)[2] * (*data)[2] + (*data)[3] * (*data)[3]));
	(*data)[0] = (*data)[0] / magnitude;
	(*data)[1] = (*data)[1] / magnitude;
	(*data)[2] = (*data)[2] / magnitude;
	(*data)[3] = (*data)[3] / magnitude;
	return this;
}

Quaternion* Quaternion::multiply(Quaternion* q)
{
	(*_data)[0] = (*data)[3] * (*q->data)[0] + (*data)[0] * (*q->data)[3] + (*data)[1] * (*q->data)[2] - (*data)[2] * (*q->data)[1];
	(*_data)[1] = (*data)[3] * (*q->data)[1] - (*data)[0] * (*q->data)[2] + (*data)[1] * (*q->data)[3] + (*data)[2] * (*q->data)[0];
	(*_data)[2] = (*data)[3] * (*q->data)[2] + (*data)[0] * (*q->data)[1] - (*data)[1] * (*q->data)[0] + (*data)[2] * (*q->data)[3];
	(*_data)[3] = (*data)[3] * (*q->data)[3] - (*data)[0] * (*q->data)[0] - (*data)[1] * (*q->data)[1] - (*data)[2] * (*q->data)[2];
	System::arraycopy(_data, 0, data, 0, data->length);
	return this;
}

Quaternion* Quaternion::add(Quaternion* q)
{
	(*data)[0] += (*q->data)[0];
	(*data)[1] += (*q->data)[1];
	(*data)[2] += (*q->data)[2];
	(*data)[3] += (*q->data)[3];
	return this;
}

Quaternion* Quaternion::scale(float value)
{
	(*data)[0] *= value;
	(*data)[1] *= value;
	(*data)[2] *= value;
	(*data)[3] *= value;
	return this;
}

Vector3* Quaternion::multiply(Vector3* v, Vector3* dest)
{
	q->set(data);
	Vector3::computeCrossProduct(q, v, t)->scale(2.0f);
	Vector3::computeCrossProduct(q, t, qxt);
	dest->set(v);
	dest->add(qxt);
	dest->add(t->scale((*data)[3]));
	return dest;
}

Matrix4x4* Quaternion::computeMatrix(Matrix4x4* matrix)
{
	matrix->set(1.0f - 2.0f * ((*data)[1] * (*data)[1] + (*data)[2] * (*data)[2]), 2.0f * ((*data)[0] * (*data)[1] + (*data)[2] * (*data)[3]), 2.0f * ((*data)[0] * (*data)[2] - (*data)[1] * (*data)[3]), 0.0f, 2.0f * ((*data)[0] * (*data)[1] - (*data)[2] * (*data)[3]), 1.0f - 2.0f * ((*data)[0] * (*data)[0] + (*data)[2] * (*data)[2]), 2.0f * ((*data)[2] * (*data)[1] + (*data)[0] * (*data)[3]), 0.0f, 2.0f * ((*data)[0] * (*data)[2] + (*data)[1] * (*data)[3]), 2.0f * ((*data)[1] * (*data)[2] - (*data)[0] * (*data)[3]), 1.0f - 2.0f * ((*data)[0] * (*data)[0] + (*data)[1] * (*data)[1]), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	return matrix;
}

floatArray* Quaternion::getArray()
{
	return data;
}

String* Quaternion::toString()
{
	return Arrays::toString(data);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Quaternion::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.math.Quaternion", 20);
    return c;
}

java::lang::Class* Quaternion::getClass0()
{
	return class_();
}


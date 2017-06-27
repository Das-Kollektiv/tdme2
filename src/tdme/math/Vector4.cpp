// Generated from /tdme/src/tdme/math/Vector4.java
#include <tdme/math/Vector4.h>

#include <java/lang/String.h>
#include <java/util/Arrays.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::math::Vector4;
using java::lang::String;
using java::util::Arrays;
using tdme::math::Vector3;

Vector4::Vector4(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Vector4::Vector4() 
	: Vector4(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Vector4::Vector4(Vector3* v, float w) 
	: Vector4(*static_cast< ::default_init_tag* >(0))
{
	ctor(v,w);
}

Vector4::Vector4(float x, float y, float z, float w) 
	: Vector4(*static_cast< ::default_init_tag* >(0))
{
	ctor(x,y,z,w);
}

Vector4::Vector4(floatArray* v) 
	: Vector4(*static_cast< ::default_init_tag* >(0))
{
	ctor(v);
}

void Vector4::ctor()
{
	super::ctor();
	data = new floatArray(4);
	(*data)[0] = 0.0f;
	(*data)[1] = 0.0f;
	(*data)[2] = 0.0f;
	(*data)[3] = 0.0f;
}

void Vector4::ctor(Vector3* v, float w)
{
	super::ctor();
	data = new floatArray(4);
	(*data)[0] = (*v->data)[0];
	(*data)[1] = (*v->data)[1];
	(*data)[2] = (*v->data)[2];
	(*data)[3] = w;
}

void Vector4::ctor(float x, float y, float z, float w)
{
	super::ctor();
	data = new floatArray(4);
	(*data)[0] = x;
	(*data)[1] = y;
	(*data)[2] = z;
	(*data)[3] = w;
}

void Vector4::ctor(floatArray* v)
{
	super::ctor();
	data = new floatArray(4);
	(*data)[0] = (*v)[0];
	(*data)[1] = (*v)[1];
	(*data)[2] = (*v)[2];
	(*data)[3] = (*v)[3];
}

Vector4* Vector4::set(float x, float y, float z, float w)
{
	(*data)[0] = x;
	(*data)[1] = y;
	(*data)[2] = z;
	(*data)[3] = w;
	return this;
}

Vector4* Vector4::set(floatArray* v)
{
	(*data)[0] = (*v)[0];
	(*data)[1] = (*v)[1];
	(*data)[2] = (*v)[2];
	(*data)[3] = (*v)[3];
	return this;
}

Vector4* Vector4::set(Vector4* v)
{
	(*data)[0] = (*v->data)[0];
	(*data)[1] = (*v->data)[1];
	(*data)[2] = (*v->data)[2];
	(*data)[3] = (*v->data)[3];
	return this;
}

Vector4* Vector4::set(Vector3* v, float w)
{
	(*data)[0] = (*v->data)[0];
	(*data)[1] = (*v->data)[1];
	(*data)[2] = (*v->data)[2];
	(*data)[3] = w;
	return this;
}

float Vector4::getX()
{
	return (*data)[0];
}

void Vector4::setX(float x)
{
	(*data)[0] = x;
}

float Vector4::getY()
{
	return (*data)[1];
}

void Vector4::setY(float y)
{
	(*data)[1] = y;
}

float Vector4::getZ()
{
	return (*data)[2];
}

void Vector4::setZ(float z)
{
	(*data)[2] = z;
}

float Vector4::getW()
{
	return (*data)[3];
}

void Vector4::setW(float w)
{
	(*data)[3] = w;
}

Vector4* Vector4::scale(float scale)
{
	(*data)[0] *= scale;
	(*data)[1] *= scale;
	(*data)[2] *= scale;
	(*data)[3] *= scale;
	return this;
}

Vector4* Vector4::scale(Vector4* scale)
{
	(*data)[0] *= (*scale->data)[0];
	(*data)[1] *= (*scale->data)[1];
	(*data)[2] *= (*scale->data)[2];
	(*data)[3] *= (*scale->data)[3];
	return this;
}

floatArray* Vector4::getArray()
{
	return data;
}

Vector4* Vector4::clone()
{
	return new Vector4(data);
}

String* Vector4::toString()
{
	return Arrays::toString(data);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Vector4::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.math.Vector4", 17);
    return c;
}

java::lang::Class* Vector4::getClass0()
{
	return class_();
}


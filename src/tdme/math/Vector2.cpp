// Generated from /tdme/src/tdme/math/Vector2.java
#include <tdme/math/Vector2.h>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/util/Arrays.h>
#include <Array.h>

using tdme::math::Vector2;
using java::lang::Math;
using java::lang::String;
using java::util::Arrays;

Vector2::Vector2(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Vector2::Vector2() 
	: Vector2(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Vector2::Vector2(float x, float y) 
	: Vector2(*static_cast< ::default_init_tag* >(0))
{
	ctor(x,y);
}

Vector2::Vector2(floatArray* v) 
	: Vector2(*static_cast< ::default_init_tag* >(0))
{
	ctor(v);
}

Vector2::Vector2(Vector2* v) 
	: Vector2(*static_cast< ::default_init_tag* >(0))
{
	ctor(v);
}

void Vector2::ctor()
{
	super::ctor();
	data = new floatArray(2);
	(*data)[0] = 0.0f;
	(*data)[1] = 0.0f;
}

void Vector2::ctor(float x, float y)
{
	super::ctor();
	data = new floatArray(2);
	(*data)[0] = x;
	(*data)[1] = y;
}

void Vector2::ctor(floatArray* v)
{
	super::ctor();
	data = new floatArray(2);
	(*data)[0] = (*v)[0];
	(*data)[1] = (*v)[1];
}

void Vector2::ctor(Vector2* v)
{
	super::ctor();
	data = new floatArray(2);
	(*data)[0] = (*v->data)[0];
	(*data)[1] = (*v->data)[1];
}

Vector2* Vector2::set(float x, float y)
{
	(*data)[0] = x;
	(*data)[1] = y;
	return this;
}

Vector2* Vector2::set(floatArray* v)
{
	(*data)[0] = (*v)[0];
	(*data)[1] = (*v)[1];
	return this;
}

Vector2* Vector2::set(Vector2* v)
{
	(*data)[0] = (*v->data)[0];
	(*data)[1] = (*v->data)[1];
	return this;
}

float Vector2::getX()
{
	return (*data)[0];
}

void Vector2::setX(float x)
{
	(*data)[0] = x;
}

float Vector2::getY()
{
	return (*data)[1];
}

void Vector2::setY(float y)
{
	(*data)[1] = y;
}

Vector2* Vector2::add(Vector2* v)
{
	(*data)[0] += (*v->data)[0];
	(*data)[1] += (*v->data)[1];
	return this;
}

Vector2* Vector2::sub(Vector2* v)
{
	(*data)[0] -= (*v->data)[0];
	(*data)[1] -= (*v->data)[1];
	return this;
}

Vector2* Vector2::scale(float scale)
{
	(*data)[0] *= scale;
	(*data)[1] *= scale;
	return this;
}

Vector2* Vector2::scale(Vector2* scale)
{
	(*data)[0] *= (*scale->data)[0];
	(*data)[1] *= (*scale->data)[1];
	return this;
}

float Vector2::computeLength()
{
	return static_cast< float >(Math::sqrt(((*data)[0] * (*data)[0]) + ((*data)[1] * (*data)[1])));
}

floatArray* Vector2::getArray()
{
	return data;
}

String* Vector2::toString()
{
	return Arrays::toString(data);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Vector2::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.math.Vector2", 17);
    return c;
}

java::lang::Class* Vector2::getClass0()
{
	return class_();
}


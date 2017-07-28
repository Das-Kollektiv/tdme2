// Generated from /tdme/src/tdme/math/Vector2.java
#include <tdme/math/Vector2.h>

#include <array>

#include <java/lang/Math.h>

using std::array;

using tdme::math::Vector2;
using java::lang::Math;

Vector2::Vector2() 
{
	data.fill(0.0f);
}

Vector2::Vector2(float x, float y) 
{
	data[0] = x;
	data[1] = y;
}

Vector2::Vector2(floatArray* v) 
{
	data[0] = (*v)[0];
	data[1] = (*v)[1];
}

Vector2::Vector2(Vector2* v) 
{
	data[0] = v->data[0];
	data[1] = v->data[1];
}

Vector2* Vector2::set(float x, float y)
{
	data[0] = x;
	data[1] = y;
	return this;
}

Vector2* Vector2::set(floatArray* v)
{
	data[0] = (*v)[0];
	data[1] = (*v)[1];
	return this;
}

Vector2* Vector2::set(Vector2* v)
{
	data[0] = v->data[0];
	data[1] = v->data[1];
	return this;
}

float Vector2::getX()
{
	return data[0];
}

void Vector2::setX(float x)
{
	data[0] = x;
}

float Vector2::getY()
{
	return data[1];
}

void Vector2::setY(float y)
{
	data[1] = y;
}

Vector2* Vector2::add(Vector2* v)
{
	data[0] += v->data[0];
	data[1] += v->data[1];
	return this;
}

Vector2* Vector2::sub(Vector2* v)
{
	data[0] -= v->data[0];
	data[1] -= v->data[1];
	return this;
}

Vector2* Vector2::scale(float scale)
{
	data[0] *= scale;
	data[1] *= scale;
	return this;
}

Vector2* Vector2::scale(Vector2* scale)
{
	data[0] *= scale->data[0];
	data[1] *= scale->data[1];
	return this;
}

float Vector2::computeLength()
{
	return static_cast< float >(Math::sqrt((data[0] * data[0]) + (data[1] * data[1])));
}

array<float, 2>* Vector2::getArray()
{
	return &data;
}

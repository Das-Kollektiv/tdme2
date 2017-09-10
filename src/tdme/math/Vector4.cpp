#include <tdme/math/Vector4.h>

#include <array>

#include <tdme/math/Vector3.h>

using std::array;

using tdme::math::Vector4;
using tdme::math::Vector3;

Vector4::Vector4() 
{
	data.fill(0.0f);
}

Vector4::Vector4(Vector4* v)
{
	data = v->data;
}

Vector4::Vector4(Vector3* v, float w) 
{
	data[0] = v->data[0];
	data[1] = v->data[1];
	data[2] = v->data[2];
	data[3] = w;
}

Vector4::Vector4(float x, float y, float z, float w) 
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
}

Vector4::Vector4(array<float, 4>* v)
{
	data = *v;
}

Vector4* Vector4::set(float x, float y, float z, float w)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
	return this;
}

Vector4* Vector4::set(array<float, 4>* v)
{
	data = *v;
	return this;
}

Vector4* Vector4::set(Vector4* v)
{
	data[0] = v->data[0];
	data[1] = v->data[1];
	data[2] = v->data[2];
	data[3] = v->data[3];
	return this;
}

Vector4* Vector4::set(Vector3* v, float w)
{
	data[0] = v->data[0];
	data[1] = v->data[1];
	data[2] = v->data[2];
	data[3] = w;
	return this;
}

float Vector4::getX()
{
	return data[0];
}

void Vector4::setX(float x)
{
	data[0] = x;
}

float Vector4::getY()
{
	return data[1];
}

void Vector4::setY(float y)
{
	data[1] = y;
}

float Vector4::getZ()
{
	return data[2];
}

void Vector4::setZ(float z)
{
	data[2] = z;
}

float Vector4::getW()
{
	return data[3];
}

void Vector4::setW(float w)
{
	data[3] = w;
}

Vector4* Vector4::scale(float scale)
{
	data[0] *= scale;
	data[1] *= scale;
	data[2] *= scale;
	data[3] *= scale;
	return this;
}

Vector4* Vector4::scale(Vector4* scale)
{
	data[0] *= scale->data[0];
	data[1] *= scale->data[1];
	data[2] *= scale->data[2];
	data[3] *= scale->data[3];
	return this;
}

array<float, 4>* Vector4::getArray()
{
	return &data;
}

Vector4* Vector4::clone()
{
	return new Vector4(this);
}


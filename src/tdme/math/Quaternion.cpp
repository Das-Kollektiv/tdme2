#include <tdme/math/Quaternion.h>

#include <array>

#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using std::array;

using tdme::math::Quaternion;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Quaternion::Quaternion() 
{
	data.fill(0.0f);
}

Quaternion::Quaternion(Quaternion* q) 
{
	data = q->data;
}

Quaternion::Quaternion(float x, float y, float z, float w) 
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
}

Quaternion::Quaternion(Vector3* v, float w) 
{
	data[0] = v->data[0];
	data[1] = v->data[1];
	data[2] = v->data[2];
	data[3] = w;
}

Quaternion* Quaternion::set(float x, float y, float z, float w)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
	return this;
}

Quaternion* Quaternion::set(Quaternion* q)
{
	data = q->data;
	return this;
}

Quaternion* Quaternion::set(Vector3* v, float w)
{
	data[0] = v->data[0];
	data[1] = v->data[1];
	data[2] = v->data[2];
	data[3] = w;
	return this;
}

Quaternion* Quaternion::identity()
{
	data[0] = 0.0f;
	data[1] = 0.0f;
	data[2] = 0.0f;
	data[3] = 1.0f;
	return this;
}

Quaternion* Quaternion::invert()
{
	data[0] *= -1.0f;
	data[1] *= -1.0f;
	data[2] *= -1.0f;
	return this;
}

Quaternion* Quaternion::rotate(float angle, Vector3* v)
{
	auto radians = angle * 3.1415927f / 180.0f;
	auto sin = static_cast< float >(Math::sin(radians * 0.5));
	auto cos = static_cast< float >(Math::cos(radians * 0.5));
	auto axisXYZ = v->getArray();
	data[0] = (*axisXYZ)[0] * sin;
	data[1] = (*axisXYZ)[1] * sin;
	data[2] = (*axisXYZ)[2] * sin;
	data[3] = cos;
	return this;
}

Quaternion* Quaternion::normalize()
{
	auto magnitude = static_cast< float >(Math::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]));
	data[0] = data[0] / magnitude;
	data[1] = data[1] / magnitude;
	data[2] = data[2] / magnitude;
	data[3] = data[3] / magnitude;
	return this;
}

Quaternion* Quaternion::multiply(Quaternion* q)
{
	array<float, 4> _data;
	_data[0] = data[3] * q->data[0] + data[0] * q->data[3] + data[1] * q->data[2] - data[2] * q->data[1];
	_data[1] = data[3] * q->data[1] - data[0] * q->data[2] + data[1] * q->data[3] + data[2] * q->data[0];
	_data[2] = data[3] * q->data[2] + data[0] * q->data[1] - data[1] * q->data[0] + data[2] * q->data[3];
	_data[3] = data[3] * q->data[3] - data[0] * q->data[0] - data[1] * q->data[1] - data[2] * q->data[2];
	data = _data;
	return this;
}

Quaternion* Quaternion::add(Quaternion* q)
{
	data[0] += q->data[0];
	data[1] += q->data[1];
	data[2] += q->data[2];
	data[3] += q->data[3];
	return this;
}

Quaternion* Quaternion::scale(float value)
{
	data[0] *= value;
	data[1] *= value;
	data[2] *= value;
	data[3] *= value;
	return this;
}

Vector3* Quaternion::multiply(Vector3* v, Vector3* dest)
{
	Vector3 q;
	Vector3 t;
	Vector3 qxt;
	q.set(data[0], data[1], data[2]);
	Vector3::computeCrossProduct(&q, v, &t)->scale(2.0f);
	Vector3::computeCrossProduct(&q, &t, &qxt);
	dest->set(v);
	dest->add(&qxt);
	dest->add(t.scale(data[3]));
	return dest;
}

Matrix4x4* Quaternion::computeMatrix(Matrix4x4* matrix)
{
	matrix->set(
		1.0f - 2.0f * (data[1] * data[1] + data[2] * data[2]),
		2.0f * (data[0] * data[1] + data[2] * data[3]),
		2.0f * (data[0] * data[2] - data[1] * data[3]),
		0.0f,
		2.0f * (data[0] * data[1] - data[2] * data[3]),
		1.0f - 2.0f * (data[0] * data[0] + data[2] * data[2]),
		2.0f * (data[2] * data[1] + data[0] * data[3]),
		0.0f,
		2.0f * (data[0] * data[2] + data[1] * data[3]),
		2.0f * (data[1] * data[2] - data[0] * data[3]),
		1.0f - 2.0f * (data[0] * data[0] + data[1] * data[1]),
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f
	);
	return matrix;
}

array<float, 4>* Quaternion::getArray()
{
	return &data;
}

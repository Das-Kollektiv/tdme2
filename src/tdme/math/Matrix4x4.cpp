#include <tdme/math/Matrix4x4.h>

#include <array>

#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>

using std::array;

using tdme::math::Matrix4x4;
using tdme::math::Math;
using tdme::math::MathTools;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::math::Vector4;

Matrix4x4::Matrix4x4() 
{
	data.fill(0.0f);
}

Matrix4x4::Matrix4x4(array<float, 16>* m)
{
	data = *m;
}

Matrix4x4::Matrix4x4(Matrix4x4* matrix) 
{
	data = matrix->data;
}

Matrix4x4::Matrix4x4(float r0c0, float r1c0, float r2c0, float r3c0, float r0c1, float r1c1, float r2c1, float r3c1, float r0c2, float r1c2, float r2c2, float r3c2, float r0c3, float r1c3, float r2c3, float r3c3) 
{
	set(r0c0, r1c0, r2c0, r3c0, r0c1, r1c1, r2c1, r3c1, r0c2, r1c2, r2c2, r3c2, r0c3, r1c3, r2c3, r3c3);
}

Matrix4x4* Matrix4x4::set(float r0c0, float r1c0, float r2c0, float r3c0, float r0c1, float r1c1, float r2c1, float r3c1, float r0c2, float r1c2, float r2c2, float r3c2, float r0c3, float r1c3, float r2c3, float r3c3)
{
	data[0] = r0c0;
	data[1] = r1c0;
	data[2] = r2c0;
	data[3] = r3c0;
	data[4] = r0c1;
	data[5] = r1c1;
	data[6] = r2c1;
	data[7] = r3c1;
	data[8] = r0c2;
	data[9] = r1c2;
	data[10] = r2c2;
	data[11] = r3c2;
	data[12] = r0c3;
	data[13] = r1c3;
	data[14] = r2c3;
	data[15] = r3c3;
	return this;
}

Matrix4x4* Matrix4x4::set(array<float, 16>* m)
{
	data = *m;
	return this;
}

Matrix4x4* Matrix4x4::set(Matrix4x4* m)
{
	data = m->data;
	return this;
}

Matrix4x4* Matrix4x4::getAxes(Vector3* xAxis, Vector3* yAxis, Vector3* zAxis)
{
	xAxis->set(data[0], data[1], data[2]);
	yAxis->set(data[4], data[5], data[6]);
	zAxis->set(data[8], data[9], data[10]);
	return this;
}

Matrix4x4* Matrix4x4::setAxes(Vector3* xAxis, Vector3* yAxis, Vector3* zAxis)
{
	data[0] = xAxis->data[0];
	data[1] = xAxis->data[1];
	data[2] = xAxis->data[2];
	data[3] = 0.0f;
	data[4] = yAxis->data[0];
	data[5] = yAxis->data[1];
	data[6] = yAxis->data[2];
	data[7] = 0.0f;
	data[8] = zAxis->data[0];
	data[9] = zAxis->data[1];
	data[10] = zAxis->data[2];
	data[11] = 0.0f;
	return this;
}

Matrix4x4* Matrix4x4::getTranslation(Vector3* translation)
{
	translation->set(data[12], data[13], data[14]);
	return this;
}

Matrix4x4* Matrix4x4::setTranslation(Vector3* translation)
{
	data[12] = translation->data[0];
	data[13] = translation->data[1];
	data[14] = translation->data[2];
	return this;
}

Matrix4x4* Matrix4x4::getScale(Vector3* scale)
{
	Vector3 tmpVector3;
	tmpVector3.set(data[0], data[1], data[2]);
	scale->data[0] = tmpVector3.computeLength();
	tmpVector3.set(data[4], data[5], data[6]);
	scale->data[1] = tmpVector3.computeLength();
	tmpVector3.set(data[8], data[9], data[10]);
	scale->data[2] = tmpVector3.computeLength();
	return this;
}

Matrix4x4* Matrix4x4::setScale(Vector3* scale)
{
	Vector3 tmpVector3;
	tmpVector3.set(data[0], data[1], data[2]);
	tmpVector3.normalize();
	tmpVector3.scale(scale->data[0]);
	data[0] = tmpVector3.data[0];
	data[1] = tmpVector3.data[1];
	data[2] = tmpVector3.data[2];
	tmpVector3.set(data[4], data[5], data[6]);
	tmpVector3.normalize();
	tmpVector3.scale(scale->data[1]);
	data[4] = tmpVector3.data[0];
	data[5] = tmpVector3.data[1];
	data[6] = tmpVector3.data[2];
	tmpVector3.set(data[8], data[9], data[10]);
	tmpVector3.normalize();
	tmpVector3.scale(scale->data[2]);
	data[8] = tmpVector3.data[0];
	data[9] = tmpVector3.data[1];
	data[10] = tmpVector3.data[2];
	return this;
}

Matrix4x4* Matrix4x4::identity()
{
	data[0] = 1.0f;
	data[1] = 0.0f;
	data[2] = 0.0f;
	data[3] = 0.0f;
	data[4] = 0.0f;
	data[5] = 1.0f;
	data[6] = 0.0f;
	data[7] = 0.0f;
	data[8] = 0.0f;
	data[9] = 0.0f;
	data[10] = 1.0f;
	data[11] = 0.0f;
	data[12] = 0.0f;
	data[13] = 0.0f;
	data[14] = 0.0f;
	data[15] = 1.0f;
	return this;
}

Vector3* Matrix4x4::multiply(Vector3* v, Vector3* dest)
{
	return dest->set(
		v->data[0] * data[0] + v->data[1] * data[4] + v->data[2] * data[8] + data[12],
		v->data[0] * data[1] + v->data[1] * data[5] + v->data[2] * data[9] + data[13],
		v->data[0] * data[2] + v->data[1] * data[6] + v->data[2] * data[10] + data[14]
	);
}

Vector3* Matrix4x4::multiplyNoTranslation(Vector3* v, Vector3* dest)
{
	return dest->set(
		v->data[0] * data[0] + v->data[1] * data[4] + v->data[2] * data[8],
		v->data[0] * data[1] + v->data[1] * data[5] + v->data[2] * data[9],
		v->data[0] * data[2] + v->data[1] * data[6] + v->data[2] * data[10]
	);
}

Vector4* Matrix4x4::multiply(Vector4* v, Vector4* dest)
{
	dest->set(
		v->data[0] * data[0] + v->data[1] * data[4] + v->data[2] * data[8] + v->data[3] * data[12],
		v->data[0] * data[1] + v->data[1] * data[5] + v->data[2] * data[9] + v->data[3] * data[13],
		v->data[0] * data[2] + v->data[1] * data[6] + v->data[2] * data[10] + v->data[3] * data[14],
		v->data[0] * data[3] + v->data[1] * data[7] + v->data[2] * data[11] + v->data[3] * data[15]
	);
	return dest;
}

Matrix4x4* Matrix4x4::multiply(Matrix4x4* m)
{
	array<float, 16> _data;
	_data[0] = data[0] * m->data[0] + data[1] * m->data[4] + data[2] * m->data[8] + data[3] * m->data[12];
	_data[1] = data[0] * m->data[1] + data[1] * m->data[5] + data[2] * m->data[9] + data[3] * m->data[13];
	_data[2] = data[0] * m->data[2] + data[1] * m->data[6] + data[2] * m->data[10] + data[3] * m->data[14];
	_data[3] = data[0] * m->data[3] + data[1] * m->data[7] + data[2] * m->data[11] + data[3] * m->data[15];
	_data[4] = data[4] * m->data[0] + data[5] * m->data[4] + data[6] * m->data[8] + data[7] * m->data[12];
	_data[5] = data[4] * m->data[1] + data[5] * m->data[5] + data[6] * m->data[9] + data[7] * m->data[13];
	_data[6] = data[4] * m->data[2] + data[5] * m->data[6] + data[6] * m->data[10] + data[7] * m->data[14];
	_data[7] = data[4] * m->data[3] + data[5] * m->data[7] + data[6] * m->data[11] + data[7] * m->data[15];
	_data[8] = data[8] * m->data[0] + data[9] * m->data[4] + data[10] * m->data[8] + data[11] * m->data[12];
	_data[9] = data[8] * m->data[1] + data[9] * m->data[5] + data[10] * m->data[9] + data[11] * m->data[13];
	_data[10] = data[8] * m->data[2] + data[9] * m->data[6] + data[10] * m->data[10] + data[11] * m->data[14];
	_data[11] = data[8] * m->data[3] + data[9] * m->data[7] + data[10] * m->data[11] + data[11] * m->data[15];
	_data[12] = data[12] * m->data[0] + data[13] * m->data[4] + data[14] * m->data[8] + data[15] * m->data[12];
	_data[13] = data[12] * m->data[1] + data[13] * m->data[5] + data[14] * m->data[9] + data[15] * m->data[13];
	_data[14] = data[12] * m->data[2] + data[13] * m->data[6] + data[14] * m->data[10] + data[15] * m->data[14];
	_data[15] = data[12] * m->data[3] + data[13] * m->data[7] + data[14] * m->data[11] + data[15] * m->data[15];
	data = _data;
	return this;
}

Matrix4x4* Matrix4x4::scale(float s)
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
	data[4] *= s;
	data[5] *= s;
	data[6] *= s;
	data[7] *= s;
	data[8] *= s;
	data[9] *= s;
	data[10] *= s;
	data[11] *= s;
	return this;
}

Matrix4x4* Matrix4x4::scale(Vector3* v)
{
	data[0] *= v->data[0];
	data[1] *= v->data[0];
	data[2] *= v->data[0];
	data[3] *= v->data[0];
	data[4] *= v->data[1];
	data[5] *= v->data[1];
	data[6] *= v->data[1];
	data[7] *= v->data[1];
	data[8] *= v->data[2];
	data[9] *= v->data[2];
	data[10] *= v->data[2];
	data[11] *= v->data[2];
	return this;
}

Matrix4x4* Matrix4x4::translate(Vector3* v)
{
	data[12] += v->data[0] * data[0] + v->data[1] * data[4] + v->data[2] * data[8];
	data[13] += v->data[0] * data[1] + v->data[1] * data[5] + v->data[2] * data[9];
	data[14] += v->data[0] * data[2] + v->data[1] * data[6] + v->data[2] * data[10];
	return this;
}

Matrix4x4* Matrix4x4::rotate(float angle, Vector3* v)
{
	set((new Quaternion())->identity()->rotate(angle, v)->computeMatrix(this));
	return this;
}

Matrix4x4* Matrix4x4::transpose()
{
	array <float, 16> _data;
	_data[0] = data[0];
	_data[1] = data[4];
	_data[2] = data[8];
	_data[3] = data[12];
	_data[4] = data[1];
	_data[5] = data[5];
	_data[6] = data[9];
	_data[7] = data[13];
	_data[8] = data[2];
	_data[9] = data[6];
	_data[10] = data[10];
	_data[11] = data[14];
	_data[12] = data[3];
	_data[13] = data[7];
	_data[14] = data[11];
	_data[15] = data[15];
	data = _data;
	return this;
}

Matrix4x4* Matrix4x4::invert()
{
	array <float, 16> _data;
	_data[0] = data[5] * data[10] * data[15] - data[5] * data[11] * data[14] - data[9] * data[6] * data[15] + data[9] * data[7] * data[14] + data[13] * data[6] * data[11] - data[13] * data[7] * data[10];
	_data[4] = -data[4] * data[10] * data[15] + data[4] * data[11] * data[14] + data[8] * data[6] * data[15] - data[8] * data[7] * data[14] - data[12] * data[6] * data[11] + data[12] * data[7] * data[10];
	_data[8] = data[4] * data[9] * data[15] - data[4] * data[11] * data[13] - data[8] * data[5] * data[15] + data[8] * data[7] * data[13] + data[12] * data[5] * data[11] - data[12] * data[7] * data[9];
	_data[12] = -data[4] * data[9] * data[14] + data[4] * data[10] * data[13] + data[8] * data[5] * data[14] - data[8] * data[6] * data[13] - data[12] * data[5] * data[10] + data[12] * data[6] * data[9];
	_data[1] = -data[1] * data[10] * data[15] + data[1] * data[11] * data[14] + data[9] * data[2] * data[15] - data[9] * data[3] * data[14] - data[13] * data[2] * data[11] + data[13] * data[3] * data[10];
	_data[5] = data[0] * data[10] * data[15] - data[0] * data[11] * data[14] - data[8] * data[2] * data[15] + data[8] * data[3] * data[14] + data[12] * data[2] * data[11] - data[12] * data[3] * data[10];
	_data[9] = -data[0] * data[9] * data[15] + data[0] * data[11] * data[13] + data[8] * data[1] * data[15] - data[8] * data[3] * data[13] - data[12] * data[1] * data[11] + data[12] * data[3] * data[9];
	_data[13] = data[0] * data[9] * data[14] - data[0] * data[10] * data[13] - data[8] * data[1] * data[14] + data[8] * data[2] * data[13] + data[12] * data[1] * data[10] - data[12] * data[2] * data[9];
	_data[2] = data[1] * data[6] * data[15] - data[1] * data[7] * data[14] - data[5] * data[2] * data[15] + data[5] * data[3] * data[14] + data[13] * data[2] * data[7] - data[13] * data[3] * data[6];
	_data[6] = -data[0] * data[6] * data[15] + data[0] * data[7] * data[14] + data[4] * data[2] * data[15] - data[4] * data[3] * data[14] - data[12] * data[2] * data[7] + data[12] * data[3] * data[6];
	_data[10] = data[0] * data[5] * data[15] - data[0] * data[7] * data[13] - data[4] * data[1] * data[15] + data[4] * data[3] * data[13] + data[12] * data[1] * data[7] - data[12] * data[3] * data[5];
	_data[14] = -data[0] * data[5] * data[14] + data[0] * data[6] * data[13] + data[4] * data[1] * data[14] - data[4] * data[2] * data[13] - data[12] * data[1] * data[6] + data[12] * data[2] * data[5];
	_data[3] = -data[1] * data[6] * data[11] + data[1] * data[7] * data[10] + data[5] * data[2] * data[11] - data[5] * data[3] * data[10] - data[9] * data[2] * data[7] + data[9] * data[3] * data[6];
	_data[7] = data[0] * data[6] * data[11] - data[0] * data[7] * data[10] - data[4] * data[2] * data[11] + data[4] * data[3] * data[10] + data[8] * data[2] * data[7] - data[8] * data[3] * data[6];
	_data[11] = -data[0] * data[5] * data[11] + data[0] * data[7] * data[9] + data[4] * data[1] * data[11] - data[4] * data[3] * data[9] - data[8] * data[1] * data[7] + data[8] * data[3] * data[5];
	_data[15] = data[0] * data[5] * data[10] - data[0] * data[6] * data[9] - data[4] * data[1] * data[10] + data[4] * data[2] * data[9] + data[8] * data[1] * data[6] - data[8] * data[2] * data[5];
	auto determinant = data[0] * _data[0] + data[1] * _data[4] + data[2] * _data[8] + data[3] * _data[12];
	if (determinant == 0.0f) {
		identity();
		return this;
	}
	determinant = 1.0f / determinant;
	for (auto i = 0; i < _data.size(); i++)
		_data[i] = _data[i] * determinant;

	data = _data;

	return this;
}

bool Matrix4x4::equals(Matrix4x4* m)
{
	return
		Math::abs(data[0] - m->data[0]) < MathTools::EPSILON &&
		Math::abs(data[1] - m->data[1]) < MathTools::EPSILON &&
		Math::abs(data[2] - m->data[2]) < MathTools::EPSILON &&
		Math::abs(data[3] - m->data[3]) < MathTools::EPSILON &&
		Math::abs(data[4] - m->data[4]) < MathTools::EPSILON &&
		Math::abs(data[5] - m->data[5]) < MathTools::EPSILON &&
		Math::abs(data[6] - m->data[6]) < MathTools::EPSILON &&
		Math::abs(data[7] - m->data[7]) < MathTools::EPSILON &&
		Math::abs(data[8] - m->data[8]) < MathTools::EPSILON &&
		Math::abs(data[9] - m->data[9]) < MathTools::EPSILON &&
		Math::abs(data[10] - m->data[10]) < MathTools::EPSILON &&
		Math::abs(data[11] - m->data[11]) < MathTools::EPSILON &&
		Math::abs(data[12] - m->data[12]) < MathTools::EPSILON &&
		Math::abs(data[13] - m->data[13]) < MathTools::EPSILON &&
		Math::abs(data[14] - m->data[14]) < MathTools::EPSILON &&
		Math::abs(data[15] - m->data[15]) < MathTools::EPSILON;
}

array<float, 16>* Matrix4x4::getArray()
{
	return &data;
}

Matrix4x4* Matrix4x4::clone()
{
	return new Matrix4x4(this);
}

Matrix4x4* Matrix4x4::interpolateLinear(Matrix4x4* m1, Matrix4x4* m2, float t, Matrix4x4* dest)
{
	return dest->set(
		(m2->data[0] * t) + ((1.0f - t) * m1->data[0]),
		(m2->data[1] * t) + ((1.0f - t) * m1->data[1]),
		(m2->data[2] * t) + ((1.0f - t) * m1->data[2]),
		(m2->data[3] * t) + ((1.0f - t) * m1->data[3]),
		(m2->data[4] * t) + ((1.0f - t) * m1->data[4]),
		(m2->data[5] * t) + ((1.0f - t) * m1->data[5]),
		(m2->data[6] * t) + ((1.0f - t) * m1->data[6]),
		(m2->data[7] * t) + ((1.0f - t) * m1->data[7]),
		(m2->data[8] * t) + ((1.0f - t) * m1->data[8]),
		(m2->data[9] * t) + ((1.0f - t) * m1->data[9]),
		(m2->data[10] * t) + ((1.0f - t) * m1->data[10]),
		(m2->data[11] * t) + ((1.0f - t) * m1->data[11]),
		(m2->data[12] * t) + ((1.0f - t) * m1->data[12]),
		(m2->data[13] * t) + ((1.0f - t) * m1->data[13]),
		(m2->data[14] * t) + ((1.0f - t) * m1->data[14]),
		(m2->data[15] * t) + ((1.0f - t) * m1->data[15])
	);
}

void Matrix4x4::computeEulerAngles(Vector3* euler)
{
	auto eulerXYZ = euler->getArray();
	auto axis0 = 0;
	auto axis1 = 1;
	auto axis2 = 2;
	auto cy = static_cast< float >(Math::sqrt(data[axis0 + 4 * axis0] * data[axis0 + 4 * axis0] + data[axis1 + 4 * axis0] * data[axis1 + 4 * axis0]));
	if (cy > 16.0f * MathTools::EPSILON) {
		(*eulerXYZ)[0] = static_cast< float >((Math::atan2(data[axis2 + 4 * axis1], data[axis2 + 4 * axis2])));
		(*eulerXYZ)[1] = static_cast< float >((Math::atan2(-data[axis2 + 4 * axis0], cy)));
		(*eulerXYZ)[2] = static_cast< float >((Math::atan2(data[axis1 + 4 * axis0], data[axis0 + 4 * axis0])));
	} else {
		(*eulerXYZ)[0] = static_cast< float >((Math::atan2(-data[axis1 + 4 * axis2], data[axis1 + 4 * axis1])));
		(*eulerXYZ)[1] = static_cast< float >((Math::atan2(-data[axis2 + 4 * axis0], cy)));
		(*eulerXYZ)[2] = 0.0f;
	}
	euler->scale(static_cast< float >((180.0 / Math::PI)));
}



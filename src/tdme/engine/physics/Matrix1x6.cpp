// Generated from /tdme/src/tdme/engine/physics/Matrix1x6.java
#include <tdme/engine/physics/Matrix1x6.h>

#include <algorithm>
#include <array>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/engine/physics/Matrix6x6.h>
#include <tdme/engine/physics/Vector6.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using std::array;
using std::begin;
using std::copy;
using std::end;

using tdme::engine::physics::Matrix1x6;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::Arrays;
using tdme::engine::physics::Matrix6x6;
using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

Matrix1x6::Matrix1x6() 
{
	data.fill(0.0f);
}

void Matrix1x6::setValue(float value0, float value1, float value2, float value3, float value4, float value5)
{
	data[0] = value0;
	data[1] = value1;
	data[2] = value2;
	data[3] = value3;
	data[4] = value4;
	data[5] = value5;
}

void Matrix1x6::setValue(int32_t idx, float value)
{
	data[idx] = value;
}

void Matrix1x6::setValue(int32_t startIdx, Vector3* vector3)
{
	data[startIdx + 0] = vector3->data[0];
	data[startIdx + 1] = vector3->data[1];
	data[startIdx + 2] = vector3->data[2];
}

float Matrix1x6::multiply(Vector6* vector)
{
	auto vector6Array = vector->getArray();
	return data[0] * (*vector6Array)[0] + data[1] * (*vector6Array)[1] + data[2] * (*vector6Array)[2] + data[3] * (*vector6Array)[3] + data[4] * (*vector6Array)[4] + data[5] * (*vector6Array)[5];
}

Matrix1x6* Matrix1x6::multiply(Matrix6x6* matrix6x6, Matrix1x6* dest)
{
	auto matrix6x6Data = matrix6x6->getArray();
	dest->data[0] = data[0] * (*matrix6x6Data)[0 * 6 + 0] + data[1] * (*matrix6x6Data)[1 * 6 + 0] + data[2] * (*matrix6x6Data)[2 * 6 + 0] + data[3] * (*matrix6x6Data)[3 * 6 + 0] + data[4] * (*matrix6x6Data)[4 * 6 + 0] + data[5] * (*matrix6x6Data)[5 * 6 + 0];
	dest->data[1] = data[0] * (*matrix6x6Data)[0 * 6 + 1] + data[1] * (*matrix6x6Data)[1 * 6 + 1] + data[2] * (*matrix6x6Data)[2 * 6 + 1] + data[3] * (*matrix6x6Data)[3 * 6 + 1] + data[4] * (*matrix6x6Data)[4 * 6 + 1] + data[5] * (*matrix6x6Data)[5 * 6 + 1];
	dest->data[2] = data[0] * (*matrix6x6Data)[0 * 6 + 2] + data[1] * (*matrix6x6Data)[1 * 6 + 2] + data[2] * (*matrix6x6Data)[2 * 6 + 2] + data[3] * (*matrix6x6Data)[3 * 6 + 2] + data[4] * (*matrix6x6Data)[4 * 6 + 2] + data[5] * (*matrix6x6Data)[5 * 6 + 2];
	dest->data[3] = data[0] * (*matrix6x6Data)[0 * 6 + 3] + data[1] * (*matrix6x6Data)[1 * 6 + 3] + data[2] * (*matrix6x6Data)[2 * 6 + 3] + data[3] * (*matrix6x6Data)[3 * 6 + 3] + data[4] * (*matrix6x6Data)[4 * 6 + 3] + data[5] * (*matrix6x6Data)[5 * 6 + 3];
	dest->data[4] = data[0] * (*matrix6x6Data)[0 * 6 + 4] + data[1] * (*matrix6x6Data)[1 * 6 + 4] + data[2] * (*matrix6x6Data)[2 * 6 + 4] + data[3] * (*matrix6x6Data)[3 * 6 + 4] + data[4] * (*matrix6x6Data)[4 * 6 + 4] + data[5] * (*matrix6x6Data)[5 * 6 + 4];
	dest->data[5] = data[0] * (*matrix6x6Data)[0 * 6 + 5] + data[1] * (*matrix6x6Data)[1 * 6 + 5] + data[2] * (*matrix6x6Data)[2 * 6 + 5] + data[3] * (*matrix6x6Data)[3 * 6 + 5] + data[4] * (*matrix6x6Data)[4 * 6 + 5] + data[5] * (*matrix6x6Data)[5 * 6 + 5];
	return dest;
}

Vector6* Matrix1x6::getTranspose(Vector6* dest)
{
	copy(begin(data), end(data), begin(dest->data));
	return dest;
}

// Generated from /tdme/src/tdme/engine/physics/Matrix6x6.java
#include <tdme/engine/physics/Matrix6x6.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/engine/physics/Vector6.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::physics::Matrix6x6;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::Arrays;
using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

Matrix6x6::Matrix6x6() 
{
	data.fill(0.0f);
}

void Matrix6x6::fill(float value)
{
	data.fill(value);
}

void Matrix6x6::setValue(int32_t idx, float value)
{
	data[idx] = value;
}

void Matrix6x6::setValue(int32_t startIdx, Vector3* vector3)
{
	data[startIdx + 0] = vector3->data[0];
	data[startIdx + 1] = vector3->data[1];
	data[startIdx + 2] = vector3->data[2];
}

void Matrix6x6::setValue(int32_t i, int32_t j, float value)
{
	data[i * 6 + j] = value;
}

array<float, 36>* Matrix6x6::getArray()
{
	return &data;
}

Vector6* Matrix6x6::multiply(Vector6* vector6, Vector6* dest)
{
	auto vector6Array = vector6->getArray();
	dest->data[0] = data[0 * 6 + 0] * (*vector6Array)[0] + data[0 * 6 + 1] * (*vector6Array)[1] + data[0 * 6 + 2] * (*vector6Array)[2] + data[0 * 6 + 3] * (*vector6Array)[3] + data[0 * 6 + 4] * (*vector6Array)[4] + data[0 * 6 + 5] * (*vector6Array)[5];
	dest->data[1] = data[1 * 6 + 0] * (*vector6Array)[0] + data[1 * 6 + 1] * (*vector6Array)[1] + data[1 * 6 + 2] * (*vector6Array)[2] + data[1 * 6 + 3] * (*vector6Array)[3] + data[1 * 6 + 4] * (*vector6Array)[4] + data[1 * 6 + 5] * (*vector6Array)[5];
	dest->data[2] = data[2 * 6 + 0] * (*vector6Array)[0] + data[2 * 6 + 1] * (*vector6Array)[1] + data[2 * 6 + 2] * (*vector6Array)[2] + data[2 * 6 + 3] * (*vector6Array)[3] + data[2 * 6 + 4] * (*vector6Array)[4] + data[2 * 6 + 5] * (*vector6Array)[5];
	dest->data[3] = data[3 * 6 + 0] * (*vector6Array)[0] + data[3 * 6 + 1] * (*vector6Array)[1] + data[3 * 6 + 2] * (*vector6Array)[2] + data[3 * 6 + 3] * (*vector6Array)[3] + data[3 * 6 + 4] * (*vector6Array)[4] + data[3 * 6 + 5] * (*vector6Array)[5];
	dest->data[4] = data[4 * 6 + 0] * (*vector6Array)[0] + data[4 * 6 + 1] * (*vector6Array)[1] + data[4 * 6 + 2] * (*vector6Array)[2] + data[4 * 6 + 3] * (*vector6Array)[3] + data[4 * 6 + 4] * (*vector6Array)[4] + data[4 * 6 + 5] * (*vector6Array)[5];
	dest->data[5] = data[5 * 6 + 0] * (*vector6Array)[0] + data[5 * 6 + 1] * (*vector6Array)[1] + data[5 * 6 + 2] * (*vector6Array)[2] + data[5 * 6 + 3] * (*vector6Array)[3] + data[5 * 6 + 4] * (*vector6Array)[4] + data[5 * 6 + 5] * (*vector6Array)[5];
	return dest;
}


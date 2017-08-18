// Generated from /tdme/src/tdme/engine/physics/Vector6.java
#include <tdme/engine/physics/Vector6.h>

#include <algorithm>
#include <array>

#include <tdme/math/Vector3.h>
#include <Array.h>

using std::array;
using std::begin;
using std::copy;
using std::end;

using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

Vector6::Vector6() 
{
	data.fill(0.0f);
}


void Vector6::fill(float value)
{
	data.fill(value);
}

Vector6* Vector6::set(Vector6* vector6)
{
	copy(begin(*vector6->getArray()), end(*vector6->getArray()), begin(data));
	return this;
}

void Vector6::setValue(int32_t idx, float value)
{
	data[idx] = value;
}

void Vector6::setValue(int32_t startIdx, Vector3* vector3)
{
	auto vector3XYZ = vector3->getArray();
	data[startIdx + 0] = (*vector3XYZ)[0];
	data[startIdx + 1] = (*vector3XYZ)[1];
	data[startIdx + 2] = (*vector3XYZ)[2];
}

Vector6* Vector6::add(Vector6* vector6)
{
	data[0] += vector6->data[0];
	data[1] += vector6->data[1];
	data[2] += vector6->data[2];
	data[3] += vector6->data[3];
	data[4] += vector6->data[4];
	data[5] += vector6->data[5];
	return this;
}

Vector6* Vector6::sub(Vector6* vector6)
{
	data[0] -= vector6->data[0];
	data[1] -= vector6->data[1];
	data[2] -= vector6->data[2];
	data[3] -= vector6->data[3];
	data[4] -= vector6->data[4];
	data[5] -= vector6->data[5];
	return this;
}

Vector6* Vector6::scale(float value)
{
	data[0] *= value;
	data[1] *= value;
	data[2] *= value;
	data[3] *= value;
	data[4] *= value;
	data[5] *= value;
	return this;
}

array<float, 6>* Vector6::getArray()
{
	return &data;
}

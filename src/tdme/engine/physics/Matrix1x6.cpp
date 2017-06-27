// Generated from /tdme/src/tdme/engine/physics/Matrix1x6.java
#include <tdme/engine/physics/Matrix1x6.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/engine/physics/Matrix6x6.h>
#include <tdme/engine/physics/Vector6.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::physics::Matrix1x6;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::Arrays;
using tdme::engine::physics::Matrix6x6;
using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

Matrix1x6::Matrix1x6(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Matrix1x6::Matrix1x6() 
	: Matrix1x6(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Matrix1x6::init()
{
	data = (new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	}));
}

void Matrix1x6::ctor()
{
	super::ctor();
	init();
}

void Matrix1x6::setValue(float value0, float value1, float value2, float value3, float value4, float value5)
{
	(*this->data)[0] = value0;
	(*this->data)[1] = value1;
	(*this->data)[2] = value2;
	(*this->data)[3] = value3;
	(*this->data)[4] = value4;
	(*this->data)[5] = value5;
}

void Matrix1x6::setValue(int32_t idx, float value)
{
	(*data)[idx] = value;
}

void Matrix1x6::setValue(int32_t startIdx, Vector3* vector3)
{
	System::arraycopy(vector3->getArray(), 0, data, startIdx, 3);
}

float Matrix1x6::multiply(Vector6* vector)
{
	auto vector6Array = vector->getArray();
	return (*data)[0] * (*vector6Array)[0] + (*data)[1] * (*vector6Array)[1] + (*data)[2] * (*vector6Array)[2] + (*data)[3] * (*vector6Array)[3] + (*data)[4] * (*vector6Array)[4] + (*data)[5] * (*vector6Array)[5];
}

Matrix1x6* Matrix1x6::multiply(Matrix6x6* matrix6x6, Matrix1x6* dest)
{
	auto matrix6x6Data = matrix6x6->getArray();
	(*dest->data)[0] = (*data)[0] * (*matrix6x6Data)[0 * 6 + 0] + (*data)[1] * (*matrix6x6Data)[1 * 6 + 0] + (*data)[2] * (*matrix6x6Data)[2 * 6 + 0] + (*data)[3] * (*matrix6x6Data)[3 * 6 + 0] + (*data)[4] * (*matrix6x6Data)[4 * 6 + 0] + (*data)[5] * (*matrix6x6Data)[5 * 6 + 0];
	(*dest->data)[1] = (*data)[0] * (*matrix6x6Data)[0 * 6 + 1] + (*data)[1] * (*matrix6x6Data)[1 * 6 + 1] + (*data)[2] * (*matrix6x6Data)[2 * 6 + 1] + (*data)[3] * (*matrix6x6Data)[3 * 6 + 1] + (*data)[4] * (*matrix6x6Data)[4 * 6 + 1] + (*data)[5] * (*matrix6x6Data)[5 * 6 + 1];
	(*dest->data)[2] = (*data)[0] * (*matrix6x6Data)[0 * 6 + 2] + (*data)[1] * (*matrix6x6Data)[1 * 6 + 2] + (*data)[2] * (*matrix6x6Data)[2 * 6 + 2] + (*data)[3] * (*matrix6x6Data)[3 * 6 + 2] + (*data)[4] * (*matrix6x6Data)[4 * 6 + 2] + (*data)[5] * (*matrix6x6Data)[5 * 6 + 2];
	(*dest->data)[3] = (*data)[0] * (*matrix6x6Data)[0 * 6 + 3] + (*data)[1] * (*matrix6x6Data)[1 * 6 + 3] + (*data)[2] * (*matrix6x6Data)[2 * 6 + 3] + (*data)[3] * (*matrix6x6Data)[3 * 6 + 3] + (*data)[4] * (*matrix6x6Data)[4 * 6 + 3] + (*data)[5] * (*matrix6x6Data)[5 * 6 + 3];
	(*dest->data)[4] = (*data)[0] * (*matrix6x6Data)[0 * 6 + 4] + (*data)[1] * (*matrix6x6Data)[1 * 6 + 4] + (*data)[2] * (*matrix6x6Data)[2 * 6 + 4] + (*data)[3] * (*matrix6x6Data)[3 * 6 + 4] + (*data)[4] * (*matrix6x6Data)[4 * 6 + 4] + (*data)[5] * (*matrix6x6Data)[5 * 6 + 4];
	(*dest->data)[5] = (*data)[0] * (*matrix6x6Data)[0 * 6 + 5] + (*data)[1] * (*matrix6x6Data)[1 * 6 + 5] + (*data)[2] * (*matrix6x6Data)[2 * 6 + 5] + (*data)[3] * (*matrix6x6Data)[3 * 6 + 5] + (*data)[4] * (*matrix6x6Data)[4 * 6 + 5] + (*data)[5] * (*matrix6x6Data)[5 * 6 + 5];
	return dest;
}

Vector6* Matrix1x6::getTranspose(Vector6* dest)
{
	System::arraycopy(data, 0, dest->data, 0, 6);
	return dest;
}

String* Matrix1x6::toString()
{
	return ::java::lang::StringBuilder().append(u"Matrix1x6 ["_j)->append(Arrays::toString(data))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Matrix1x6::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.Matrix1x6", 29);
    return c;
}

java::lang::Class* Matrix1x6::getClass0()
{
	return class_();
}


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

Matrix6x6::Matrix6x6(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Matrix6x6::Matrix6x6() 
	: Matrix6x6(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Matrix6x6::init()
{
	data = (new floatArray({
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	}));
}

void Matrix6x6::ctor()
{
	super::ctor();
	init();
}

void Matrix6x6::fill(float value)
{
	Arrays::fill(data, value);
}

void Matrix6x6::setValue(int32_t idx, float value)
{
	(*data)[idx] = value;
}

void Matrix6x6::setValue(int32_t startIdx, Vector3* vector3)
{
	System::arraycopy(vector3->getArray(), 0, data, startIdx, 3);
}

void Matrix6x6::setValue(int32_t i, int32_t j, float value)
{
	(*data)[i * 6 + j] = value;
}

floatArray* Matrix6x6::getArray()
{
	return data;
}

Vector6* Matrix6x6::multiply(Vector6* vector6, Vector6* dest)
{
	auto vector6Array = vector6->getArray();
	(*dest->data)[0] = (*data)[0 * 6 + 0] * (*vector6Array)[0] + (*data)[0 * 6 + 1] * (*vector6Array)[1] + (*data)[0 * 6 + 2] * (*vector6Array)[2] + (*data)[0 * 6 + 3] * (*vector6Array)[3] + (*data)[0 * 6 + 4] * (*vector6Array)[4] + (*data)[0 * 6 + 5] * (*vector6Array)[5];
	(*dest->data)[1] = (*data)[1 * 6 + 0] * (*vector6Array)[0] + (*data)[1 * 6 + 1] * (*vector6Array)[1] + (*data)[1 * 6 + 2] * (*vector6Array)[2] + (*data)[1 * 6 + 3] * (*vector6Array)[3] + (*data)[1 * 6 + 4] * (*vector6Array)[4] + (*data)[1 * 6 + 5] * (*vector6Array)[5];
	(*dest->data)[2] = (*data)[2 * 6 + 0] * (*vector6Array)[0] + (*data)[2 * 6 + 1] * (*vector6Array)[1] + (*data)[2 * 6 + 2] * (*vector6Array)[2] + (*data)[2 * 6 + 3] * (*vector6Array)[3] + (*data)[2 * 6 + 4] * (*vector6Array)[4] + (*data)[2 * 6 + 5] * (*vector6Array)[5];
	(*dest->data)[3] = (*data)[3 * 6 + 0] * (*vector6Array)[0] + (*data)[3 * 6 + 1] * (*vector6Array)[1] + (*data)[3 * 6 + 2] * (*vector6Array)[2] + (*data)[3 * 6 + 3] * (*vector6Array)[3] + (*data)[3 * 6 + 4] * (*vector6Array)[4] + (*data)[3 * 6 + 5] * (*vector6Array)[5];
	(*dest->data)[4] = (*data)[4 * 6 + 0] * (*vector6Array)[0] + (*data)[4 * 6 + 1] * (*vector6Array)[1] + (*data)[4 * 6 + 2] * (*vector6Array)[2] + (*data)[4 * 6 + 3] * (*vector6Array)[3] + (*data)[4 * 6 + 4] * (*vector6Array)[4] + (*data)[4 * 6 + 5] * (*vector6Array)[5];
	(*dest->data)[5] = (*data)[5 * 6 + 0] * (*vector6Array)[0] + (*data)[5 * 6 + 1] * (*vector6Array)[1] + (*data)[5 * 6 + 2] * (*vector6Array)[2] + (*data)[5 * 6 + 3] * (*vector6Array)[3] + (*data)[5 * 6 + 4] * (*vector6Array)[4] + (*data)[5 * 6 + 5] * (*vector6Array)[5];
	return dest;
}

String* Matrix6x6::toString()
{
	return ::java::lang::StringBuilder().append(u"Matrix6x6 [data="_j)->append(Arrays::toString(data))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Matrix6x6::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.Matrix6x6", 29);
    return c;
}

java::lang::Class* Matrix6x6::getClass0()
{
	return class_();
}


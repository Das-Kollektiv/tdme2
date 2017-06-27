// Generated from /tdme/src/tdme/engine/physics/Vector6.java
#include <tdme/engine/physics/Vector6.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/math/Vector3.h>
#include <Array.h>

using tdme::engine::physics::Vector6;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::Arrays;
using tdme::math::Vector3;

Vector6::Vector6(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Vector6::Vector6() 
	: Vector6(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Vector6::init()
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

void Vector6::ctor()
{
	super::ctor();
	init();
}

void Vector6::fill(float value)
{
	Arrays::fill(data, value);
}

Vector6* Vector6::set(Vector6* vector6)
{
	System::arraycopy(vector6->getArray(), 0, data, 0, data->length);
	return this;
}

void Vector6::setValue(int32_t idx, float value)
{
	(*data)[idx] = value;
}

void Vector6::setValue(int32_t startIdx, Vector3* vector3)
{
	System::arraycopy(vector3->getArray(), 0, data, startIdx, 3);
}

Vector6* Vector6::add(Vector6* vector6)
{
	(*data)[0] += (*vector6->data)[0];
	(*data)[1] += (*vector6->data)[1];
	(*data)[2] += (*vector6->data)[2];
	(*data)[3] += (*vector6->data)[3];
	(*data)[4] += (*vector6->data)[4];
	(*data)[5] += (*vector6->data)[5];
	return this;
}

Vector6* Vector6::sub(Vector6* vector6)
{
	(*data)[0] -= (*vector6->data)[0];
	(*data)[1] -= (*vector6->data)[1];
	(*data)[2] -= (*vector6->data)[2];
	(*data)[3] -= (*vector6->data)[3];
	(*data)[4] -= (*vector6->data)[4];
	(*data)[5] -= (*vector6->data)[5];
	return this;
}

Vector6* Vector6::scale(float value)
{
	(*data)[0] *= value;
	(*data)[1] *= value;
	(*data)[2] *= value;
	(*data)[3] *= value;
	(*data)[4] *= value;
	(*data)[5] *= value;
	return this;
}

floatArray* Vector6::getArray()
{
	return data;
}

String* Vector6::toString()
{
	return ::java::lang::StringBuilder().append(u"Vector6 [data="_j)->append(Arrays::toString(data))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Vector6::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.Vector6", 27);
    return c;
}

java::lang::Class* Vector6::getClass0()
{
	return class_();
}


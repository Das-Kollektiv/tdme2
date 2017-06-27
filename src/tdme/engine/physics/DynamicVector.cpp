// Generated from /tdme/src/tdme/engine/physics/DynamicVector.java
#include <tdme/engine/physics/DynamicVector.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <Array.h>

using tdme::engine::physics::DynamicVector;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;

DynamicVector::DynamicVector(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

DynamicVector::DynamicVector(int32_t size) 
	: DynamicVector(*static_cast< ::default_init_tag* >(0))
{
	ctor(size);
}

void DynamicVector::ctor(int32_t size)
{
	super::ctor();
	data = new floatArray(size);
}

void DynamicVector::setSize(int32_t size)
{
	data = new floatArray(size);
}

void DynamicVector::setValue(int32_t idx, float value)
{
	(*data)[idx] = value;
}

float DynamicVector::getValue(int32_t idx)
{
	return (*data)[idx];
}

void DynamicVector::scale(float value, DynamicVector* dest)
{
	if (data->length != dest->data->length) {
		dest->setSize(data->length);
	}
	for (auto i = 0; i < data->length; i++) {
		(*dest->data)[i] = (*data)[i] * value;
	}
}

String* DynamicVector::toString()
{
	return ::java::lang::StringBuilder().append(u"DynamicVector [data="_j)->append(Arrays::toString(data))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DynamicVector::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.DynamicVector", 33);
    return c;
}

java::lang::Class* DynamicVector::getClass0()
{
	return class_();
}


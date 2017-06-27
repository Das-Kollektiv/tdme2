// Generated from /tdme/src/tdme/engine/model/Color4Base.java
#include <tdme/engine/model/Color4Base.h>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/math/MathTools.h>
#include <Array.h>

using tdme::engine::model::Color4Base;
using java::lang::Math;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::Arrays;
using tdme::math::MathTools;

Color4Base::Color4Base(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Color4Base::Color4Base() 
	: Color4Base(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Color4Base::Color4Base(Color4Base* color) 
	: Color4Base(*static_cast< ::default_init_tag* >(0))
{
	ctor(color);
}

Color4Base::Color4Base(floatArray* color) 
	: Color4Base(*static_cast< ::default_init_tag* >(0))
{
	ctor(color);
}

Color4Base::Color4Base(float r, float g, float b, float a) 
	: Color4Base(*static_cast< ::default_init_tag* >(0))
{
	ctor(r,g,b,a);
}

void Color4Base::ctor()
{
	super::ctor();
	this->data = new floatArray(4);
}

void Color4Base::ctor(Color4Base* color)
{
	super::ctor();
	this->data = new floatArray(4);
	System::arraycopy(color->data, 0, data, 0, Math::min(color->data->length, data->length));
}

void Color4Base::ctor(floatArray* color)
{
	super::ctor();
	this->data = new floatArray(4);
	System::arraycopy(color, 0, this->data, 0, Math::min(color->length, data->length));
}

void Color4Base::ctor(float r, float g, float b, float a)
{
	super::ctor();
	data = new floatArray(4);
	(*data)[0] = r;
	(*data)[1] = g;
	(*data)[2] = b;
	(*data)[3] = a;
}

void Color4Base::set(floatArray* color)
{
	System::arraycopy(color, 0, this->data, 0, Math::min(color->length, data->length));
}

void Color4Base::set(float r, float g, float b, float a)
{
	(*data)[0] = r;
	(*data)[1] = g;
	(*data)[2] = b;
	(*data)[3] = a;
}

void Color4Base::set(Color4Base* color)
{
	System::arraycopy(color->data, 0, data, 0, 4);
}

void Color4Base::add(float r, float g, float b, float a)
{
	(*data)[0] += r;
	(*data)[1] += g;
	(*data)[2] += b;
	(*data)[3] += a;
}

float Color4Base::getRed()
{
	return (*data)[0];
}

void Color4Base::setRed(float red)
{
	(*data)[0] = red;
}

float Color4Base::getGreen()
{
	return (*data)[1];
}

void Color4Base::setGreen(float green)
{
	(*data)[1] = green;
}

float Color4Base::getBlue()
{
	return (*data)[2];
}

void Color4Base::setBlue(float blue)
{
	(*data)[2] = blue;
}

float Color4Base::getAlpha()
{
	return (*data)[3];
}

void Color4Base::setAlpha(float alpha)
{
	(*data)[3] = alpha;
}

floatArray* Color4Base::getArray()
{
	return data;
}

bool Color4Base::equals(Color4Base* c)
{
	return (this == c) || (Math::abs((*data)[0] - (*c->data)[0]) < MathTools::EPSILON && Math::abs((*data)[1] - (*c->data)[1]) < MathTools::EPSILON && Math::abs((*data)[2] - (*c->data)[2]) < MathTools::EPSILON && Math::abs((*data)[3] - (*c->data)[3]) < MathTools::EPSILON);
}

String* Color4Base::toString()
{
	return ::java::lang::StringBuilder().append(u"Color4 [data="_j)->append(Arrays::toString(data))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Color4Base::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.Color4Base", 28);
    return c;
}

bool Color4Base::equals(Object* arg0)
{
	return super::equals(arg0);
}

java::lang::Class* Color4Base::getClass0()
{
	return class_();
}


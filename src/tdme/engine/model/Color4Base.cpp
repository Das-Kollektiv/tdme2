// Generated from /tdme/src/tdme/engine/model/Color4Base.java
#include <tdme/engine/model/Color4Base.h>

#include <algorithm>
#include <array>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/math/MathTools.h>
#include <Array.h>

using std::array;
using std::begin;
using std::copy;
using std::end;

using tdme::engine::model::Color4Base;
using java::lang::Math;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::util::Arrays;
using tdme::math::MathTools;

Color4Base::Color4Base() 
{
	data[0] = 0.0f;
	data[1] = 0.0f;
	data[2] = 0.0f;
	data[3] = 1.0f;
}

Color4Base::Color4Base(Color4Base* color) 
{
	data = color->data;
}

Color4Base::Color4Base(array<float, 4>* color)
{
	this->data = *color;
}

Color4Base::Color4Base(floatArray* color) 
{
	this->data[0] = (*color)[0];
	this->data[1] = (*color)[1];
	this->data[2] = (*color)[2];
	this->data[3] = (*color)[3];
}

Color4Base::Color4Base(float r, float g, float b, float a) 
{
	data[0] = r;
	data[1] = g;
	data[2] = b;
	data[3] = a;
}

void Color4Base::set(array<float, 4>* color)
{
	this->data = *color;
}

void Color4Base::set(floatArray* color)
{
	this->data[0] = (*color)[0];
	this->data[1] = (*color)[1];
	this->data[2] = (*color)[2];
	this->data[3] = (*color)[3];
}

void Color4Base::set(float r, float g, float b, float a)
{
	data[0] = r;
	data[1] = g;
	data[2] = b;
	data[3] = a;
}

void Color4Base::set(Color4Base* color)
{
	data = color->data;
}

void Color4Base::add(float r, float g, float b, float a)
{
	data[0] += r;
	data[1] += g;
	data[2] += b;
	data[3] += a;
}

float Color4Base::getRed()
{
	return data[0];
}

void Color4Base::setRed(float red)
{
	data[0] = red;
}

float Color4Base::getGreen()
{
	return data[1];
}

void Color4Base::setGreen(float green)
{
	data[1] = green;
}

float Color4Base::getBlue()
{
	return data[2];
}

void Color4Base::setBlue(float blue)
{
	data[2] = blue;
}

float Color4Base::getAlpha()
{
	return data[3];
}

void Color4Base::setAlpha(float alpha)
{
	data[3] = alpha;
}

array<float, 4>* Color4Base::getArray()
{
	return &data;
}

bool Color4Base::equals(Color4Base* c)
{
	return (this == c) || (
		Math::abs(data[0] - c->data[0]) < MathTools::EPSILON &&
		Math::abs(data[1] - c->data[1]) < MathTools::EPSILON &&
		Math::abs(data[2] - c->data[2]) < MathTools::EPSILON &&
		Math::abs(data[3] - c->data[3]) < MathTools::EPSILON
	);
}

// Generated from /tdme/src/tdme/engine/model/TextureCoordinate.java
#include <tdme/engine/model/TextureCoordinate.h>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <tdme/math/MathTools.h>
#include <Array.h>

using tdme::engine::model::TextureCoordinate;
using java::lang::Math;
using java::lang::String;
using java::lang::System;
using java::util::Arrays;
using tdme::math::MathTools;

TextureCoordinate::TextureCoordinate(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TextureCoordinate::TextureCoordinate(TextureCoordinate* textureCoordinate) 
	: TextureCoordinate(*static_cast< ::default_init_tag* >(0))
{
	ctor(textureCoordinate);
}

TextureCoordinate::TextureCoordinate(floatArray* uv) 
	: TextureCoordinate(*static_cast< ::default_init_tag* >(0))
{
	ctor(uv);
}

TextureCoordinate::TextureCoordinate(float u, float v) 
	: TextureCoordinate(*static_cast< ::default_init_tag* >(0))
{
	ctor(u,v);
}

void TextureCoordinate::ctor(TextureCoordinate* textureCoordinate)
{
	super::ctor();
	data = new floatArray(2);
	(*data)[0] = (*textureCoordinate->data)[0];
	(*data)[1] = (*textureCoordinate->data)[1];
}

void TextureCoordinate::ctor(floatArray* uv)
{
	super::ctor();
	data = new floatArray(2);
	System::arraycopy(uv, 0, data, 0, Math::min(uv->length, data->length));
}

void TextureCoordinate::ctor(float u, float v)
{
	super::ctor();
	data = new floatArray(2);
	(*data)[0] = u;
	(*data)[1] = 1.0f - v;
}

float TextureCoordinate::getU()
{
	return (*data)[0];
}

float TextureCoordinate::getV()
{
	return (*data)[1];
}

floatArray* TextureCoordinate::getArray()
{
	return data;
}

TextureCoordinate* TextureCoordinate::clone()
{
	return new TextureCoordinate((*data)[0], 1.0f - (*data)[1]);
}

bool TextureCoordinate::equals(TextureCoordinate* textureCoordinate)
{
	return (this == textureCoordinate) || (Math::abs((*data)[0] - (*textureCoordinate->data)[0]) < MathTools::EPSILON && Math::abs((*data)[1] - (*textureCoordinate->data)[1]) < MathTools::EPSILON);
}

String* TextureCoordinate::toString()
{
	return Arrays::toString(data);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TextureCoordinate::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.model.TextureCoordinate", 35);
    return c;
}

bool TextureCoordinate::equals(Object* arg0)
{
	return super::equals(arg0);
}

java::lang::Class* TextureCoordinate::getClass0()
{
	return class_();
}


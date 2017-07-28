// Generated from /tdme/src/tdme/engine/model/TextureCoordinate.java
#include <tdme/engine/model/TextureCoordinate.h>

#include <array>

#include <java/lang/Math.h>
#include <java/lang/System.h>
#include <tdme/math/MathTools.h>
#include <Array.h>

using std::array;

using tdme::engine::model::TextureCoordinate;
using java::lang::Math;
using java::lang::String;
using java::lang::System;
using java::util::Arrays;
using tdme::math::MathTools;

TextureCoordinate::TextureCoordinate()
{
	data.fill(0.0f);
}

TextureCoordinate::TextureCoordinate(TextureCoordinate* textureCoordinate) 
{
	data = textureCoordinate->data;
}

TextureCoordinate::TextureCoordinate(floatArray* uv) 
{
	data[0] = (*uv)[0];
	data[1] = (*uv)[1];
}

TextureCoordinate::TextureCoordinate(float u, float v) 
{
	data[0] = u;
	data[1] = 1.0f - v;
}

float TextureCoordinate::getU()
{
	return data[0];
}

float TextureCoordinate::getV()
{
	return data[1];
}

array<float, 2>* TextureCoordinate::getArray()
{
	return &data;
}

TextureCoordinate* TextureCoordinate::clone()
{
	return new TextureCoordinate(data[0], 1.0f - data[1]);
}

bool TextureCoordinate::equals(TextureCoordinate* textureCoordinate)
{
	return
		this == textureCoordinate ||
		(
			Math::abs(data[0] - textureCoordinate->data[0]) < MathTools::EPSILON &&
			Math::abs(data[1] - textureCoordinate->data[1]) < MathTools::EPSILON
		);
}


#include <tdme/engine/model/TextureCoordinate.h>

#include <array>

#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>

using std::array;

using tdme::engine::model::TextureCoordinate;
using tdme::math::Math;
using tdme::math::MathTools;

TextureCoordinate::TextureCoordinate()
{
	data.fill(0.0f);
}

TextureCoordinate::TextureCoordinate(TextureCoordinate* textureCoordinate) 
{
	data = textureCoordinate->data;
}

TextureCoordinate::TextureCoordinate(array<float, 2>* uv)
{
	data = *uv;
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

array<float, 2>& TextureCoordinate::getArray() const
{
	return (array<float, 2>&)data;
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


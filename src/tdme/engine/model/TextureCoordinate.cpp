#include <tdme/engine/model/TextureCoordinate.h>

#include <array>

#include <tdme/math/Math.h>

using std::array;

using tdme::engine::model::TextureCoordinate;
using tdme::math::Math;

TextureCoordinate::TextureCoordinate()
{
	data.fill(0.0f);
}

TextureCoordinate::TextureCoordinate(const TextureCoordinate& textureCoordinate)
{
	data = textureCoordinate.data;
}

TextureCoordinate::TextureCoordinate(const array<float, 2>& uv)
{
	data = uv;
}

TextureCoordinate::TextureCoordinate(float u, float v) 
{
	data[0] = u;
	data[1] = 1.0f - v;
}

float TextureCoordinate::getU() const
{
	return data[0];
}

float TextureCoordinate::getV() const
{
	return data[1];
}

TextureCoordinate& TextureCoordinate::set(const TextureCoordinate& textureCoordinate) {
	data = textureCoordinate.data;
	return *this;
}

TextureCoordinate& TextureCoordinate::set(const array<float, 2>& uv) {
	data = uv;
	return *this;
}

TextureCoordinate& TextureCoordinate::set(float u, float v) {
	data[0] = u;
	data[1] = 1.0f - v;
	return *this;
}

array<float, 2>& TextureCoordinate::getArray() const
{
	return (array<float, 2>&)data;
}

TextureCoordinate TextureCoordinate::clone()
{
	return TextureCoordinate(data[0], 1.0f - data[1]);
}

bool TextureCoordinate::equals(const TextureCoordinate& textureCoordinate) const
{
	return
		this == &textureCoordinate ||
		(
			Math::abs(data[0] - textureCoordinate.data[0]) < Math::EPSILON &&
			Math::abs(data[1] - textureCoordinate.data[1]) < Math::EPSILON
		);
}


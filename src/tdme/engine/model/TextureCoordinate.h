#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/math/Math.h>

using std::array;

using tdme::math::Math;

/**
 * Class representing texture UV coordinates data
 * @author andreas.drewke
 */
class tdme::engine::model::TextureCoordinate final
{
private:
	array<float, 2> data;
public:
	/**
	 * Public constructor
	 */
	inline TextureCoordinate() {
		data.fill(0.0f);
	}

	/**
	 * Public constructor
	 * @param textureCoordinate texture coordinate
	 */
	inline TextureCoordinate(const TextureCoordinate& textureCoordinate) {
		data = textureCoordinate.data;
	}

	/**
	 * Public constructor
	 * @param uv texture coordinate
	 */
	inline TextureCoordinate(const array<float, 2>& uv) {
		data = uv;
	}

	/**
	 * Public constructor
	 * @param u u
	 * @param v v
	 */
	inline TextureCoordinate(float u, float v) {
		data[0] = u;
		data[1] = 1.0f - v;
	}

	/**
	 * @return U
	 */
	inline float getU() const {
		return data[0];
	}

	/**
	 * @return V
	 */
	inline float getV() const {
		return data[1];
	}

	/**
	 * Set texture coordinate
	 * @param textureCoordinate texture coordinate
	 */
	inline TextureCoordinate& set(const TextureCoordinate& textureCoordinate) {
		data = textureCoordinate.data;
		return *this;
	}

	/**
	 * Set texture coordinate
	 * @param uv texture coordinate
	 */
	inline TextureCoordinate& set(const array<float, 2>& uv) {
		data = uv;
		return *this;
	}

	/**
	 * Set texture coordinate
	 * @param u u
	 * @param v v
	 */
	inline TextureCoordinate& set(float u, float v) {
		data[0] = u;
		data[1] = 1.0f - v;
		return *this;
	}

	/**
	 * @return texture data as array
	 */
	inline array<float, 2>& getArray() const {
		return (array<float, 2>&)data;
	}

	/**
	 * Clones the texture coordinate
	 * @return new texture coordinate
	 */
	inline TextureCoordinate clone() {
		return TextureCoordinate(data[0], 1.0f - data[1]);
	}

	/**
	 * Compares this texture coordinate with given texture coordinate
	 * @return equality
	 */
	inline bool equals(const TextureCoordinate& textureCoordinate) const {
		return
			this == &textureCoordinate ||
			(
				Math::abs(data[0] - textureCoordinate.data[0]) < Math::EPSILON &&
				Math::abs(data[1] - textureCoordinate.data[1]) < Math::EPSILON
			);
	}

};

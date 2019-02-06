
#pragma once

#include <array>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

using std::array;

/** 
 * Class representing texture UV coordinates data
 * @author andreas.drewke
 * @version $Id$
 */
class tdme::engine::model::TextureCoordinate final
{
private:
	array<float, 2> data {  };
public:
	/** 
	 * @return U
	 */
	float getU() const;

	/** 
	 * @return V
	 */
	float getV() const;

	/**
	 * Set texture coordinate
	 * @param textureCoordinate texture coordinate
	 */
	TextureCoordinate& set(const TextureCoordinate& textureCoordinate);

	/**
	 * Set texture coordinate
	 * @param uv texture coordinate
	 */
	TextureCoordinate& set(const array<float, 2>& uv);

	/**
	 * Set texture coordinate
	 * @param u u
	 * @param v v
	 */
	TextureCoordinate& set(float u, float v);

	/** 
	 * @return texture data as array
	 */
	array<float, 2>& getArray() const;

	/** 
	 * Clones the texture coordinate
	 * @return new texture coordinate
	 */
	TextureCoordinate clone();

	/** 
	 * Compares this texture coordinate with given texture coordinate
	 * @return equality
	 */
	bool equals(const TextureCoordinate& textureCoordinate) const;

	/**
	 * Public constructor
	 */
	TextureCoordinate();

	/**
	 * Public constructor
	 * @param textureCoordinate texture coordinate
	 */
	TextureCoordinate(const TextureCoordinate& textureCoordinate);

	/**
	 * Public constructor
	 * @param uv texture coordinate
	 */
	TextureCoordinate(const array<float, 2>& uv);

	/**
	 * Public constructor
	 * @param u u
	 * @param v v
	 */
	TextureCoordinate(float u, float v);
};

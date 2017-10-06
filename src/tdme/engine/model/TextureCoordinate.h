
#pragma once

#include <array>

#include <fwd-tdme.h>
#include <tdme/engine/model/fwd-tdme.h>

using std::array;

/** 
 * Class representing a UV data
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
	 * @param texture coordinate
	 */
	TextureCoordinate(const TextureCoordinate& textureCoordinate);

	/**
	 * Public constructor
	 * @param texture coordinate
	 */
	TextureCoordinate(const array<float, 2>& uv);

	/**
	 * Public constructor
	 * @param u
	 * @param v
	 */
	TextureCoordinate(float u, float v);
};

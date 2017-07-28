// Generated from /tdme/src/tdme/engine/model/TextureCoordinate.java

#pragma once

#include <array>

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
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
	float getU();

	/** 
	 * @return V
	 */
	float getV();

	/** 
	 * @return texture data as array
	 */
	array<float, 2>* getArray();

	/** 
	 * Clones the texture coordinate
	 * @return new texture coordinate
	 */
	TextureCoordinate* clone();

	/** 
	 * Compares this texture coordinate with given texture coordinate
	 * @return equality
	 */
	bool equals(TextureCoordinate* textureCoordinate);

	/**
	 * Public constructor
	 */
	TextureCoordinate();

	/**
	 * Public constructor
	 * @param texture coordinate
	 */
	TextureCoordinate(TextureCoordinate* textureCoordinate);

	/**
	 * Public constructor
	 * @param texture coordinate
	 */
	TextureCoordinate(floatArray* uv);

	/**
	 * Public constructor
	 * @param u
	 * @param v
	 */
	TextureCoordinate(float u, float v);
};

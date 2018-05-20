
#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>

using std::string;

using tdme::utils::ByteBuffer;

/** 
 * Texture
 * @version $Id$
 * @author Andreas Drewke
 */
class tdme::engine::fileio::textures::Texture
{
public:
	/**
	 * Public constructor
	 * @param id
	 * @param depth
	 * @param width
	 * @param height
	 * @param texture width
	 * @param texture height
	 * @param texture data
	 */
	Texture(
		const string& id,
		int32_t depth,
		int32_t width,
		int32_t height,
		int32_t textureWidth,
		int32_t textureHeight,
		ByteBuffer* textureData
	);

	/**
	 * Destructor
	 */
	~Texture();

	/** 
	 * @return id
	 */
	const string& getId();

	/** 
	 * @return depth in bits per pixel
	 */
	int32_t getDepth();

	/** 
	 * @return image width
	 */
	int32_t getWidth();

	/** 
	 * @return image height
	 */
	int32_t getHeight();

	/** 
	 * @return texture height
	 */
	int32_t getTextureHeight();

	/** 
	 * @return texture width
	 */
	int32_t getTextureWidth();

	/** 
	 * @return texture data wrapped in a byte buffer
	 */
	ByteBuffer* getTextureData();

private:
	string id;
	int32_t depth;
	int32_t width;
	int32_t height;
	int32_t textureHeight;
	int32_t textureWidth;
	ByteBuffer* textureData;
};

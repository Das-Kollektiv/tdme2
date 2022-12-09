#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/utilities/ByteBuffer.h>

using std::vector;

using tdme::utilities::ByteBuffer;

/**
 * BZ7 texture reader class
 * @author Andreas Drewke
 */
class tdme::engine::fileio::textures::BZ7TextureReader final
{
	friend class tdme::engine::Texture;

public:
	/**
	 * Read BZ7 from memory into texture byte buffer
	 * @param width width
	 * @param height height
	 * @param bytesPerPixel bytes per pixel
	 * @param bz7Data bz7 vector data to read PNG from
	 * @param textureByteBuffer texture byte buffer
	 * @return success
	 */
	static bool read(int width, int height, int bytesPerPixel, const vector<uint8_t>& bz7Data, ByteBuffer& textureByteBuffer);

};

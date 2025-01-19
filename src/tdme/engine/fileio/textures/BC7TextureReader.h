#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/utilities/ByteBuffer.h>

using std::vector;

using tdme::utilities::ByteBuffer;

/**
 * BC7 texture reader class
 * @author Andreas Drewke
 */
class tdme::engine::fileio::textures::BC7TextureReader final
{
	friend class tdme::engine::Texture;

public:
	/**
	 * Read BC7 from memory into texture byte buffer
	 * @param width width
	 * @param height height
	 * @param bytesPerPixel bytes per pixel
	 * @param bc7Data BC7 vector data to read BC7 from
	 * @param textureByteBuffer texture byte buffer
	 * @returns success
	 */
	static bool read(int width, int height, int bytesPerPixel, const vector<uint8_t>& bc7Data, ByteBuffer& textureByteBuffer);

};

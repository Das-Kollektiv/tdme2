#pragma once

#include <ext/libpng/png.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/utilities/ByteBuffer.h>

using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::utilities::ByteBuffer;

/**
 * BZ7 texture writer class
 * @author Andreas Drewke
 */
class tdme::engine::fileio::textures::BZ7TextureWriter final
{
	friend class Texture;

public:

	/**
	 * Writes a texture to BZ7 using a data vector
	 * @param width width
	 * @param height height
	 * @param bytesPerPixel bytes per pixel
	 * @param textureByteBuffer texture RGB byte buffer
	 * @param bz7Data BZ7 data
	 * @return success
	 */
	static bool write(int width, int height, int bytesPerPixel, const ByteBuffer& textureByteBuffer, vector<uint8_t>& bz7Data);

};

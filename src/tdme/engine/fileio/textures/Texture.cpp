#include <tdme/engine/fileio/textures/Texture.h>

#include <tdme/utils/ByteBuffer.h>

using tdme::engine::fileio::textures::Texture;

using tdme::utils::ByteBuffer;

Texture::~Texture() {
	delete textureData;
}


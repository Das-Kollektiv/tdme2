#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>

#include <tdme/utilities/ByteBuffer.h>

using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::TextureReader;

using tdme::utilities::ByteBuffer;

ByteBuffer Texture::getUncompressedTextureData() {
	auto textureSize = textureWidth * textureHeight * (depth / 8);
	textureData.clear();
	textureData.put(textureData.getBuffer(), textureSize);
	return textureData;
}

void Texture::setTextureData(TextureFormat format, const ByteBuffer& textureData) {
	auto textureSize = textureWidth * textureHeight * (depth / 8);
	this->textureData.clear();
	this->textureData.put(textureData.getBuffer(), textureSize);
}

void Texture::onDelete() {
	TextureReader::removeFromCache(this);
}

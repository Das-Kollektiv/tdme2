#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/TextureReader.h>

#include <tdme/utilities/ByteBuffer.h>

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;

using tdme::utilities::ByteBuffer;

ByteBuffer Texture::getRGBTextureData() {
	auto rgbTextureSize = textureWidth * textureHeight * (getRGBDepthBitsPerPixel() / 8);
	auto rgbTextureData = ByteBuffer(rgbTextureSize);
	rgbTextureData.put(this->textureData.getBuffer(), rgbTextureSize);
	return rgbTextureData;
}

void Texture::setTextureData(TextureFormat format, const ByteBuffer& textureData) {
	auto textureSize = textureWidth * textureHeight * (getRGBDepthBitsPerPixel() / 8);
	this->textureData.clear();
	this->textureData.put(textureData.getBuffer(), textureSize);
}

void Texture::onDelete() {
	TextureReader::removeFromCache(this);
}

#include <tdme/engine/fileio/textures/Texture.h>

#include <string>

using std::wstring;
using std::to_wstring;

using tdme::engine::fileio::textures::Texture;

Texture::Texture(
	const wstring& id,
	int32_t depth,
	int32_t width, int32_t height,
	int32_t textureWidth, int32_t textureHeight,
	ByteBuffer* textureData)
	:
	id(id),
	depth(depth),
	width(width),
	height(height),
	textureWidth(textureWidth),
	textureHeight(textureHeight),
	textureData(textureData) {
	//
}

Texture::~Texture() {
	delete textureData;
}

const wstring& Texture::getId() {
	return id;
}

int32_t Texture::getDepth() {
	return depth;
}

int32_t Texture::getWidth() {
	return width;
}

int32_t Texture::getHeight() {
	return height;
}

int32_t Texture::getTextureHeight() {
	return textureHeight;
}

int32_t Texture::getTextureWidth() {
	return textureWidth;
}

ByteBuffer* Texture::getTextureData() {
	return textureData;
}

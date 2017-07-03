// Generated from /tdme/src/tdme/engine/fileio/textures/Texture.java
#include <tdme/engine/fileio/textures/Texture.h>

using tdme::engine::fileio::textures::Texture;
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Texture::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.textures.Texture", 35);
    return c;
}

Texture::Texture(
	String* id,
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

String* Texture::getId() {
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

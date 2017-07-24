// Generated from /tdme/src/tdme/engine/fileio/textures/Texture.java
#include <tdme/engine/fileio/textures/Texture.h>

#include <java/lang/String.h>

#include <string>

using std::wstring;
using std::to_wstring;

using java::lang::String;

using tdme::engine::fileio::textures::Texture;

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Texture::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.textures.Texture", 35);
    return c;
}

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

String* Texture::toString() {
	return new String(
		wstring(
			L"Material["
			L"id=" + id + L", " +
			L"depth=" + to_wstring(depth) + L", " +
			L"width=" + to_wstring(width) + L", " +
			L"height=" + to_wstring(height) + L", " +
			L"textureHeight=" + to_wstring(textureHeight) + L", " +
			L"textureWidth=" + to_wstring(textureWidth) + L", " +
			L"textureData=" + (textureData != nullptr?L"yes":L"no") +
			L"]"
		)
	);
}

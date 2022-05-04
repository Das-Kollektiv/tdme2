#include <tdme/utilities/TextureAtlas.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

using tdme::utilities::TextureAtlas;

using std::string;
using std::to_string;

using tdme::engine::fileio::textures::Texture;
using tdme::math::Math;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;

TextureAtlas::TextureAtlas(const string& id): atlasTextureId(id) {
}

TextureAtlas::~TextureAtlas() {
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
		atlasTexture = nullptr;
	}
}

int TextureAtlas::addTexture(Texture* texture) {
	Console::println("TextureAtlas::addTexture(): texture added to atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
	// check if texture had been added
	{
		auto textureIdx = getTextureIdx(texture);
		if (textureIdx != TEXTURE_IDX_NONE) {
			textureReferenceCounter[texture]++;
			return textureIdx;
		}
	}
	// nope, add it
	auto textureIdx = -1;
	if (freeTextureIds.empty() == false) {
		textureIdx = freeTextureIds[0];
		freeTextureIds.erase(freeTextureIds.begin() + 0);
	} else {
		textureIdx = textureToAtlasTextureIdxMapping.size();
	}
	//
	texture->acquireReference();
	textureToAtlasTextureIdxMapping[texture] = textureIdx;
	atlasTextureIdxToTextureMapping[textureIdx] = texture;
	textureReferenceCounter[texture]++;
	//
	needsUpdate = true;
	//
	return textureIdx;
}

void TextureAtlas::removeTexture(Texture* texture) {
	Console::println("TextureAtlas::removeTexture(): texture removed from atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
	auto textureIdx = getTextureIdx(texture);
	if (textureIdx == TEXTURE_IDX_NONE) {
		Console::println("TextureAtlas::removeTexture(): texture was not yet added to atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
		return;
	}
	textureReferenceCounter[texture]--;
	if (textureReferenceCounter[texture] == 0) {
		textureToAtlasTextureIdxMapping.erase(texture);
		atlasTextureIdxToTextureMapping.erase(textureIdx);
	}
	texture->releaseReference();
	//
	needsUpdate = true;
}

void TextureAtlas::update() {
	Console::println("TextureAtlas::update(): " + atlasTextureId);
	// release last atlas if we have any
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
		atlasTexture = nullptr;
	}

	if (atlasTextureIdxToTextureMapping.empty() == true) {
		Console::println("TextureAtlas::update(): " + atlasTextureId + ": nothing to do");
		//
		needsUpdate = false;
		//
		return;
	}

	//
	auto textureAtlasSize = static_cast<int>(Math::ceil(Math::sqrt(atlasTextureIdxToTextureMapping.size())));
	auto atlasTextureWidth = textureAtlasSize * ATLAS_TEXTURE_SIZE;
	auto atlasTextureHeight = textureAtlasSize * ATLAS_TEXTURE_SIZE;
	auto atlasTextureByteBuffer = ByteBuffer::allocate(atlasTextureWidth * atlasTextureHeight * 4);
	/*
	for (auto y = 0; y < atlasTextureHeight; y++)
	for (auto x = 0; x < atlasTextureWidth; x++) {
		auto atlasTextureIdxX = x / ATLAS_TEXTURE_SIZE;
		auto atlasTextureIdxY = y / ATLAS_TEXTURE_SIZE;
		auto textureX = x - (atlasTextureIdxX * ATLAS_TEXTURE_SIZE);
		auto textureY = y - (atlasTextureIdxY * ATLAS_TEXTURE_SIZE);
		auto textureXFloat = static_cast<float>(textureX) / static_cast<float>(ATLAS_TEXTURE_SIZE);
		auto textureYFloat = static_cast<float>(textureY) / static_cast<float>(ATLAS_TEXTURE_SIZE);
		auto atlasTextureIdx = atlasTextureIdxY * textureAtlasSize + atlasTextureIdxX;
		auto texture = atlasTextureIdxToTextureMapping[atlasTextureIdx];
		if (texture != nullptr) {
			auto textureWidth = texture->getTextureWidth();
			auto textureHeight = texture->getTextureHeight();
			auto textureBytesPerPixel = texture->getDepth() / 8;
			auto textureXInt = static_cast<int>(textureXFloat * static_cast<float>(textureWidth));
			auto textureYInt = static_cast<int>(textureYFloat * static_cast<float>(textureHeight));
			if (textureXInt < ATLAS_TEXTURE_BORDER) textureXInt = 0; else
			if (textureXInt > textureWidth - ATLAS_TEXTURE_BORDER) textureXInt = textureWidth - 1; else
				textureXInt = static_cast<int>((static_cast<float>(textureXInt) - static_cast<float>(ATLAS_TEXTURE_BORDER)) * (static_cast<float>(textureWidth) + static_cast<float>(ATLAS_TEXTURE_BORDER) * 2.0f) / static_cast<float>(textureWidth));
			if (textureYInt < ATLAS_TEXTURE_BORDER) textureYInt = 0; else
			if (textureYInt > textureHeight - ATLAS_TEXTURE_BORDER) textureYInt = textureHeight - 1; else
				textureYInt = static_cast<int>((static_cast<float>(textureYInt) - static_cast<float>(ATLAS_TEXTURE_BORDER)) * (static_cast<float>(textureHeight) + static_cast<float>(ATLAS_TEXTURE_BORDER) * 2.0f) / static_cast<float>(textureHeight));
			auto texturePixelOffset =
				textureYInt * textureWidth * textureBytesPerPixel +
				textureXInt * textureBytesPerPixel;
			auto r = texture->getTextureData()->get(texturePixelOffset + 0);
			auto g = texture->getTextureData()->get(texturePixelOffset + 1);
			auto b = texture->getTextureData()->get(texturePixelOffset + 2);
			auto a = textureBytesPerPixel == 4?texture->getTextureData()->get(texturePixelOffset + 3):0xff;
			atlasTextureByteBuffer->put(r);
			atlasTextureByteBuffer->put(g);
			atlasTextureByteBuffer->put(b);
			atlasTextureByteBuffer->put(a);
		} else {
			auto r = 0xff;
			auto g = 0x00;
			auto b = 0x00;
			auto a = 0xff;
			atlasTextureByteBuffer->put(r);
			atlasTextureByteBuffer->put(g);
			atlasTextureByteBuffer->put(b);
			atlasTextureByteBuffer->put(a);
		}
	}
	*/
	atlasTexture = new Texture(
		atlasTextureId,
		32,
		atlasTextureWidth, atlasTextureHeight,
		atlasTextureWidth, atlasTextureHeight,
		atlasTextureByteBuffer
	);
	atlasTexture->setAtlasSize(textureAtlasSize);
	atlasTexture->setUseMipMap(false);
	atlasTexture->acquireReference();

	//
	needsUpdate = false;
}


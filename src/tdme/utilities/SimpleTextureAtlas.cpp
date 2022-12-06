#include <tdme/utilities/SimpleTextureAtlas.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

using tdme::utilities::SimpleTextureAtlas;

using std::string;
using std::to_string;

using tdme::engine::fileio::textures::Texture;
using tdme::math::Math;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;

SimpleTextureAtlas::SimpleTextureAtlas(const string& id): atlasTextureId(id) {
}

SimpleTextureAtlas::~SimpleTextureAtlas() {
	for (auto& it: atlasTextureIdxToTextureMapping) {
		it.second->releaseReference();
	}
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
	}
}

int SimpleTextureAtlas::addTexture(Texture* texture) {
	Console::println("SimpleTextureAtlas::addTexture(): texture added to atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
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
	requiresUpdate = true;
	//
	return textureIdx;
}

void SimpleTextureAtlas::removeTexture(Texture* texture) {
	Console::println("SimpleTextureAtlas::removeTexture(): texture removed from atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
	auto textureIdx = getTextureIdx(texture);
	if (textureIdx == TEXTURE_IDX_NONE) {
		Console::println("SimpleTextureAtlas::removeTexture(): texture was not yet added to atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
		return;
	}
	textureReferenceCounter[texture]--;
	if (textureReferenceCounter[texture] == 0) {
		Console::println("SimpleTextureAtlas::removeTexture(): reference counter = 0, texture removed from atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
		textureReferenceCounter.erase(texture);
		textureToAtlasTextureIdxMapping.erase(texture);
		atlasTextureIdxToTextureMapping.erase(textureIdx);
		texture->releaseReference();
	}
	//
	requiresUpdate = true;
}

void SimpleTextureAtlas::update() {
	Console::println("SimpleTextureAtlas::update(): " + atlasTextureId);
	// release last atlas if we have any
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
		atlasTexture = nullptr;
	}

	//
	if (atlasTextureIdxToTextureMapping.empty() == true) {
		Console::println("SimpleTextureAtlas::update(): " + atlasTextureId + ": nothing to do");
		//
		requiresUpdate = false;
		//
		return;
	}

	//
	auto textureAtlasSize = static_cast<int>(Math::ceil(Math::sqrt(atlasTextureIdxToTextureMapping.size())));
	auto atlasTextureWidth = textureAtlasSize * ATLAS_TEXTURE_SIZE;
	auto atlasTextureHeight = textureAtlasSize * ATLAS_TEXTURE_SIZE;
	auto atlasTextureByteBuffer = ByteBuffer(atlasTextureWidth * atlasTextureHeight * 4);
	for (auto y = 0; y < atlasTextureHeight; y++)
	for (auto x = 0; x < atlasTextureWidth; x++) {
		auto atlasTextureIdxX = x / ATLAS_TEXTURE_SIZE;
		auto atlasTextureIdxY = y / ATLAS_TEXTURE_SIZE;
		auto textureX = x - (atlasTextureIdxX * ATLAS_TEXTURE_SIZE);
		auto textureY = y - (atlasTextureIdxY * ATLAS_TEXTURE_SIZE);
		auto textureXFloat = static_cast<float>(textureX) / static_cast<float>(ATLAS_TEXTURE_SIZE);
		auto textureYFloat = static_cast<float>(textureY) / static_cast<float>(ATLAS_TEXTURE_SIZE);
		auto atlasTextureIdx = atlasTextureIdxY * textureAtlasSize + atlasTextureIdxX;
		auto textureIt = atlasTextureIdxToTextureMapping.find(atlasTextureIdx);
		auto texture = textureIt != atlasTextureIdxToTextureMapping.end()?textureIt->second:nullptr;
		if (texture != nullptr) {
			auto textureTextureData = texture->getUncompressedTextureData();
			auto textureWidth = texture->getTextureWidth();
			auto textureHeight = texture->getTextureHeight();
			auto textureBytesPerPixel = texture->getDepthBitsPerPixel() / 8;
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
			auto r = textureTextureData.get(texturePixelOffset + 0);
			auto g = textureTextureData.get(texturePixelOffset + 1);
			auto b = textureTextureData.get(texturePixelOffset + 2);
			auto a = textureBytesPerPixel == 4?textureTextureData.get(texturePixelOffset + 3):0xff;
			atlasTextureByteBuffer.put(r);
			atlasTextureByteBuffer.put(g);
			atlasTextureByteBuffer.put(b);
			atlasTextureByteBuffer.put(a);
		} else {
			auto r = 0xff;
			auto g = 0x00;
			auto b = 0x00;
			auto a = 0xff;
			atlasTextureByteBuffer.put(r);
			atlasTextureByteBuffer.put(g);
			atlasTextureByteBuffer.put(b);
			atlasTextureByteBuffer.put(a);
		}
	}
	atlasTexture = new Texture(
		atlasTextureId,
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		atlasTextureWidth, atlasTextureHeight,
		atlasTextureWidth, atlasTextureHeight,
		Texture::TEXTUREFORMAT_RGBA,
		atlasTextureByteBuffer
	);
	atlasTexture->setAtlasSize(textureAtlasSize);
	atlasTexture->setUseMipMap(false);
	atlasTexture->acquireReference();

	//
	requiresUpdate = false;
}


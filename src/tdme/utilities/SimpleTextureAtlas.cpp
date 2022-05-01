#include <tdme/utilities/SimpleTextureAtlas.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

using tdme::utilities::SimpleTextureAtlas;

using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::math::Math;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;

SimpleTextureAtlas::SimpleTextureAtlas(const string& id): atlasTextureId(id) {
}

SimpleTextureAtlas::~SimpleTextureAtlas() {
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
		atlasTexture = nullptr;
	}
}

int SimpleTextureAtlas::addTexture(Texture* texture) {
	// check if texture had been added
	{
		auto textureIdx = getTextureIdx(texture);
		if (textureIdx != TEXTURE_IDX_NONE) {
			Console::println("SimpleTextureAtlas::addTexture(): texture was already added to atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
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
	//
	needsUpdate = true;
	//
	return textureIdx;
}

void SimpleTextureAtlas::removeTexture(Texture* texture) {
	auto textureIdx = getTextureIdx(texture);
	if (textureIdx == TEXTURE_IDX_NONE) {
		Console::println("SimpleTextureAtlas::removeTexture(): texture was not yet added to atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
		return;
	}
	textureToAtlasTextureIdxMapping.erase(texture);
	atlasTextureIdxToTextureMapping.erase(textureIdx);
	texture->releaseReference();
	//
	needsUpdate = true;
}

void SimpleTextureAtlas::update() {
	Console::println("SimpleTextureAtlas::update(): " + atlasTextureId);
	// release last atlas if we have any
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
		atlasTexture = nullptr;
	}
	//
	auto textureAtlasSize = static_cast<int>(Math::ceil(Math::sqrt(atlasTextureIdxToTextureMapping.size())));
	#define ATLAS_TEXTURE_SIZE	512
	#define ATLAS_TEXTURE_BORDER	32
	auto textureWidth = textureAtlasSize * ATLAS_TEXTURE_SIZE;
	auto textureHeight = textureAtlasSize * ATLAS_TEXTURE_SIZE;
	auto textureByteBuffer = ByteBuffer::allocate(textureWidth * textureHeight * 4);
	for (auto y = 0; y < textureHeight; y++)
	for (auto x = 0; x < textureWidth; x++) {
		auto atlasTextureIdxX = x / ATLAS_TEXTURE_SIZE;
		auto atlasTextureIdxY = y / ATLAS_TEXTURE_SIZE;
		auto materialTextureX = x - (atlasTextureIdxX * ATLAS_TEXTURE_SIZE);
		auto materialTextureY = y - (atlasTextureIdxY * ATLAS_TEXTURE_SIZE);
		auto materialTextureXFloat = static_cast<float>(materialTextureX) / static_cast<float>(ATLAS_TEXTURE_SIZE);
		auto materialTextureYFloat = static_cast<float>(materialTextureY) / static_cast<float>(ATLAS_TEXTURE_SIZE);
		auto atlasTextureIdx = atlasTextureIdxY * textureAtlasSize + atlasTextureIdxX;
		auto materialTexture = atlasTextureIdxToTextureMapping[atlasTextureIdx];
		if (materialTexture != nullptr) {
			auto materialTextureWidth = materialTexture->getTextureWidth();
			auto materialTextureHeight = materialTexture->getTextureHeight();
			auto materialTextureBytesPerPixel = materialTexture->getDepth() / 8;
			auto materialTextureXInt = static_cast<int>(materialTextureXFloat * static_cast<float>(materialTextureWidth));
			auto materialTextureYInt = static_cast<int>(materialTextureYFloat * static_cast<float>(materialTextureHeight));
			if (materialTextureXInt < ATLAS_TEXTURE_BORDER) materialTextureXInt = 0; else
			if (materialTextureXInt > materialTextureWidth - ATLAS_TEXTURE_BORDER) materialTextureXInt = materialTextureWidth - 1; else
				materialTextureXInt = static_cast<int>((static_cast<float>(materialTextureXInt) - static_cast<float>(ATLAS_TEXTURE_BORDER)) * (static_cast<float>(materialTextureWidth) + static_cast<float>(ATLAS_TEXTURE_BORDER) * 2.0f) / static_cast<float>(materialTextureWidth));
			if (materialTextureYInt < ATLAS_TEXTURE_BORDER) materialTextureYInt = 0; else
			if (materialTextureYInt > materialTextureHeight - ATLAS_TEXTURE_BORDER) materialTextureYInt = materialTextureHeight - 1; else
				materialTextureYInt = static_cast<int>((static_cast<float>(materialTextureYInt) - static_cast<float>(ATLAS_TEXTURE_BORDER)) * (static_cast<float>(materialTextureHeight) + static_cast<float>(ATLAS_TEXTURE_BORDER) * 2.0f) / static_cast<float>(materialTextureHeight));
			auto materialTexturePixelOffset =
				materialTextureYInt * materialTextureWidth * materialTextureBytesPerPixel +
				materialTextureXInt * materialTextureBytesPerPixel;
			auto materialPixelR = materialTexture->getTextureData()->get(materialTexturePixelOffset + 0);
			auto materialPixelG = materialTexture->getTextureData()->get(materialTexturePixelOffset + 1);
			auto materialPixelB = materialTexture->getTextureData()->get(materialTexturePixelOffset + 2);
			auto materialPixelA = materialTextureBytesPerPixel == 4?materialTexture->getTextureData()->get(materialTexturePixelOffset + 3):0xff;
			textureByteBuffer->put(materialPixelR);
			textureByteBuffer->put(materialPixelG);
			textureByteBuffer->put(materialPixelB);
			textureByteBuffer->put(materialPixelA);
		} else {
			auto materialPixelR = 0xff;
			auto materialPixelG = 0x00;
			auto materialPixelB = 0x00;
			auto materialPixelA = 0xff;
			textureByteBuffer->put(materialPixelR);
			textureByteBuffer->put(materialPixelG);
			textureByteBuffer->put(materialPixelB);
			textureByteBuffer->put(materialPixelA);
		}
	}
	atlasTexture = new Texture(
		atlasTextureId,
		32,
		textureWidth, textureHeight,
		textureWidth, textureHeight,
		textureByteBuffer
	);
	atlasTexture->setAtlasSize(textureAtlasSize);
	atlasTexture->acquireReference();
}


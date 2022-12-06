#include <tdme/utilities/TextureAtlas.h>

#include <algorithm>
#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

using tdme::utilities::TextureAtlas;

using std::sort;
using std::string;
using std::to_string;

using tdme::engine::fileio::textures::Texture;
using tdme::math::Math;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;

TextureAtlas::TextureAtlas(const string& id): atlasTextureId(id) {
}

TextureAtlas::~TextureAtlas() {
	for (auto& it: atlasTextureIdxToAtlasTextureMapping) {
		it.second.texture->releaseReference();
	}
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
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
	atlasTextureIdxToAtlasTextureMapping[textureIdx] = {
		.texture = texture,
		.orientation = AtlasTexture::ORIENTATION_NONE,
		.textureIdx = textureIdx,
		.left = -1,
		.top = -1,
		.width = texture->getTextureWidth(),
		.height = texture->getTextureHeight(),
		.line = -1
	};
	textureReferenceCounter[texture]++;
	//
	requiresUpdate = true;
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
		Console::println("TextureAtlas::removeTexture(): reference counter = 0, texture removed from atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
		textureReferenceCounter.erase(texture);
		textureToAtlasTextureIdxMapping.erase(texture);
		atlasTextureIdxToAtlasTextureMapping.erase(textureIdx);
		texture->releaseReference();
	}
	//
	requiresUpdate = true;
}

void TextureAtlas::update() {
	// see: https://www-ui.is.s.u-tokyo.ac.jp/~takeo/papers/i3dg2001.pdf

	//
	Console::println("TextureAtlas::update(): " + atlasTextureId);

	// release last atlas if we have any
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
		atlasTexture = nullptr;
	}

	//
	if (atlasTextureIdxToAtlasTextureMapping.empty() == true) {
		Console::println("TextureAtlas::update(): " + atlasTextureId + ": nothing to do");
		//
		requiresUpdate = false;
		//
		return;
	}

	// create a array of registered textures
	// rotate textures if required, aka stand up textures
	vector<AtlasTexture> atlasTextures;
	auto totalWidth = 0;
	auto totalHeight = 0;
	for (auto atlasTextureIdxToTextureMappingIt: atlasTextureIdxToAtlasTextureMapping) {
		auto& atlasTexture = atlasTextureIdxToTextureMappingIt.second;
		atlasTexture.left = -1;
		atlasTexture.height = -1;
		atlasTexture.line = -1;
		if (atlasTexture.texture->getTextureWidth() > atlasTexture.texture->getTextureHeight()) {
			atlasTexture.orientation = AtlasTexture::ORIENTATION_ROTATED;
			atlasTexture.width = atlasTexture.texture->getTextureHeight();
			atlasTexture.height = atlasTexture.texture->getTextureWidth();
		} else {
			atlasTexture.orientation = AtlasTexture::ORIENTATION_NORMAL;
			atlasTexture.width = atlasTexture.texture->getTextureWidth();
			atlasTexture.height = atlasTexture.texture->getTextureHeight();
		}
		totalWidth+= atlasTexture.texture->getTextureWidth();
		totalHeight+= atlasTexture.texture->getTextureHeight();
		atlasTextures.push_back(atlasTextureIdxToTextureMappingIt.second);
	}

	// sort by height
	sort(atlasTextures.begin(), atlasTextures.end(), sortAtlasTexturesByHeight);

	//
	auto atlasTextureWidth = 4096; // TODO: does not seem to work: static_cast<int>(Math::sqrt(static_cast<float>(totalWidth * totalHeight) * 1.2f));

	// initial layout
	{
		auto line = 0;
		auto left = 0;
		auto top = 0;
		auto heigthColumnMax = 0;
		for (auto& atlasTexture: atlasTextures) {
			atlasTexture.left = left;
			atlasTexture.top = top;
			atlasTexture.line = line;
			left+= atlasTexture.width;
			heigthColumnMax = Math::max(heigthColumnMax, atlasTexture.height);
			if (left >= atlasTextureWidth) {
				left = 0;
				top+= heigthColumnMax;
				heigthColumnMax = 0;
				line++;
			}
		}
		if (line == 0) {
			atlasTextureWidth = left;
			auto textureWidth = 1;
			while (textureWidth < atlasTextureWidth) textureWidth*= 2;
			atlasTextureWidth = textureWidth;
		}
	}

	// push upwards
	for (auto i = 0; i < atlasTextures.size(); i++) {
		auto pushedAtlasTextureTop = -1;
		auto& atlasTexture = atlasTextures[i];
		// compare with previous texture height if x in range of previous texture left ... left + width
		for (auto j = 0; j < i; j++) {
			auto& atlasTextureCompare = atlasTextures[j];
			if (atlasTextureCompare.line != atlasTexture.line - 1) continue;
			//
			if (atlasTextureCompare.left >= atlasTexture.left + atlasTexture.width) continue;
			if (atlasTexture.left >= atlasTextureCompare.left + atlasTextureCompare.width) continue;
			//
			pushedAtlasTextureTop = Math::max(pushedAtlasTextureTop, atlasTextureCompare.top + atlasTextureCompare.height);
		}
		if (pushedAtlasTextureTop != -1) atlasTexture.top = pushedAtlasTextureTop;
	}

	// determine new height
	auto atlasTextureHeight = 0;
	for (auto& atlasTexture: atlasTextures) {
		atlasTextureHeight = Math::max(atlasTextureHeight, atlasTexture.top + atlasTexture.height);
	}

	// height power of 2
	{
		auto textureHeight = 1;
		while (textureHeight < atlasTextureHeight) textureHeight*= 2;
		atlasTextureHeight = textureHeight;
	}

	//
	auto atlasTextureByteBuffer = ByteBuffer(atlasTextureWidth * atlasTextureHeight * 4);
	auto atlasTextureBuffer = atlasTextureByteBuffer.getBuffer();

	// generate atlas
	for (auto& atlasTexture: atlasTextures) {
		auto atlasLeft = atlasTexture.left;
		auto atlasTop = atlasTexture.top;
		auto texture = atlasTexture.texture;
		auto textureData = texture->getUncompressedTextureData();
		auto textureBytesPerPixel = texture->getDepthBitsPerPixel() / 8;
		auto textureWidth = texture->getTextureWidth();
		auto textureHeight = texture->getTextureHeight();
		for (auto y = 0; y < textureHeight; y++) {
			for (auto x = 0; x < textureWidth; x++) {
				auto r = textureData.get(y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel + 0);
				auto g = textureData.get(y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel + 1);
				auto b = textureData.get(y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel + 2);
				auto a = textureBytesPerPixel == 4?textureData.get(y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel + 3):0xff;
				if (atlasTexture.orientation == AtlasTexture::ORIENTATION_NORMAL) {
					atlasTextureBuffer[(atlasTop + textureHeight - 1 - y) * atlasTextureWidth * 4 + (atlasLeft + x) * 4 + 0] = r;
					atlasTextureBuffer[(atlasTop + textureHeight - 1 - y) * atlasTextureWidth * 4 + (atlasLeft + x) * 4 + 1] = g;
					atlasTextureBuffer[(atlasTop + textureHeight - 1 - y) * atlasTextureWidth * 4 + (atlasLeft + x) * 4 + 2] = b;
					atlasTextureBuffer[(atlasTop + textureHeight - 1 - y) * atlasTextureWidth * 4 + (atlasLeft + x) * 4 + 3] = a;
				} else
				if (atlasTexture.orientation == AtlasTexture::ORIENTATION_ROTATED) {
					atlasTextureBuffer[(atlasTop + x) * atlasTextureWidth * 4 + (atlasLeft + textureHeight - 1 - y) * 4 + 0] = r;
					atlasTextureBuffer[(atlasTop + x) * atlasTextureWidth * 4 + (atlasLeft + textureHeight - 1 - y) * 4 + 1] = g;
					atlasTextureBuffer[(atlasTop + x) * atlasTextureWidth * 4 + (atlasLeft + textureHeight - 1 - y) * 4 + 2] = b;
					atlasTextureBuffer[(atlasTop + x) * atlasTextureWidth * 4 + (atlasLeft + textureHeight - 1 - y) * 4 + 3] = a;
				}
			}
		}
	}

	//
	atlasTexture = new Texture(
		atlasTextureId,
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		atlasTextureWidth, atlasTextureHeight,
		atlasTextureWidth, atlasTextureHeight,
		Texture::TEXTUREFORMAT_RGBA,
		atlasTextureByteBuffer
	);
	atlasTexture->setUseMipMap(false);
	atlasTexture->acquireReference();

	// write atlas textures back to our hash map
	for (auto& atlasTexture: atlasTextures) atlasTextureIdxToAtlasTextureMapping[atlasTexture.textureIdx] = atlasTexture;

	//
	Console::println("TextureAtlas::update(): dump textures: ");
	for (auto atlasTextureIdxToTextureMappingIt: atlasTextureIdxToAtlasTextureMapping) {
		auto& atlasTexture = atlasTextureIdxToTextureMappingIt.second;
		Console::println(
			"TextureAtlas::update(): have texture: " + atlasTexture.texture->getId() + ", " +
			"left: " + to_string(atlasTexture.left) + ", " +
			"top: " + to_string(atlasTexture.top) + ", " +
			"width: " + to_string(atlasTexture.width) + ", " +
			"height: " + to_string(atlasTexture.height) + ", " +
			"orientation: " + to_string(atlasTexture.orientation)
		);
	}

	//
	requiresUpdate = false;
}


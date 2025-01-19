#include <agui/utilities/TextureAtlas.h>

#include <algorithm>
#include <string>

#include <agui/agui.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/math/Math.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Console.h>

using agui::utilities::TextureAtlas;

using std::sort;
using std::string;
using std::to_string;

using agui::gui::textures::GUITexture;
using agui::math::Math;
using agui::utilities::ByteBuffer;
using agui::utilities::Console;

TextureAtlas::TextureAtlas(const string& id): atlasTextureId(id) {
}

TextureAtlas::~TextureAtlas() {
	for (const auto& [atlasTextureEntityIdx, atlasTextureEntity]: atlasTextureIdxToAtlasTextureMapping) {
		atlasTextureEntity.texture->releaseReference();
	}
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
	}
}

int TextureAtlas::addTexture(GUITexture* texture) {
	if (VERBOSE == true) Console::printLine("TextureAtlas::addTexture(): texture added to atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
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

void TextureAtlas::removeTexture(GUITexture* texture) {
	if (VERBOSE == true) Console::printLine("TextureAtlas::removeTexture(): texture removed from atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
	auto textureIdx = getTextureIdx(texture);
	if (textureIdx == TEXTURE_IDX_NONE) {
		Console::printLine("TextureAtlas::removeTexture(): texture was not yet added to atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
		return;
	}
	textureReferenceCounter[texture]--;
	if (textureReferenceCounter[texture] == 0) {
		if (VERBOSE == true) Console::printLine("TextureAtlas::removeTexture(): reference counter = 0, texture removed from atlas: " + texture->getId() + ", atlas with id: " + atlasTextureId);
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
	if (VERBOSE == true) Console::printLine("TextureAtlas::update(): " + atlasTextureId);

	// release last atlas if we have any
	if (atlasTexture != nullptr) {
		atlasTexture->releaseReference();
		atlasTexture = nullptr;
	}

	//
	if (atlasTextureIdxToAtlasTextureMapping.empty() == true) {
		if (VERBOSE == true) Console::printLine("TextureAtlas::update(): " + atlasTextureId + ": nothing to do");
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
	for (auto& [atlasTextureEntityIdx, atlasTextureEntity]: atlasTextureIdxToAtlasTextureMapping) {
		atlasTextureEntity.left = -1;
		atlasTextureEntity.height = -1;
		atlasTextureEntity.line = -1;
		if (atlasTextureEntity.texture->getTextureWidth() > atlasTextureEntity.texture->getTextureHeight()) {
			atlasTextureEntity.orientation = AtlasTexture::ORIENTATION_ROTATED;
			atlasTextureEntity.width = atlasTextureEntity.texture->getTextureHeight();
			atlasTextureEntity.height = atlasTextureEntity.texture->getTextureWidth();
		} else {
			atlasTextureEntity.orientation = AtlasTexture::ORIENTATION_NORMAL;
			atlasTextureEntity.width = atlasTextureEntity.texture->getTextureWidth();
			atlasTextureEntity.height = atlasTextureEntity.texture->getTextureHeight();
		}
		totalWidth+= atlasTextureEntity.texture->getTextureWidth();
		totalHeight+= atlasTextureEntity.texture->getTextureHeight();
		atlasTextures.push_back(atlasTextureEntity);
	}

	// sort by height
	sort(
		atlasTextures.begin(),
		atlasTextures.end(),
		[](const AtlasTexture& atlasTexture1, const AtlasTexture& atlasTexture2) {
			return atlasTexture1.height > atlasTexture2.height;
		}
	);

	//
	auto atlasTextureWidth = 4096; // TODO: does not seem to work: static_cast<int>(Math::sqrt(static_cast<float>(totalWidth * totalHeight) * 1.2f));

	// initial layout
	{
		auto line = 0;
		auto left = 0;
		auto top = 0;
		auto heigthColumnMax = 0;
		for (auto& atlasTextureEntity: atlasTextures) {
			atlasTextureEntity.left = left;
			atlasTextureEntity.top = top;
			atlasTextureEntity.line = line;
			left+= atlasTextureEntity.width;
			heigthColumnMax = Math::max(heigthColumnMax, atlasTextureEntity.height);
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
		auto& atlasTextureEntity = atlasTextures[i];
		// compare with previous texture height if x in range of previous texture left ... left + width
		for (auto j = 0; j < i; j++) {
			const auto& atlasTextureEntityCompare = atlasTextures[j];
			if (atlasTextureEntityCompare.line != atlasTextureEntity.line - 1) continue;
			//
			if (atlasTextureEntityCompare.left >= atlasTextureEntity.left + atlasTextureEntity.width) continue;
			if (atlasTextureEntity.left >= atlasTextureEntityCompare.left + atlasTextureEntityCompare.width) continue;
			//
			pushedAtlasTextureTop = Math::max(pushedAtlasTextureTop, atlasTextureEntityCompare.top + atlasTextureEntityCompare.height);
		}
		if (pushedAtlasTextureTop != -1) atlasTextureEntity.top = pushedAtlasTextureTop;
	}

	// determine new height
	auto atlasTextureHeight = 0;
	for (const auto& atlasTextureEntity: atlasTextures) {
		atlasTextureHeight = Math::max(atlasTextureHeight, atlasTextureEntity.top + atlasTextureEntity.height);
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
	for (const auto& atlasTextureEntity: atlasTextures) {
		auto atlasLeft = atlasTextureEntity.left;
		auto atlasTop = atlasTextureEntity.top;
		auto texture = atlasTextureEntity.texture;
		auto textureData = texture->getRGBTextureData();
		auto textureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;
		auto textureWidth = texture->getTextureWidth();
		auto textureHeight = texture->getTextureHeight();
		for (auto y = 0; y < textureHeight; y++) {
			for (auto x = 0; x < textureWidth; x++) {
				auto r = textureData.get(y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel + 0);
				auto g = textureData.get(y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel + 1);
				auto b = textureData.get(y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel + 2);
				auto a = textureBytesPerPixel == 4?textureData.get(y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel + 3):0xff;
				if (atlasTextureEntity.orientation == AtlasTexture::ORIENTATION_NORMAL) {
					atlasTextureBuffer[(atlasTop + textureHeight - 1 - y) * atlasTextureWidth * 4 + (atlasLeft + x) * 4 + 0] = r;
					atlasTextureBuffer[(atlasTop + textureHeight - 1 - y) * atlasTextureWidth * 4 + (atlasLeft + x) * 4 + 1] = g;
					atlasTextureBuffer[(atlasTop + textureHeight - 1 - y) * atlasTextureWidth * 4 + (atlasLeft + x) * 4 + 2] = b;
					atlasTextureBuffer[(atlasTop + textureHeight - 1 - y) * atlasTextureWidth * 4 + (atlasLeft + x) * 4 + 3] = a;
				} else
				if (atlasTextureEntity.orientation == AtlasTexture::ORIENTATION_ROTATED) {
					atlasTextureBuffer[(atlasTop + x) * atlasTextureWidth * 4 + (atlasLeft + textureHeight - 1 - y) * 4 + 0] = r;
					atlasTextureBuffer[(atlasTop + x) * atlasTextureWidth * 4 + (atlasLeft + textureHeight - 1 - y) * 4 + 1] = g;
					atlasTextureBuffer[(atlasTop + x) * atlasTextureWidth * 4 + (atlasLeft + textureHeight - 1 - y) * 4 + 2] = b;
					atlasTextureBuffer[(atlasTop + x) * atlasTextureWidth * 4 + (atlasLeft + textureHeight - 1 - y) * 4 + 3] = a;
				}
			}
		}
	}

	//
	atlasTexture = new GUITexture(
		atlasTextureId,
		GUITexture::TEXTUREDEPTH_RGBA,
		GUITexture::TEXTUREFORMAT_RGBA,
		atlasTextureWidth, atlasTextureHeight,
		atlasTextureWidth, atlasTextureHeight,
		GUITexture::TEXTUREFORMAT_RGBA,
		atlasTextureByteBuffer
	);
	atlasTexture->setUseCompression(false);
	atlasTexture->setUseMipMap(false);
	atlasTexture->acquireReference();

	// write atlas textures back to our hash map
	for (const auto& atlasTextureEntity: atlasTextures) atlasTextureIdxToAtlasTextureMapping[atlasTextureEntity.textureIdx] = atlasTextureEntity;

	//
	if (VERBOSE == true) {
		Console::printLine("TextureAtlas::update(): dump textures: ");
		for (const auto& [atlasTextureEntityIdx, atlasTextureEntity]: atlasTextureIdxToAtlasTextureMapping) {
			Console::printLine(
				"TextureAtlas::update(): have texture: " + atlasTextureEntity.texture->getId() + ", " +
				"left: " + to_string(atlasTextureEntity.left) + ", " +
				"top: " + to_string(atlasTextureEntity.top) + ", " +
				"width: " + to_string(atlasTextureEntity.width) + ", " +
				"height: " + to_string(atlasTextureEntity.height) + ", " +
				"orientation: " + to_string(atlasTextureEntity.orientation)
			);
		}
	}

	//
	requiresUpdate = false;
}


#include <tdme/engine/subsystems/renderer/Renderer.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/utilities/ByteBuffer.h>

using std::string;
using std::to_string;

using tdme::engine::subsystems::renderer::Renderer;

using tdme::engine::Texture;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::utilities::ByteBuffer;

Renderer::Renderer()
{
	CONTEXTINDEX_DEFAULT = 0;
	ID_NONE = -1;
	CLEAR_DEPTH_BUFFER_BIT = -1;
	CLEAR_COLOR_BUFFER_BIT = -1;
	CULLFACE_FRONT = -1;
	CULLFACE_BACK = -1;
	TEXTUREUNITS_MAX = -1;
	PROGRAM_GUI = 1;
	PROGRAM_OBJECTS = 2;
	PROGRAM_POINTS = 3;
	PROGRAM_LINES = 4;
	PROGRAM_COMPUTE = 5;
	SHADER_FRAGMENT_SHADER = -1;
	SHADER_VERTEX_SHADER = -1;
	SHADER_COMPUTE_SHADER = -1;
	DEPTHFUNCTION_ALWAYS = -1;
	DEPTHFUNCTION_EQUAL = -1;
	DEPTHFUNCTION_LESSEQUAL = -1;
	DEPTHFUNCTION_GREATEREQUAL = -1;
	FRAMEBUFFER_DEFAULT = -1;
	FRONTFACE_CW = -1;
	FRONTFACE_CCW = -1;
	LIGHTING_NONE = 0;
	CUBEMAPTEXTUREINDEX_NEGATIVE_X = -1;
	CUBEMAPTEXTUREINDEX_POSITIVE_X = -1;
	CUBEMAPTEXTUREINDEX_POSITIVE_Y = -1;
	CUBEMAPTEXTUREINDEX_NEGATIVE_Y = -1;
	CUBEMAPTEXTUREINDEX_POSITIVE_Z = -1;
	CUBEMAPTEXTUREINDEX_NEGATIVE_Z = -1;
	LIGHTING_SPECULAR = 1;
	LIGHTING_PBR = 2;
	UNIFORM_CL_SKINNING_VERTEX_COUNT = -1;
	UNIFORM_CL_SKINNING_MATRIX_COUNT = -1;
	UNIFORM_CL_SKINNING_INSTANCE_COUNT = -1;
	viewPortWidth = 0;
	viewPortHeight = 0;
	TEXTUREUNITS_MAX = 2;
	projectionMatrix.identity();
	cameraMatrix.identity();
	modelViewMatrix.identity();
	viewportMatrix.identity();
	effectPass = 0;
}

Renderer::~Renderer() {
}

Texture* Renderer::generateMipMap(const string& id, Texture* texture, int32_t level, int32_t atlasBorderSize) {
	auto textureTextureData = texture->getRGBTextureData();
	auto generatedTextureWidth = texture->getTextureWidth() / 2;
	auto generatedTextureHeight = texture->getTextureHeight() / 2;
	auto generatedTextureByteBuffer = ByteBuffer(generatedTextureWidth * generatedTextureHeight * 4);
	auto atlasTextureSize = texture->getWidth() / texture->getAtlasSize();
	auto materialTextureWidth = texture->getTextureWidth() / texture->getAtlasSize();
	auto materialTextureHeight = texture->getTextureHeight() / texture->getAtlasSize();
	auto materialTextureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;
	for (auto y = 0; y < generatedTextureHeight; y++)
	for (auto x = 0; x < generatedTextureWidth; x++) {
		auto atlasTextureIdxX = (x * 2) / atlasTextureSize;
		auto atlasTextureIdxY = (y * 2) / atlasTextureSize;
		auto materialTextureX = (x * 2) - (atlasTextureIdxX * atlasTextureSize);
		auto materialTextureY = (y * 2) - (atlasTextureIdxY * atlasTextureSize);
		auto materialTextureXFloat = static_cast<float>(materialTextureX) / static_cast<float>(atlasTextureSize);
		auto materialTextureYFloat = static_cast<float>(materialTextureY) / static_cast<float>(atlasTextureSize);
		{
			auto materialSamples = 0;
			auto materialTextureXInt = static_cast<int>(materialTextureXFloat * static_cast<float>(materialTextureWidth));
			auto materialTextureYInt = static_cast<int>(materialTextureYFloat * static_cast<float>(materialTextureHeight));
			auto materialPixelR = 0;
			auto materialPixelG = 0;
			auto materialPixelB = 0;
			auto materialPixelA = 0;
			for (auto y = -1; y <= 1; y++)
			for (auto x = -1; x <= 1; x++)
			if ((Math::abs(x) == 1 && Math::abs(y) == 1) == false &&
				materialTextureXInt + x >= 0 && materialTextureXInt + x < materialTextureWidth &&
				materialTextureYInt + y >= 0 && materialTextureYInt + y < materialTextureHeight) {
				auto materialTexturePixelOffset =
					(atlasTextureIdxY * materialTextureHeight + materialTextureYInt + y) * texture->getTextureWidth() * materialTextureBytesPerPixel +
					(atlasTextureIdxX * materialTextureWidth + materialTextureXInt + x) * materialTextureBytesPerPixel;
				materialPixelR+= textureTextureData.get(materialTexturePixelOffset + 0);
				materialPixelG+= textureTextureData.get(materialTexturePixelOffset + 1);
				materialPixelB+= textureTextureData.get(materialTexturePixelOffset + 2);
				materialPixelA+= materialTextureBytesPerPixel == 4?textureTextureData.get(materialTexturePixelOffset + 3):0xff;
				materialSamples++;
			}
			generatedTextureByteBuffer.put(materialPixelR / materialSamples);
			generatedTextureByteBuffer.put(materialPixelG / materialSamples);
			generatedTextureByteBuffer.put(materialPixelB / materialSamples);
			generatedTextureByteBuffer.put(materialPixelA / materialSamples);
		}
	}
	auto generatedTexture = new Texture(
		id + ".mipmap." + to_string(level),
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		generatedTextureWidth,
		generatedTextureHeight,
		generatedTextureWidth,
		generatedTextureHeight,
		Texture::TEXTUREFORMAT_RGBA,
		generatedTextureByteBuffer
	);
	generatedTexture->setAtlasSize(texture->getAtlasSize());
	generatedTexture->acquireReference();
	return generatedTexture;
}

int Renderer::getMipLevels(Texture* texture) {
	if (texture->isUseMipMap() == false) return 1;
	auto widthMipLevels = 1;
	auto heightMipLevels = 1;
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	while (textureWidth > 16) {
		textureWidth/= 2;
		widthMipLevels++;
	}
	while (textureHeight > 16) {
		textureHeight/= 2;
		heightMipLevels++;
	}
	auto mipLevels = Math::min(widthMipLevels, heightMipLevels);
	if (texture->getAtlasSize() > 1) {
		auto borderSize = 32;
		auto maxLevel = 0;
		while (borderSize > 4) {
			maxLevel++;
			borderSize/= 2;
		}
		return Math::min(mipLevels, maxLevel);
	}
	//
	return mipLevels;
}

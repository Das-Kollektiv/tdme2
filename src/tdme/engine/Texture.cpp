#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/BZ7TextureReader.h>
#include <tdme/engine/fileio/textures/BZ7TextureWriter.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/fileio/textures/PNGTextureReader.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Texture;

using tdme::engine::fileio::textures::BZ7TextureReader;
using tdme::engine::fileio::textures::BZ7TextureWriter;
using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::fileio::textures::PNGTextureReader;
using tdme::engine::fileio::textures::PNGTextureWriter;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;

ByteBuffer Texture::getRGBTextureData(TextureFormat format, const ByteBuffer& textureData) {
	// do we already have the requested rgb format?
	auto rgbFormat = getRGBFormatByPixelBitsPerPixel(getRGBDepthBitsPerPixel());
	if (format == rgbFormat) {
		// yup, done
		return textureData;
	}

	// no?, convert it
	switch(format) {
		case TEXTUREFORMAT_RGB:
			{
				// input texture parameters
				auto textureBytesPerPixel = 3;
				// generated rgb raw data
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				auto rgbTextureData = ByteBuffer(textureWidth * textureHeight * rgbTextureDataBytesPerPixel);
				for (auto y = 0; y < textureHeight; y++) {
					for (auto x = 0; x < textureWidth; x++) {
						auto offset = y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel;
						auto red = textureData.get(offset + 0);
						auto green = textureData.get(offset + 1);
						auto blue = textureData.get(offset + 2);
						auto alpha = 0xff;
						//
						rgbTextureData.put(red);
						rgbTextureData.put(green);
						rgbTextureData.put(blue);
						if (rgbTextureDataBytesPerPixel == 4) rgbTextureData.put(0xff);
					}
				}
				//
				return rgbTextureData;
			}
		case TEXTUREFORMAT_RGBA:
			{
				// input texture parameters
				auto textureBytesPerPixel = 4;
				// generated rgb raw data
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				auto rgbTextureData = ByteBuffer(textureWidth * textureHeight * rgbTextureDataBytesPerPixel);
				for (auto y = 0; y < textureHeight; y++) {
					for (auto x = 0; x < textureWidth; x++) {
						auto offset = y * textureWidth * textureBytesPerPixel + x * textureBytesPerPixel;
						auto red = textureData.get(offset + 0);
						auto green = textureData.get(offset + 1);
						auto blue = textureData.get(offset + 2);
						auto alpha = textureData.get(offset + 3);
						//
						rgbTextureData.put(red);
						rgbTextureData.put(green);
						rgbTextureData.put(blue);
						if (rgbTextureDataBytesPerPixel == 4) rgbTextureData.put(alpha);
					}
				}
				//
				return rgbTextureData;
			}
		case TEXTUREFORMAT_RGB_PNG:
			{
				// generated rgb raw data
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				auto rgbTextureData = ByteBuffer(textureWidth * textureHeight * rgbTextureDataBytesPerPixel);

				//
				PNGTextureReader::read(*textureData.getBufferVector(), rgbTextureData);

				//
				return rgbTextureData;
			}
		case TEXTUREFORMAT_RGBA_PNG:
			{
				// generated rgb raw data
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				auto rgbTextureData = ByteBuffer(textureWidth * textureHeight * rgbTextureDataBytesPerPixel);

				//
				PNGTextureReader::read(*textureData.getBufferVector(), rgbTextureData);

				//
				return rgbTextureData;
			}
		case TEXTUREFORMAT_RGB_BZ7:
			{
				// generated rgb raw data
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				auto rgbTextureData = ByteBuffer(textureWidth * textureHeight * rgbTextureDataBytesPerPixel);

				//
				BZ7TextureReader::read(textureWidth, textureHeight, rgbTextureDataBytesPerPixel, *textureData.getBufferVector(), rgbTextureData);

				//
				return rgbTextureData;
			}
		case TEXTUREFORMAT_RGBA_BZ7:
			{
				// generated rgb raw data
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				auto rgbTextureData = ByteBuffer(textureWidth * textureHeight * rgbTextureDataBytesPerPixel);

				//
				BZ7TextureReader::read(textureWidth, textureHeight, rgbTextureDataBytesPerPixel, *textureData.getBufferVector(), rgbTextureData);

				//
				return rgbTextureData;
			}
	}

	//
	return ByteBuffer();
}

ByteBuffer Texture::getBZ7TextureData() {
	// do we already have the requested bz7 format?
	auto bz7Format = getBZ7FormatByPixelBitsPerPixel(getRGBDepthBitsPerPixel());
	if (format == bz7Format) {
		// yup, done
		return textureData;
	}

	//
	auto rgbaTextureData = getRGBTextureData();
	auto rgbaTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;

	// no?, convert it
	vector<uint8_t> bz7Data;
	BZ7TextureWriter::write(textureWidth, textureHeight, rgbaTextureDataBytesPerPixel, rgbaTextureData, bz7Data);

	//
	return ByteBuffer(bz7Data);
}

void Texture::setTextureData(TextureFormat format, const ByteBuffer& textureData) {
	if (this->format == format) {
		this->textureData = textureData;
	} else {
		switch(this->format) {
			case TEXTUREFORMAT_RGB:
			{
				//
				auto textureSize = textureWidth * textureHeight * 3;
				this->textureData = ByteBuffer(textureSize);
				// read rgb raw data
				auto rgbTextureData = getRGBTextureData(format, textureData);
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				for (auto y = 0; y < textureHeight; y++) {
					for (auto x = 0; x < textureWidth; x++) {
						auto offset = y * textureWidth * rgbTextureDataBytesPerPixel + x * rgbTextureDataBytesPerPixel;
						auto red = rgbTextureData.get(offset + 0);
						auto green = rgbTextureData.get(offset + 1);
						auto blue = rgbTextureData.get(offset + 2);
						auto alpha = rgbTextureDataBytesPerPixel == 4?rgbTextureData.get(offset + 3):0xff;
						//
						this->textureData.put(red);
						this->textureData.put(green);
						this->textureData.put(blue);
					}
				}
				break;
			}
			case TEXTUREFORMAT_RGBA:
				{
					//
					auto textureSize = textureWidth * textureHeight * 4;
					this->textureData = ByteBuffer(textureSize);
					// read rgb raw data
					auto rgbTextureData = getRGBTextureData(format, textureData);
					auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
					for (auto y = 0; y < textureHeight; y++) {
						for (auto x = 0; x < textureWidth; x++) {
							auto offset = y * textureWidth * rgbTextureDataBytesPerPixel + x * rgbTextureDataBytesPerPixel;
							auto red = rgbTextureData.get(offset + 0);
							auto green = rgbTextureData.get(offset + 1);
							auto blue = rgbTextureData.get(offset + 2);
							auto alpha = rgbTextureDataBytesPerPixel == 4?rgbTextureData.get(offset + 3):0xff;
							//
							this->textureData.put(red);
							this->textureData.put(green);
							this->textureData.put(blue);
							this->textureData.put(alpha);
						}
					}
					break;
				}
			case TEXTUREFORMAT_RGB_PNG:
				{
					// read rgb raw data
					auto rgbTextureData = getRGBTextureData(format, textureData);
					//
					vector<uint8_t> pngData;
					PNGTextureWriter::write(textureWidth, textureHeight, getRGBDepthBitsPerPixel() / 8, rgbTextureData, pngData, true, false);
					//
					this->textureData = ByteBuffer(pngData);
					//
					break;
				}
			case TEXTUREFORMAT_RGBA_PNG:
				{
					// read rgb raw data
					auto rgbTextureData = getRGBTextureData(format, textureData);
					//
					vector<uint8_t> pngData;
					PNGTextureWriter::write(textureWidth, textureHeight, getRGBDepthBitsPerPixel() / 8, rgbTextureData, pngData, false, false);
					//
					this->textureData = ByteBuffer(pngData);
					//
					break;
				}
		}
	}
}

ByteBuffer Texture::generateMipMap(int textureWidth, int textureHeight, int bytesPerPixel, const ByteBuffer& textureTextureData) {
	auto generatedTextureWidth = textureWidth / 2;
	auto generatedTextureHeight = textureHeight / 2;
	auto generatedTextureByteBuffer = ByteBuffer(generatedTextureWidth * generatedTextureHeight * bytesPerPixel);
	auto atlasTextureSize = textureWidth / atlasSize;
	auto materialTextureWidth = textureWidth / atlasSize;
	auto materialTextureHeight = textureHeight / atlasSize;
	auto materialTextureBytesPerPixel = bytesPerPixel;
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
					(atlasTextureIdxY * materialTextureHeight + materialTextureYInt + y) * textureWidth * materialTextureBytesPerPixel +
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
			if (bytesPerPixel == 4) generatedTextureByteBuffer.put(materialPixelA / materialSamples);
		}
	}
	return generatedTextureByteBuffer;
}

vector<Texture::MipMapTexture> Texture::getMipMapTextures(bool bz7Encoded) {
	vector<Texture::MipMapTexture> mipMapTextures;
	//
	auto mipLevels = getMipLevels();
	auto previousMipmapTexture = static_cast<Texture*>(nullptr);
	auto mipmapTexture = static_cast<Texture*>(nullptr);
	auto mipMapTextureWidth = textureWidth;
	auto mipMapTextureHeight = textureHeight;
	auto textureTextureData = getRGBTextureData();
	auto textureBytePerPixel = getRGBDepthBitsPerPixel() / 8;
	for (auto i = 1; i < mipLevels; i++) {
		textureTextureData = generateMipMap(mipMapTextureWidth, mipMapTextureHeight, textureBytePerPixel, textureTextureData);
		//
		mipMapTextureWidth/= 2;
		mipMapTextureHeight/= 2;
		//
		if (bz7Encoded == true) {
			vector<uint8_t> bz7Data;
			BZ7TextureWriter::write(mipMapTextureWidth, mipMapTextureHeight, textureBytePerPixel, textureTextureData, bz7Data);
			//
			mipMapTextures.push_back(
				{
					.format = getBZ7FormatByPixelBitsPerPixel(getRGBDepthBitsPerPixel()),
					.width = mipMapTextureWidth,
					.height = mipMapTextureHeight,
					.textureData = ByteBuffer(bz7Data)

				}
			);
		} else {
			//
			mipMapTextures.push_back(
				{
					.format = getRGBFormatByPixelBitsPerPixel(getRGBDepthBitsPerPixel()),
					.width = mipMapTextureWidth,
					.height = mipMapTextureHeight,
					.textureData = textureTextureData

				}
			);
		}
	}
	return mipMapTextures;
}

void Texture::onDelete() {
	TextureReader::removeFromCache(this);
}

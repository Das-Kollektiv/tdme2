#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fileio/textures/BC7TextureReader.h>
#include <tdme/engine/fileio/textures/BC7TextureWriter.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/fileio/textures/PNGTextureReader.h>
#include <tdme/engine/fileio/textures/PNGTextureWriter.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::Texture;

using tdme::engine::fileio::textures::BC7TextureReader;
using tdme::engine::fileio::textures::BC7TextureWriter;
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
		case TEXTUREFORMAT_RGB_BC7:
			{
				// generated rgb raw data
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				auto rgbTextureData = ByteBuffer(textureWidth * textureHeight * rgbTextureDataBytesPerPixel);

				//
				BC7TextureReader::read(textureWidth, textureHeight, rgbTextureDataBytesPerPixel, *textureData.getBufferVector(), rgbTextureData);

				//
				return rgbTextureData;
			}
		case TEXTUREFORMAT_RGBA_BC7:
			{
				// generated rgb raw data
				auto rgbTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;
				auto rgbTextureData = ByteBuffer(textureWidth * textureHeight * rgbTextureDataBytesPerPixel);

				//
				BC7TextureReader::read(textureWidth, textureHeight, rgbTextureDataBytesPerPixel, *textureData.getBufferVector(), rgbTextureData);

				//
				return rgbTextureData;
			}
	}

	//
	return ByteBuffer();
}

ByteBuffer Texture::getBC7TextureData() {
	// do we already have the requested bc7 format?
	auto bc7Format = getBC7FormatByPixelBitsPerPixel(getRGBDepthBitsPerPixel());
	if (format == bc7Format) {
		// yup, done
		return textureData;
	}

	//
	auto rgbaTextureData = getRGBTextureData();
	auto rgbaTextureDataBytesPerPixel = getRGBDepthBitsPerPixel() / 8;

	// no?, convert it
	vector<uint8_t> bc7Data;
	BC7TextureWriter::write(textureWidth, textureHeight, rgbaTextureDataBytesPerPixel, rgbaTextureData, bc7Data);

	//
	return ByteBuffer(bc7Data);
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
	auto materialTextureWidth = textureWidth / atlasSize;
	auto materialTextureHeight = textureHeight / atlasSize;
	auto materialTextureBytesPerPixel = bytesPerPixel;
	for (auto y = 0; y < generatedTextureHeight; y++)
	for (auto x = 0; x < generatedTextureWidth; x++) {
		auto atlasTextureIdxX = (x * 2) / materialTextureWidth;
		auto atlasTextureIdxY = (y * 2) / materialTextureHeight;
		auto materialTextureX = (x * 2) - (atlasTextureIdxX * materialTextureWidth);
		auto materialTextureY = (y * 2) - (atlasTextureIdxY * materialTextureHeight);
		auto materialTextureXFloat = static_cast<float>(materialTextureX) / static_cast<float>(materialTextureWidth);
		auto materialTextureYFloat = static_cast<float>(materialTextureY) / static_cast<float>(materialTextureHeight);
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

const vector<Texture::MipMapTexture>& Texture::getMipMapTextures(bool bc7Encoded) {
	// do we have any mip maps stored already?
	if (mipMapTextures.empty() == false) {
		// for now we only support stored BC7 mip maps and only return those if bc7 encodeding was requested
		//	TODO: maybe conversion from BC7 to RGB is required here conditionally, but can also be that decoding BC7 is slower than generating new mip maps
		auto mipMapFormatBC7 = mipMapTextures[0].format == TEXTUREFORMAT_RGB_BC7 || mipMapTextures[0].format == TEXTUREFORMAT_RGBA_BC7;
		if (mipMapFormatBC7 == true) {
			if (bc7Encoded == true) return mipMapTextures;
		} else {
			if (bc7Encoded == false) return mipMapTextures;
		}
		//
		mipMapTextures.clear();
	}

	//
	auto mipLevels = getMipLevels();
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
		if (bc7Encoded == true) {
			vector<uint8_t> bc7Data;
			BC7TextureWriter::write(mipMapTextureWidth, mipMapTextureHeight, textureBytePerPixel, textureTextureData, bc7Data);
			//
			mipMapTextures.emplace_back(
				getBC7FormatByPixelBitsPerPixel(getRGBDepthBitsPerPixel()),
				mipMapTextureWidth,
				mipMapTextureHeight,
				ByteBuffer(bc7Data)
			);
		} else {
			//
			mipMapTextures.emplace_back(
				getRGBFormatByPixelBitsPerPixel(getRGBDepthBitsPerPixel()),
				mipMapTextureWidth,
				mipMapTextureHeight,
				textureTextureData
			);
		}
	}
	return mipMapTextures;
}

void Texture::onDelete() {
	TextureReader::removeFromCache(this);
}

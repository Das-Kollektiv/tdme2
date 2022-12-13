#include <string>

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

void Texture::onDelete() {
	TextureReader::removeFromCache(this);
}

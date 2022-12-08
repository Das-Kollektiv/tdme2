#include <tdme/engine/fileio/textures/PNGTextureReader.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/TextureReader.h>
#include <tdme/engine/Texture.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

#include <ext/libpng/png.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::fileio::textures::PNGTextureReader;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::Texture;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;

void PNGTextureReader::readDataFromMemory(png_structp png_ptr, png_bytep outBytes, png_size_t outBytesToRead) {
	auto io_ptr = png_get_io_ptr(png_ptr);
	if (io_ptr == nullptr) return;

	auto pngInputStream = static_cast<PNGInputStream*>(io_ptr);
	pngInputStream->readBytes((int8_t*)outBytes, outBytesToRead);
}

bool PNGTextureReader::readHeader(const vector<uint8_t>& data, int& width, int& height, uint8_t& bytesPerPixel) {
	// create PNG input stream
	PNGInputStream pngInputStream(&data);

	// check that the PNG signature is in the file header
	unsigned char sig[8];
	pngInputStream.readBytes((int8_t*)sig, sizeof(sig));
	if (png_sig_cmp(sig, 0, 8)) {
		return false;
	}

	// create two data structures: 'png_struct' and 'png_info'
	auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png == nullptr) {
		return false;
	}
	auto info = png_create_info_struct(png);
	if (info == nullptr) {
		png_destroy_read_struct(&png, nullptr, nullptr);
		return false;
	}

	// set up custom read function
	png_set_read_fn(png, &pngInputStream, PNGTextureReader::readDataFromMemory);

	// set libpng error handling mechanism
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info, nullptr);
		return false;
	}

	// tell libpng we already read the signature
	png_set_sig_bytes(png, sizeof(sig));

	// get image information
	png_read_info(png, info);

	// dimensions
	width = png_get_image_width(png, info);
	height = png_get_image_height(png, info);

	// determine bytes per pixel
	bytesPerPixel = 0;
	switch(png_get_color_type(png, info)) {
		case PNG_COLOR_TYPE_GRAY:
			{
				bytesPerPixel = 3;
				break;
			}
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			{
				bytesPerPixel = 4;
				break;
			}
		case PNG_COLOR_TYPE_PALETTE:
			{
				// if transparency, convert it to alpha
				bool alpha = false;
				if (png_get_valid(png, info, PNG_INFO_tRNS)) {
					alpha = true;
				}
				bytesPerPixel = alpha?4:3;
				break;
			}
		case PNG_COLOR_TYPE_RGB:
			{
				bytesPerPixel = 3;
				break;
			}
		case PNG_COLOR_TYPE_RGBA:
			{
				bytesPerPixel = 4;
				break;
			}
		default:
			{
				png_destroy_read_struct(&png, &info, nullptr);
				return false;
			}
	}

	// done
	png_destroy_read_struct(&png, &info, nullptr);

	//
	return true;
}

bool PNGTextureReader::read(const vector<uint8_t>& data, ByteBuffer& textureByteBuffer) {
	// see: http://devcry.heiho.net/html/2015/20150517-libpng.html

	// create PNG input stream
	PNGInputStream pngInputStream(&data);

	// check that the PNG signature is in the file header
	unsigned char sig[8];
	pngInputStream.readBytes((int8_t*)sig, sizeof(sig));
	if (png_sig_cmp(sig, 0, 8)) {
		return false;
	}

	// create two data structures: 'png_struct' and 'png_info'
	auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png == nullptr) {
		return false;
	}
	auto info = png_create_info_struct(png);
	if (info == nullptr) {
		png_destroy_read_struct(&png, nullptr, nullptr);
		return false;
	}

	// set up custom read function
	png_set_read_fn(png, &pngInputStream, PNGTextureReader::readDataFromMemory);

	// set libpng error handling mechanism
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info, nullptr);
		return false;
	}

	// tell libpng we already read the signature
	png_set_sig_bytes(png, sizeof(sig));

	// get image information
	png_read_info(png, info);

	// dimensions
	auto width = png_get_image_width(png, info);
	auto height = png_get_image_height(png, info);

	// set one byte per channel
	if (png_get_bit_depth(png, info) < 8) png_set_packing(png);
	if (png_get_bit_depth(png, info) == 16) png_set_strip_16(png);

	// determine bytes per pixel
	auto bytesPerPixel = -1;
	switch(png_get_color_type(png, info)) {
		case PNG_COLOR_TYPE_GRAY:
			{
				bytesPerPixel = 3;
				png_set_gray_to_rgb(png);
				break;
			}
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			{
				bytesPerPixel = 4;
				png_set_gray_to_rgb(png);
				break;
			}
		case PNG_COLOR_TYPE_PALETTE:
			{
				// if transparency, convert it to alpha
				bool alpha = false;
				if (png_get_valid(png, info, PNG_INFO_tRNS)) {
					alpha = true;
					png_set_tRNS_to_alpha(png);
				}
				bytesPerPixel = alpha?4:3;
				png_set_expand(png);
				break;
			}
		case PNG_COLOR_TYPE_RGB:
			{
				bytesPerPixel = 3;
				break;
			}
		case PNG_COLOR_TYPE_RGBA:
			{
				bytesPerPixel = 4;
				break;
			}
		default:
			{
				png_destroy_read_struct(&png, &info, nullptr);
				return false;
			}
	}

	// ... what ever :DDD
	png_set_interlace_handling(png);
	png_read_update_info(png, info);

	// setup array with row pointers into pixel buffer
	auto rows = new png_bytep[height];
	auto p = (uint8_t*)textureByteBuffer.getBuffer();
	for(auto i = 0; i < height; i++) {
		rows[i] = p;
		p += width * bytesPerPixel;
	}

	// read all rows (data goes into 'pixels' buffer)
	// Note that any decoding errors will jump to the
	// setjmp point and eventually return nullptr
	png_read_image(png, rows);
	png_read_end(png, nullptr);

	//
	delete [] rows;

	// done
	png_destroy_read_struct(&png, &info, nullptr);

	//
	return true;
}

Texture* PNGTextureReader::read(const string& textureId, const vector<uint8_t>& data, bool powerOfTwo, const string& idPrefix) {
	int width;
	int height;
	uint8_t bytesPerPixel;
	if (readHeader(data, width, height, bytesPerPixel) == false) {
		Console::println("PNGTextureReader::read(): " + idPrefix + textureId + ": Could not read PNG header");
		return nullptr;
	}
	// make width, height a power of 2
	auto textureWidth = width;
	auto textureHeight = height;
	if (powerOfTwo == true) {
		textureWidth = 1;
		while (textureWidth < width) textureWidth*= 2;
		textureHeight = 1;
		while (textureHeight < height) textureHeight*= 2;
		if (textureWidth != width || textureHeight != height) {
			auto textureByteBuffer = ByteBuffer(width * height * bytesPerPixel);
			if (read(data, textureByteBuffer) == false) {
				Console::println("PNGTextureReader::read(): " + idPrefix + textureId + ": Could not read PNG bitmap data");
				return nullptr;
			}
			Console::println("PNGTextureReader::read(): " + idPrefix + textureId + ": scaling to fit power of 2: " + to_string(width) + "x" + to_string(height) + " --> " + to_string(textureWidth) + "x" + to_string(textureHeight));
			auto textureByteBufferScaled = ByteBuffer(textureWidth * textureHeight * bytesPerPixel);
			auto textureYIncrement = (float)textureHeight / (float)height;
			auto textureYPixelRest = 0.0f;
			auto textureY = 0;
			for (auto y = 0; y < height; y++) {
				for (auto i = 0; i < (int)textureYIncrement + (int)textureYPixelRest; i++) {
					TextureReader::scaleTextureLine(textureByteBuffer, textureByteBufferScaled, width, textureWidth, bytesPerPixel, y);
					textureY++;
				}
				textureYPixelRest-= (int)textureYPixelRest;
				textureYPixelRest+= textureYIncrement - (int)textureYIncrement;

			}
			while (textureY < textureHeight) {
				TextureReader::scaleTextureLine(textureByteBuffer, textureByteBufferScaled, width, textureWidth, bytesPerPixel, height - 1);
				textureY++;
			}
			// thats it, return the scaled version
			auto texture = new Texture(
				idPrefix + textureId,
				Texture::getRGBDepthByPixelBitsPerPixel(bytesPerPixel * 8),
				Texture::getRGBFormatByPixelBitsPerPixel(bytesPerPixel * 8),
				width,
				height,
				textureWidth,
				textureHeight,
				Texture::getRGBFormatByPixelBitsPerPixel(bytesPerPixel * 8),
				textureByteBufferScaled
			);
			texture->acquireReference();
			return texture;
		}
	}

	// thats it, return unscaled version
	auto texture = new Texture(
		idPrefix + textureId,
		Texture::getRGBDepthByPixelBitsPerPixel(bytesPerPixel * 8),
		bytesPerPixel == 3?Texture::TEXTUREFORMAT_RGB_PNG:Texture::TEXTUREFORMAT_RGBA_PNG,
		width,
		height,
		textureWidth,
		textureHeight,
		bytesPerPixel == 3?Texture::TEXTUREFORMAT_RGB_PNG:Texture::TEXTUREFORMAT_RGBA_PNG,
		ByteBuffer(data)
	);
	texture->acquireReference();
	return texture;
}


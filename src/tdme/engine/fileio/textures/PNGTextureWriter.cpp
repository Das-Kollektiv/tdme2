#include <tdme/engine/fileio/textures/PNGTextureWriter.h>

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>

#include <ext/libpng/png.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::fileio::textures::PNGTextureWriter;

using tdme::engine::fileio::textures::Texture;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;


void PNGTextureWriter::writePNGDataToMemory(png_structp png_ptr, png_bytep inBytes, png_size_t inBytesToWrite) {
	png_voidp io_ptr = png_get_io_ptr(png_ptr);
	if (io_ptr == nullptr) return;

	PNGOutputStream* pngOutputStream = static_cast<PNGOutputStream*>(io_ptr);
	pngOutputStream->writeBytes((int8_t*)inBytes, inBytesToWrite);
}

void PNGTextureWriter::flushPNGDataToMemory(png_structp png_ptr) {
	// no op
}

bool PNGTextureWriter::write(Texture* texture, const string& pathName, const string& fileName, bool removeAlphaChannel, bool flipY) {
	vector<uint8_t> data;
	if (write(texture, data, removeAlphaChannel, flipY) == false) return false;

	FileSystem::getInstance()->setContent(pathName, fileName, data);

	return true;
}

bool PNGTextureWriter::write(Texture* texture, vector<uint8_t>& pngData, bool removeAlphaChannel, bool flipY) {
	// see: https://gist.github.com/niw/5963798
	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) {
		return false;
	}

	png_infop info = png_create_info_struct(png);
	if (!info) {
		return false;
	}

	if (setjmp(png_jmpbuf(png))) {
		return false;
	}

	// create PNG input stream
	PNGOutputStream pngOutputStream(&pngData);

	// set up custom read function
	png_set_write_fn(png, &pngOutputStream, PNGTextureWriter::writePNGDataToMemory, PNGTextureWriter::flushPNGDataToMemory);

	//
	auto bytesPerPixel = texture->getDepth() / 8;
	auto width = texture->getTextureWidth();
	auto height = texture->getTextureHeight();
	auto pixels = texture->getTextureData();

	// output is 8bit depth, RGBA format.
	png_set_IHDR(
		png,
		info,
		width,
		height,
		8,
		removeAlphaChannel == false && bytesPerPixel == 4?PNG_COLOR_TYPE_RGBA:PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);
	png_write_info(png, info);

	// remove the alpha channel for PNG_COLOR_TYPE_RGB format
	if (removeAlphaChannel == true) {
		png_set_filler(png, 0, PNG_FILLER_AFTER);
	}

	//
	png_bytep* row_pointers = new png_bytep[height];
	if (flipY == true) {
		for (auto y = 0; y < height; y++) row_pointers[y] = pixels->getBuffer() + width * bytesPerPixel * (height - 1 - y);
	} else {
		for (auto y = 0; y < height; y++) row_pointers[y] = pixels->getBuffer() + width * bytesPerPixel * y;
	}

	png_write_image(png, row_pointers);
	png_write_end(png, NULL);

	free (row_pointers);

	png_destroy_write_struct(&png, &info);

	return true;
}

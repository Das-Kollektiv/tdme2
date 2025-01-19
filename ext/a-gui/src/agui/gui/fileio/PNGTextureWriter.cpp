#include <agui/gui/fileio/PNGTextureWriter.h>

#include <new>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Console.h>

#include <ext/libpng/png.h>

using std::nothrow;
using std::string;
using std::to_string;
using std::vector;

using agui::gui::fileio::PNGTextureWriter;

using agui::gui::textures::GUITexture;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;
using agui::utilities::ByteBuffer;
using agui::utilities::Console;


void PNGTextureWriter::writePNGDataToMemory(png_structp png_ptr, png_bytep inBytes, png_size_t inBytesToWrite) {
	png_voidp io_ptr = png_get_io_ptr(png_ptr);
	if (io_ptr == nullptr) return;

	PNGOutputStream* pngOutputStream = static_cast<PNGOutputStream*>(io_ptr);
	pngOutputStream->writeBytes((int8_t*)inBytes, inBytesToWrite);
}

void PNGTextureWriter::flushPNGDataToMemory(png_structp png_ptr) {
	// no op
}

bool PNGTextureWriter::write(GUITexture* texture, const string& pathName, const string& fileName, bool removeAlphaChannel, bool flipY) {
	vector<uint8_t> data;
	if (write(texture, data, removeAlphaChannel, flipY) == false) return false;

	FileSystem::getInstance()->setContent(pathName, fileName, data);

	return true;
}

bool PNGTextureWriter::write(GUITexture* texture, vector<uint8_t>& pngData, bool removeAlphaChannel, bool flipY) {
	return
		write(
			texture->getTextureWidth(),
			texture->getTextureHeight(),
			texture->getRGBDepthBitsPerPixel() / 8,
			texture->getRGBTextureData(),
			pngData,
			removeAlphaChannel,
			flipY
		);
}

bool PNGTextureWriter::write(int width, int height, int bytesPerPixel, const ByteBuffer& textureByteBuffer, vector<uint8_t>& pngData, bool removeAlphaChannel, bool flipY) {
	// see: https://gist.github.com/niw/5963798
	auto png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png == nullptr) {
		return false;
	}

	auto info = png_create_info_struct(png);
	if (info == nullptr) {
		return false;
	}

	if (setjmp(png_jmpbuf(png))) {
		return false;
	}

	// create PNG input stream
	PNGOutputStream pngOutputStream(&pngData);

	// set up custom read function
	png_set_write_fn(png, &pngOutputStream, PNGTextureWriter::writePNGDataToMemory, PNGTextureWriter::flushPNGDataToMemory);

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
	if (removeAlphaChannel == true && bytesPerPixel == 4) {
		png_set_filler(png, 0, PNG_FILLER_AFTER);
	}

	// write png
	auto success = false;
	auto rowPtrs = new(nothrow)png_bytep[height];
	if (rowPtrs != nullptr) {
		//
		success = true;
		// create pointers to each line beginning in texture byte buffer
		auto pixelBuffer = (uint8_t*)textureByteBuffer.getBuffer();
		//
		if (flipY == true) {
			for (auto y = 0; y < height; y++) rowPtrs[y] = pixelBuffer + width * bytesPerPixel * (height - 1 - y);
		} else {
			for (auto y = 0; y < height; y++) rowPtrs[y] = pixelBuffer + width * bytesPerPixel * y;
		}
		//
		png_write_image(png, rowPtrs);
		png_write_end(png, NULL);

		//
		delete [] rowPtrs;
	}

	//
	png_destroy_write_struct(&png, &info);

	//
	return success;
}

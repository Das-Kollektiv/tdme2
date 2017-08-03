// Generated from /tdme/src/tdme/engine/fileio/textures/TextureLoader.java
#include <tdme/engine/fileio/textures/TextureLoader.h>

#include <stdlib.h>

#include <string>

#include <java/lang/String.h>
#include <java/nio/ByteBuffer.h>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/os/_FileSystem.h>
#include <tdme/os/_FileSystemInterface.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/_Console.h>

#include <ext/libpng/png.h>

using std::wstring;

using java::lang::String;
using java::nio::ByteBuffer;

using tdme::engine::fileio::textures::TextureLoader;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::PNGInputStream;
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::StringConverter;
using tdme::utils::_Console;

Texture* TextureLoader::loadTexture(const wstring& path, const wstring& fileName) throw (_FileSystemException)
{
	// _Console::println(wstring(L"TextureLoader::loadTexture(): loading: " + path->getCPPWString() + L"/" + fileName->getCPPWString()));
	if ((new String(fileName))->toLowerCase()->endsWith(new String(L".png")) == true) {
		Texture* texture = TextureLoader::loadPNG(path, fileName);
		return texture;
	}
	return nullptr;
}

void TextureLoader::readPNGDataFromMemory(png_structp png_ptr, png_bytep outBytes, png_size_t outBytesToRead) {
	png_voidp io_ptr = png_get_io_ptr(png_ptr);
	if (io_ptr == nullptr) return;

	PNGInputStream* pngInputStream = (PNGInputStream*)io_ptr;
	pngInputStream->readBytes((int8_t*)outBytes, outBytesToRead);
}

Texture* TextureLoader::loadPNG(const wstring& path, const wstring& fileName) throw (_FileSystemException) {
	// see: http://devcry.heiho.net/html/2015/20150517-libpng.html

	// canonical file name for id
	auto canonicalFileName = _FileSystem::getInstance()->getCanonicalPath(new String(path), new String(fileName));

	// create PNG input stream
	PNGInputStream* pngInputStream = new PNGInputStream(_FileSystem::getInstance()->getContent(new String(path), new String(fileName)));

	// check that the PNG signature is in the file header
	unsigned char sig[8];
	pngInputStream->readBytes((int8_t*)sig, sizeof(sig));
	if (png_sig_cmp(sig, 0, 8)) {
		delete pngInputStream;
	    return nullptr;
	}

	// create two data structures: 'png_struct' and 'png_info'
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png == nullptr) {
		delete pngInputStream;
	    return nullptr;
	}
	png_infop info = png_create_info_struct(png);
	if (info == nullptr) {
	    png_destroy_read_struct(&png, nullptr, nullptr);
	    delete pngInputStream;
	    return nullptr;
	}

	// set up custom read function
	png_set_read_fn(png, pngInputStream, TextureLoader::readPNGDataFromMemory);

	// set libpng error handling mechanism
	if (setjmp(png_jmpbuf(png))) {
	    png_destroy_read_struct(&png, &info, nullptr);
	    delete pngInputStream;
	    return nullptr;
	}

	// tell libpng we already read the signature
	png_set_sig_bytes(png, sizeof(sig));

	// get image information
	png_read_info(png, info);

	// dimensions
	int width = png_get_image_width(png, info);
	int height = png_get_image_height(png, info);

	// set one byte per channel
	if (png_get_bit_depth(png, info) < 8) png_set_packing(png);
	if (png_get_bit_depth(png, info) == 16) png_set_strip_16(png);

	// determine bytes per pixel
	int bytesPerPixel = -1;
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
	    		// does not seem to work though
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
	    		delete pngInputStream;
	    		return nullptr;
	    	}
	}

	// bytes per row
	int bytesPerRow = png_get_rowbytes(png, info);

	// ... what ever :DDD
	png_set_interlace_handling(png);
	png_read_update_info(png, info);

	// allocate pixel buffer
	unsigned char* pixels = new unsigned char[width * height * bytesPerPixel];

	// setup array with row pointers into pixel buffer
	png_bytep rows[height];
	unsigned char *p = pixels;
	for(int i = 0; i < height; i++) {
	    rows[i] = p;
	    p += width * bytesPerPixel;
	}

	// read all rows (data goes into 'pixels' buffer)
	// Note that any decoding errors will jump to the
	// setjmp point and eventually return nullptr
	png_read_image(png, rows);
	png_read_end(png, nullptr);

	// done
	png_destroy_read_struct(&png, &info, nullptr);
	delete pngInputStream;

	// thats it
	return new Texture(
		canonicalFileName->getCPPWString(),
		bytesPerPixel * 8,
		width,
		height,
		width,
		height,
		new ByteBuffer(width * height * bytesPerPixel, (int8_t*)pixels)
	);
}

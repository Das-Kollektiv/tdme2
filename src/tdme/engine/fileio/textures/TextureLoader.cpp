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
using tdme::os::_FileSystem;
using tdme::os::_FileSystemInterface;
using tdme::utils::StringConverter;
using tdme::utils::_Console;

TextureLoader::TextureLoader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

TextureLoader::TextureLoader()
	: TextureLoader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Texture* TextureLoader::loadTexture(String* path, String* fileName)
{
	clinit();
	// _Console::println(wstring(L"TextureLoader::loadTexture(): loading: " + path->getCPPWString() + L"/" + fileName->getCPPWString()));
	if (fileName->toLowerCase()->endsWith(new String(L".png")) == true) {
		Texture* texture = TextureLoader::loadPNG(path, fileName);
		return texture;
	}
	return nullptr;
}

Texture* TextureLoader::loadPNG(String* path, String* fileName) {
	// see: http://devcry.heiho.net/html/2015/20150517-libpng.html
	clinit();

	// canonical file name for id
	auto canonicalFileName = _FileSystem::getInstance()->getCanonicalPath(path, fileName);
	if (canonicalFileName == nullptr) {
		_Console::println(string("TextureLoader::loadPNG(): No canonical file name"));
	}

	// open file
	FILE *f = fopen(StringConverter::toString(canonicalFileName->getCPPWString()).c_str(), "rb");
	if (f == nullptr) {
	    return nullptr;
	}

	// check that the PNG signature is in the file header
	unsigned char sig[8];
	if (fread(sig, 1, sizeof(sig), f) < 8) {
	    fclose(f);
	    return nullptr;
	}
	if (png_sig_cmp(sig, 0, 8)) {
	    fclose(f);
	    return nullptr;
	}

	// create two data structures: 'png_struct' and 'png_info'
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png == nullptr) {
	    fclose(f);
	    return nullptr;
	}
	png_infop info = png_create_info_struct(png);
	if (info == nullptr) {
	    png_destroy_read_struct(&png, nullptr, nullptr);
	    fclose(f);
	    return nullptr;
	}

	// set libpng error handling mechanism
	if (setjmp(png_jmpbuf(png))) {
	    png_destroy_read_struct(&png, &info, nullptr);
	    fclose(f);
	    return nullptr;
	}

	// pass open file to png struct
	png_init_io(png, f);

	// skip signature bytes (we already read those)
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
	    		fclose(f);
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
	fclose(f);

	// thats it
	return new Texture(
		canonicalFileName,
		bytesPerPixel * 8,
		width,
		height,
		width,
		height,
		new ByteBuffer(width * height * bytesPerPixel, (int8_t*)pixels)
	);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* TextureLoader::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.fileio.textures.TextureLoader", 41);
    return c;
}

java::lang::Class* TextureLoader::getClass0()
{
	return class_();
}


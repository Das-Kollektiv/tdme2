#include <tdme/engine/fileio/textures/TextureReader.h>

#include <stdlib.h>

#include <string>
#include <vector>

#include <tdme/utils/ByteBuffer.h>

#include <tdme/engine/fileio/textures/Texture.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/StringUtils.h>

#include <ext/libpng/png.h>

using std::vector;
using std::string;

using tdme::utils::ByteBuffer;
using tdme::utils::Console;
using tdme::utils::Exception;

using tdme::engine::fileio::textures::TextureReader;
using tdme::engine::fileio::textures::Texture;
using tdme::engine::fileio::textures::PNGInputStream;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::StringUtils;

vector<string> TextureReader::extensions = {"png"};
map<string, Texture*> TextureReader::textureCache;

const vector<string>& TextureReader::getTextureExtensions() {
	return extensions;
}

Texture* TextureReader::read(const string& pathName, const string& fileName, bool useCache)
{
	Texture* texture = nullptr;

	// make canonical
	auto canonicalFile = FileSystem::getInstance()->getCanonicalPath(pathName, fileName);
	auto canonicalPathName = FileSystem::getInstance()->getPathName(canonicalFile);
	auto canonicalFileName = FileSystem::getInstance()->getFileName(canonicalFile);

	// do cache look up
	if (useCache == true) {
		auto textureCacheIt = textureCache.find(canonicalPathName + "/" + canonicalFileName);
		if (textureCacheIt != textureCache.end()) {
			texture = textureCacheIt->second;
		}
	}

	// have texture?
	if (texture == nullptr) {
		// nope try to load
		try {
			if (StringUtils::endsWith(StringUtils::toLowerCase(canonicalFileName), ".png") == true) {
				texture = TextureReader::loadPNG(canonicalPathName, canonicalFileName);
				if (texture != nullptr && useCache == true) textureCache[texture->getId()] = texture;
			}
		} catch (Exception& exception) {
			Console::println("TextureReader::loadTexture(): Could not load texture: " + canonicalPathName + "/" + canonicalFileName + ": " + (exception.what()));
		}
	}

	// done
	if (texture != nullptr) texture->acquireReference();
	return texture;
}

void TextureReader::readPNGDataFromMemory(png_structp png_ptr, png_bytep outBytes, png_size_t outBytesToRead) {
	png_voidp io_ptr = png_get_io_ptr(png_ptr);
	if (io_ptr == nullptr) return;

	PNGInputStream* pngInputStream = (PNGInputStream*)io_ptr;
	pngInputStream->readBytes((int8_t*)outBytes, outBytesToRead);
}

Texture* TextureReader::loadPNG(const string& pathName, const string& fileName) throw (FileSystemException) {
	// see: http://devcry.heiho.net/html/2015/20150517-libpng.html

	// canonical file name for id
	auto canonicalFileName = FileSystem::getInstance()->getCanonicalPath(pathName, fileName);

	// create PNG input stream
	vector<uint8_t> content;
	FileSystem::getInstance()->getContent(pathName, fileName, content);
	PNGInputStream* pngInputStream = new PNGInputStream(&content);

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
	png_set_read_fn(png, pngInputStream, TextureReader::readPNGDataFromMemory);

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
	ByteBuffer* pixelByteBuffer = ByteBuffer::allocate(width * height * bytesPerPixel);

	// setup array with row pointers into pixel buffer
	png_bytep* rows = new png_bytep[height];
	uint8_t* p = (uint8_t*)pixelByteBuffer->getBuffer();
	for(int i = 0; i < height; i++) {
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
	delete pngInputStream;

	// thats it
	return new Texture(
		canonicalFileName,
		bytesPerPixel * 8,
		width,
		height,
		width,
		height,
		pixelByteBuffer
	);
}

void TextureReader::removeFromCache(Texture* texture) {
	auto textureCacheIt = textureCache.find(texture->getId());
	if (textureCacheIt != textureCache.end()) textureCache.erase(textureCacheIt);
}

#include <tdme/engine/fileio/textures/TextureReader.h>

#include <stdlib.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/ByteBuffer.h>

#include <tdme/engine/Texture.h>
#include <tdme/math/Matrix2D3x3.h>
#include <tdme/math/Vector2.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

#include <ext/libpng/png.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::Exception;

using tdme::engine::Texture;
using tdme::engine::fileio::textures::TextureReader;
using tdme::math::Matrix2D3x3;
using tdme::math::Vector2;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::os::threading::Mutex;
using tdme::utilities::StringTools;

vector<string> TextureReader::extensions = {"png"};
Mutex* TextureReader::textureCacheMutex = new Mutex("texturecache-mutex");
map<string, Texture*>* TextureReader::textureCache = new map<string, Texture*>();

const vector<string>& TextureReader::getTextureExtensions() {
	return extensions;
}

Texture* TextureReader::read(const string& pathName, const string& fileName, bool useCache, bool powerOfTwo, const string& idPrefix)
{
	Texture* texture = nullptr;

	// make canonical
	auto canonicalFilePath = FileSystem::getInstance()->getCanonicalPath(pathName, fileName);
	auto canonicalPathName = FileSystem::getInstance()->getPathName(canonicalFilePath);
	auto canonicalFileName = FileSystem::getInstance()->getFileName(canonicalFilePath);

	// do cache look up
	if (useCache == true) {
		textureCacheMutex->lock();
		auto textureCacheIt = textureCache->find(idPrefix + canonicalFilePath);
		if (textureCacheIt != textureCache->end()) {
			texture = textureCacheIt->second;
		}
	}

	// have texture?
	if (texture == nullptr) {
		// nope try to load
		try {
			if (StringTools::endsWith(StringTools::toLowerCase(canonicalFileName), ".png") == true) {

				// create PNG input stream
				vector<uint8_t> data;
				FileSystem::getInstance()->getContent(pathName, fileName, data);

				texture = TextureReader::readPNG(canonicalFilePath, data, powerOfTwo, idPrefix);
				if (texture != nullptr && useCache == true) {
					(*textureCache)[texture->getId()] = texture;
				}
			}
		} catch (Exception& exception) {
			Console::println("TextureReader::read(): Could not load texture: " + canonicalPathName + "/" + canonicalFileName + ": " + (exception.what()));
		}
	}

	// done
	if (texture != nullptr) texture->acquireReference();

	//
	if (useCache == true) textureCacheMutex->unlock();

	// done
	return texture;
}

Texture* TextureReader::read16(const string& pathName, const string& fileName, bool useCache, bool powerOfTwo, const string& idPrefix)
{
	Texture* texture = nullptr;

	// make canonical
	auto canonicalFilePath = FileSystem::getInstance()->getCanonicalPath(pathName, fileName);
	auto canonicalPathName = FileSystem::getInstance()->getPathName(canonicalFilePath);
	auto canonicalFileName = FileSystem::getInstance()->getFileName(canonicalFilePath);

	// do cache look up
	if (useCache == true) {
		textureCacheMutex->lock();
		auto textureCacheIt = textureCache->find(idPrefix + canonicalFilePath + ":16");
		if (textureCacheIt != textureCache->end()) {
			texture = textureCacheIt->second;
		}
	}

	// have texture?
	if (texture == nullptr) {
		// nope try to load
		try {
			if (StringTools::endsWith(StringTools::toLowerCase(canonicalFileName), ".png") == true) {

				// create PNG input stream
				vector<uint8_t> data;
				FileSystem::getInstance()->getContent(pathName, fileName, data);

				texture = TextureReader::readPNG16(canonicalFilePath + ":16", data, powerOfTwo, idPrefix);
				if (texture != nullptr && useCache == true) {
					(*textureCache)[texture->getId()] = texture;
				}
			}
		} catch (Exception& exception) {
			Console::println("TextureReader::read16(): Could not load texture: " + canonicalPathName + "/" + canonicalFileName + ": " + (exception.what()));
		}
	}

	// done
	if (texture != nullptr) texture->acquireReference();

	//
	if (useCache == true) textureCacheMutex->unlock();

	// done
	return texture;
}

Texture* TextureReader::read2(const string& texturePathName, const string& textureFileName, const string& transparencyTexturePathName, const string& transparencyTextureFileName, bool useCache, bool powerOfTwo, const string& idPrefix) {
	// make canonical
	auto canonicalFile = FileSystem::getInstance()->getCanonicalPath(texturePathName, textureFileName);
	auto canonicalPathName = FileSystem::getInstance()->getPathName(canonicalFile);
	auto canonicalFileName = FileSystem::getInstance()->getFileName(canonicalFile);
	auto cacheId = idPrefix + canonicalPathName + "/" + canonicalFileName + "/transparency";

	// do cache look up
	if (useCache == true) {
		textureCacheMutex->lock();
		auto textureCacheIt = textureCache->find(cacheId);
		if (textureCacheIt != textureCache->end()) {
			auto texture = textureCacheIt->second;
			texture->acquireReference();
			textureCacheMutex->unlock();
			return texture;
		}
	}

	// load diffuse texture
	auto texture = TextureReader::read(texturePathName, textureFileName, false, powerOfTwo, idPrefix);
	if (texture == nullptr) {
		if (useCache == true) textureCacheMutex->unlock();
		return nullptr;
	}
	// additional transparency texture
	auto transparencyTexture = TextureReader::read(transparencyTexturePathName, transparencyTextureFileName, false, powerOfTwo, idPrefix);
	// do we have one?
	if (transparencyTexture == nullptr) {
		Console::println("TextureReader::read2(): transparency texture: failed: " + texturePathName + "/" + textureFileName + ";" + transparencyTexturePathName + "/" + transparencyTextureFileName);
		if (useCache == true) {
			(*textureCache)[cacheId] = texture;
			textureCacheMutex->unlock();
		}
		return texture;
	}
	// same dimensions and supported pixel depth?
	if (texture->getTextureWidth() != transparencyTexture->getTextureWidth() || texture->getTextureHeight() != transparencyTexture->getTextureHeight()) {
		Console::println("TextureReader::read2(): texture does not match transparency texture dimension: " + texturePathName + "/" + textureFileName + ";" + transparencyTexturePathName + "/" + transparencyTextureFileName);
		if (useCache == true) {
			(*textureCache)[cacheId] = texture;
			textureCacheMutex->unlock();
		}
		return texture;
	}
	// yep, combine diffuse map + diffuse transparency map
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto textureByteBuffer = ByteBuffer(textureWidth * textureHeight * 4);
	auto diffuseTextureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;
	auto transparencyTextureBytesPerPixel = transparencyTexture->getRGBDepthBitsPerPixel() / 8;
	auto transparencyTextureTextureData = transparencyTexture->getRGBTextureData();
	auto textureTextureData = texture->getRGBTextureData();
	for (auto y = 0; y < textureHeight; y++) {
		for (auto x = 0; x < textureWidth; x++) {
			auto transparencyTextureRed = transparencyTextureTextureData.get((y * textureWidth * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 0);
			auto transparencyTextureGreen = transparencyTextureTextureData.get((y * textureWidth * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 1);
			auto transparencyTextureBlue = transparencyTextureTextureData.get((y * textureWidth * transparencyTextureBytesPerPixel) + (x * transparencyTextureBytesPerPixel) + 2);
			textureByteBuffer.put(textureTextureData.get((y * textureWidth * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 0));
			textureByteBuffer.put(textureTextureData.get((y * textureWidth * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 1));
			textureByteBuffer.put(textureTextureData.get((y * textureWidth * diffuseTextureBytesPerPixel) + (x * diffuseTextureBytesPerPixel) + 2));
			textureByteBuffer.put((uint8_t)((transparencyTextureRed + transparencyTextureGreen + transparencyTextureBlue) * 0.3333f));
		}
	}
	//
	auto textureWithTransparency = new Texture(
		idPrefix + texture->getId() + "/transparency",
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		texture->getWidth(),
		texture->getHeight(),
		texture->getTextureWidth(),
		texture->getTextureHeight(),
		Texture::TEXTUREFORMAT_RGBA,
		textureByteBuffer
	);
	textureWithTransparency->acquireReference();
	if (useCache == true) {
		(*textureCache)[cacheId] = textureWithTransparency;
		textureCacheMutex->unlock();
	}
	texture->releaseReference();
	transparencyTexture->releaseReference();
	return textureWithTransparency;
}

void TextureReader::readPNGDataFromMemory(png_structp png_ptr, png_bytep outBytes, png_size_t outBytesToRead) {
	auto io_ptr = png_get_io_ptr(png_ptr);
	if (io_ptr == nullptr) return;

	auto pngInputStream = static_cast<PNGInputStream*>(io_ptr);
	pngInputStream->readBytes((int8_t*)outBytes, outBytesToRead);
}

Texture* TextureReader::readPNG(const string& textureId, const vector<uint8_t>& data, bool powerOfTwo, const string& idPrefix) {
	// see: http://devcry.heiho.net/html/2015/20150517-libpng.html

	// create PNG input stream
	PNGInputStream pngInputStream(&data);

	// check that the PNG signature is in the file header
	unsigned char sig[8];
	pngInputStream.readBytes((int8_t*)sig, sizeof(sig));
	if (png_sig_cmp(sig, 0, 8)) {
		return nullptr;
	}

	// create two data structures: 'png_struct' and 'png_info'
	auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png == nullptr) {
		return nullptr;
	}
	auto info = png_create_info_struct(png);
	if (info == nullptr) {
		png_destroy_read_struct(&png, nullptr, nullptr);
		return nullptr;
	}

	// set up custom read function
	png_set_read_fn(png, &pngInputStream, TextureReader::readPNGDataFromMemory);

	// set libpng error handling mechanism
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info, nullptr);
		return nullptr;
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
    			return nullptr;
    		}
	}

	// ... what ever :DDD
	png_set_interlace_handling(png);
	png_read_update_info(png, info);

	// allocate pixel buffer
	auto pixelByteBuffer = ByteBuffer(width * height * bytesPerPixel);

	// setup array with row pointers into pixel buffer
	auto rows = new png_bytep[height];
	auto p = (uint8_t*)pixelByteBuffer.getBuffer();
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

	// make width, height a power of 2
	auto textureWidth = width;
	auto textureHeight = height;
	if (powerOfTwo == true) {
		textureWidth = 1;
		while (textureWidth < width) textureWidth*= 2;
		textureHeight = 1;
		while (textureHeight < height) textureHeight*= 2;
		if (textureWidth != width || textureHeight != height) {
			Console::println("TextureReader::readPNG(): " + idPrefix + textureId + ": scaling to fit power of 2: " + to_string(width) + "x" + to_string(height) + " --> " + to_string(textureWidth) + "x" + to_string(textureHeight));
			auto pixelByteBufferScaled = ByteBuffer(textureWidth * textureHeight * bytesPerPixel);
			auto textureYIncrement = (float)textureHeight / (float)height;
			auto textureYPixelRest = 0.0f;
			auto textureY = 0;
			for (auto y = 0; y < height; y++) {
				for (auto i = 0; i < (int)textureYIncrement + (int)textureYPixelRest; i++) {
					scaleTextureLine(pixelByteBuffer, pixelByteBufferScaled, width, textureWidth, bytesPerPixel, y);
					textureY++;
				}
				textureYPixelRest-= (int)textureYPixelRest;
				textureYPixelRest+= textureYIncrement - (int)textureYIncrement;

			}
			while (textureY < textureHeight) {
				scaleTextureLine(pixelByteBuffer, pixelByteBufferScaled, width, textureWidth, bytesPerPixel, height - 1);
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
				pixelByteBufferScaled
			);
			texture->acquireReference();
			return texture;
		}
	}

	// thats it, return unscaled version
	auto texture = new Texture(
		idPrefix + textureId,
		Texture::getRGBDepthByPixelBitsPerPixel(bytesPerPixel * 8),
		Texture::getRGBFormatByPixelBitsPerPixel(bytesPerPixel * 8),
		width,
		height,
		textureWidth,
		textureHeight,
		Texture::getRGBFormatByPixelBitsPerPixel(bytesPerPixel * 8),
		pixelByteBuffer
	);
	texture->acquireReference();
	return texture;
}

Texture* TextureReader::readPNG16(const string& textureId, const vector<uint8_t>& data, bool powerOfTwo, const string& idPrefix) {
	// see: http://devcry.heiho.net/html/2015/20150517-libpng.html

	// create PNG input stream
	PNGInputStream pngInputStream(&data);

	// check that the PNG signature is in the file header
	unsigned char sig[8];
	pngInputStream.readBytes((int8_t*)sig, sizeof(sig));
	if (png_sig_cmp(sig, 0, 8)) {
		return nullptr;
	}

	// create two data structures: 'png_struct' and 'png_info'
	auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png == nullptr) {
		return nullptr;
	}
	auto info = png_create_info_struct(png);
	if (info == nullptr) {
		png_destroy_read_struct(&png, nullptr, nullptr);
		return nullptr;
	}

	// set up custom read function
	png_set_read_fn(png, &pngInputStream, TextureReader::readPNGDataFromMemory);

	// set libpng error handling mechanism
	if (setjmp(png_jmpbuf(png))) {
		png_destroy_read_struct(&png, &info, nullptr);
		return nullptr;
	}

	// tell libpng we already read the signature
	png_set_sig_bytes(png, sizeof(sig));

	// get image information
	png_read_info(png, info);

	// dimensions
	auto width = png_get_image_width(png, info);
	auto height = png_get_image_height(png, info);

	// set one byte per channel
	if (png_get_bit_depth(png, info) != 16) {
		Console::println("TextureReader::readPNG16(): Not a 16 bit PNG: " + textureId);
		png_destroy_read_struct(&png, &info, nullptr);
		return nullptr;
	}

	// determine bytes per pixel
	auto bytesPerPixel = -1;
	switch(png_get_color_type(png, info)) {
	    case PNG_COLOR_TYPE_GRAY:
			{
				bytesPerPixel = 6;
				png_set_gray_to_rgb(png);
				break;
			}
	    case PNG_COLOR_TYPE_GRAY_ALPHA:
			{
				bytesPerPixel = 8;
				png_set_gray_to_rgb(png);
				break;
			}
	    case PNG_COLOR_TYPE_RGB:
			{
				bytesPerPixel = 6;
				break;
			}
	    case PNG_COLOR_TYPE_RGBA:
			{
				bytesPerPixel = 8;
				break;
			}
	    default:
			{
				png_destroy_read_struct(&png, &info, nullptr);
				return nullptr;
			}
	}

	// ... what ever :DDD
	png_set_interlace_handling(png);
	png_read_update_info(png, info);

	// allocate pixel buffer
	auto pixelByteBuffer = ByteBuffer(width * height * bytesPerPixel);

	// setup array with row pointers into pixel buffer
	auto rows = new png_bytep[height];
	auto p = (uint8_t*)pixelByteBuffer.getBuffer();
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

	// make width, height a power of 2
	auto textureWidth = width;
	auto textureHeight = height;
	if (powerOfTwo == true) {
		textureWidth = 1;
		while (textureWidth < width) textureWidth*= 2;
		textureHeight = 1;
		while (textureHeight < height) textureHeight*= 2;
		if (textureWidth != width || textureHeight != height) {
			Console::println("TextureReader::readPNG16(): " + idPrefix + textureId + ": scaling to fit power of 2: " + to_string(width) + "x" + to_string(height) + " --> " + to_string(textureWidth) + "x" + to_string(textureHeight));
			auto pixelByteBufferScaled = ByteBuffer(textureWidth * textureHeight * bytesPerPixel);
			auto textureYIncrement = (float)textureHeight / (float)height;
			auto textureYPixelRest = 0.0f;
			auto textureY = 0;
			for (auto y = 0; y < height; y++) {
				for (auto i = 0; i < (int)textureYIncrement + (int)textureYPixelRest; i++) {
					scaleTextureLine(pixelByteBuffer, pixelByteBufferScaled, width, textureWidth, bytesPerPixel, y);
					textureY++;
				}
				textureYPixelRest-= (int)textureYPixelRest;
				textureYPixelRest+= textureYIncrement - (int)textureYIncrement;

			}
			while (textureY < textureHeight) {
				scaleTextureLine(pixelByteBuffer, pixelByteBufferScaled, width, textureWidth, bytesPerPixel, height - 1);
				textureY++;
			}
			// thats it, return scaled version
			auto texture = new Texture(
				idPrefix + textureId + ":16",
				Texture::getRGBDepthByPixelBitsPerPixel(bytesPerPixel * 8),
				Texture::getRGBFormatByPixelBitsPerPixel(bytesPerPixel * 8),
				width,
				height,
				textureWidth,
				textureHeight,
				Texture::getRGBFormatByPixelBitsPerPixel(bytesPerPixel * 8),
				pixelByteBufferScaled
			);
			texture->acquireReference();
			return texture;
		}
	}

	// thats it, return unscaled version
	auto texture = new Texture(
		idPrefix + textureId + ":16",
		Texture::getRGBDepthByPixelBitsPerPixel(bytesPerPixel * 8),
		Texture::getRGBFormatByPixelBitsPerPixel(bytesPerPixel * 8),
		width,
		height,
		textureWidth,
		textureHeight,
		Texture::getRGBFormatByPixelBitsPerPixel(bytesPerPixel * 8),
		pixelByteBuffer
	);
	texture->acquireReference();
	return texture;
}

void TextureReader::scaleTextureLine(const ByteBuffer& pixelByteBuffer, ByteBuffer& pixelByteBufferScaled, int width, int textureWidth, int bytesPerPixel, int y) {
	auto textureXIncrement = (float)textureWidth / (float)width;
	auto textureXPixelRest = 0.0f;
	auto textureX = 0;
	for (auto x = 0; x < width; x++) {
		for (auto i = 0; i < (int)textureXIncrement + (int)textureXPixelRest; i++) {
			for (auto bytePerPixel = 0; bytePerPixel < bytesPerPixel; bytePerPixel++) {
				pixelByteBufferScaled.put(pixelByteBuffer.get((y * width * bytesPerPixel) + (x * bytesPerPixel) + bytePerPixel));
			}
			textureX++;
		}
		textureXPixelRest-= (int)textureXPixelRest;
		textureXPixelRest+= textureXIncrement - (int)textureXIncrement;
	}
	{
		auto x = width - 1;
		while (textureX < textureWidth) {
			for (auto bytePerPixel = 0; bytePerPixel < bytesPerPixel; bytePerPixel++) {
				pixelByteBufferScaled.put(pixelByteBuffer.get((y * width * bytesPerPixel) + (x * bytesPerPixel) + bytePerPixel));
			}
			textureX++;
		}
	}
}

void TextureReader::removeFromCache(Texture* texture) {
	textureCacheMutex->lock();
	auto textureCacheIt = textureCache->find(texture->getId());
	if (textureCacheIt != textureCache->end()) textureCache->erase(textureCacheIt);
	textureCacheMutex->unlock();
}

Texture* TextureReader::rotate(Texture* texture, float rotation, const string& idSuffix) {
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto textureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;
	auto textureWidthRotated = -1;
	auto textureHeightRotated = -1;
	{
		auto rotationsMatrix = Matrix2D3x3::rotateAroundPoint(Vector2(textureWidth / 2.0f, textureHeight / 2.0f), rotation);
		Vector2 leftTop(0.0f, 0.0f);
		Vector2 rightTop(textureWidth, 0.0f);
		Vector2 leftBottom(0.0f, textureHeight);
		Vector2 rightBottom(textureWidth, textureHeight);
		auto leftTopRotated = rotationsMatrix.multiply(leftTop);
		auto rightTopRotated = rotationsMatrix.multiply(rightTop);
		auto leftBottomRotated = rotationsMatrix.multiply(leftBottom);
		auto rightBottomRotated = rotationsMatrix.multiply(rightBottom);
		auto textureWidthTransformedMin = Math::min(leftTopRotated.getX(),
				Math::min(rightTopRotated.getX(),
						Math::min(leftBottomRotated.getX(),
								rightBottomRotated.getX())));
		auto textureWidthTransformedMax = Math::max(leftTopRotated.getX(),
				Math::max(rightTopRotated.getX(),
						Math::max(leftBottomRotated.getX(),
								rightBottomRotated.getX())));
		auto textureHeightTransformedMin = Math::min(leftTopRotated.getY(),
				Math::min(rightTopRotated.getY(),
						Math::min(leftBottomRotated.getY(),
								rightBottomRotated.getY())));
		auto textureHeightTransformedMax = Math::max(leftTopRotated.getY(),
				Math::max(rightTopRotated.getY(),
						Math::max(leftBottomRotated.getY(),
								rightBottomRotated.getY())));
		textureWidthRotated = static_cast<int>(textureWidthTransformedMax
				- textureWidthTransformedMin);
		textureHeightRotated = static_cast<int>(textureHeightTransformedMax
				- textureHeightTransformedMin);
	}
	auto textureTextureData = texture->getRGBTextureData();
	auto rotatedTextureByteBuffer = ByteBuffer(textureWidthRotated * textureHeightRotated * 4);
	auto rotationsMatrix = Matrix2D3x3::rotateAroundPoint(Vector2(textureWidth / 2.0f, textureHeight / 2.0f), rotation);
	for (auto y = 0; y < textureHeightRotated; y++) {
		for (auto x = 0; x < textureWidthRotated; x++) {
			auto originalTexturePoint = rotationsMatrix.multiply(
				Vector2(
					x - (textureWidthRotated - textureWidth) / 2.0f,
					y - (textureHeightRotated - textureHeight) / 2.0f
				)
			);
			auto red = 0;
			auto green = 0;
			auto blue = 0;
			auto alpha = 0;
			auto originalX = static_cast<int>(originalTexturePoint.getX());
			auto originalY = static_cast<int>(originalTexturePoint.getY());
			if (originalX >= 0 && originalX < textureWidth && originalY >= 0 && originalY < textureHeight) {
				red = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 0);
				green = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 1);
				blue = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 2);
				alpha = textureBytesPerPixel == 4?textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 3):255;
			}
			rotatedTextureByteBuffer.put(red);
			rotatedTextureByteBuffer.put(green);
			rotatedTextureByteBuffer.put(blue);
			rotatedTextureByteBuffer.put(alpha);
		}
	}
	//
	auto rotatedTexture = new Texture(
		texture->getId() + idSuffix + ":tmp",
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		textureWidthRotated,
		textureHeightRotated,
		textureWidthRotated,
		textureHeightRotated,
		Texture::TEXTUREFORMAT_RGBA,
		rotatedTextureByteBuffer
	);
	rotatedTexture->acquireReference();
	// do smooooth
	auto filteredTexture = smooth(rotatedTexture, idSuffix);
	rotatedTexture->releaseReference();
	return filteredTexture;
}

Texture* TextureReader::scale(Texture* texture, int width, int height, const string& idSuffix) {
	auto textureTextureData = texture->getRGBTextureData();
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto textureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;
	auto textureWidthScaled = width;
	auto textureHeightScaled = height;
	auto scaledTextureByteBuffer = ByteBuffer(textureWidthScaled * textureHeightScaled * 4);
	auto scaleX = static_cast<float>(textureWidth) / static_cast<float>(textureWidthScaled);
	auto scaleY = static_cast<float>(textureHeight) / static_cast<float>(textureHeightScaled);
	for (auto y = 0; y < textureHeightScaled; y++) {
		for (auto x = 0; x < textureWidthScaled; x++) {
			auto originalTexturePoint = Vector2(static_cast<float>(x) * scaleX, static_cast<float>(y) * scaleY);
			auto red = 0;
			auto green = 0;
			auto blue = 0;
			auto alpha = 0;
			auto originalX = static_cast<int>(originalTexturePoint.getX());
			auto originalY = static_cast<int>(originalTexturePoint.getY());
			if (originalX >= 0 && originalX < textureWidth && originalY >= 0 && originalY < textureHeight) {
				red = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 0);
				green = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 1);
				blue = textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 2);
				alpha = textureBytesPerPixel == 4?textureTextureData.get((originalY * textureWidth * textureBytesPerPixel) + (originalX * textureBytesPerPixel) + 3):255;
			}
			scaledTextureByteBuffer.put(red);
			scaledTextureByteBuffer.put(green);
			scaledTextureByteBuffer.put(blue);
			scaledTextureByteBuffer.put(alpha);
		}
	}
	//
	auto scaledTexture = new Texture(
		texture->getId() + idSuffix,
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		textureWidthScaled,
		textureHeightScaled,
		textureWidthScaled,
		textureHeightScaled,
		Texture::TEXTUREFORMAT_RGBA,
		scaledTextureByteBuffer
	);
	scaledTexture->acquireReference();
	// no smoothing if texture got smaller
	if (textureWidthScaled < textureWidth) return scaledTexture;
	// otherwise do smoothing
	auto filteredTexture = smooth(scaledTexture, idSuffix);
	scaledTexture->releaseReference();
	return filteredTexture;
}

Texture* TextureReader::smooth(Texture* texture, const string& idSuffix, float adjacentSampleWeight) {
	//
	auto textureWidth = texture->getTextureWidth();
	auto textureHeight = texture->getTextureHeight();
	auto textureBytesPerPixel = texture->getRGBDepthBitsPerPixel() / 8;

	//
	auto textureTextureData = texture->getRGBTextureData();

	//
	auto filteredTextureByteBuffer = ByteBuffer(textureWidth * textureHeight * 4);
	for (auto y = 0; y < textureHeight; y++) {
		for (auto x = 0; x < textureWidth; x++) {
			auto samples = 0.0f;
			auto red = 0.0f;
			auto green = 0.0f;
			auto blue = 0.0f;
			auto alpha = 0.0f;
			{
				auto pixelOffset = (y * textureWidth * textureBytesPerPixel) + (x * textureBytesPerPixel);
				red+= textureTextureData.get(pixelOffset + 0) * 1.0f;
				green+= textureTextureData.get(pixelOffset + 1) * 1.0f;
				blue+= textureTextureData.get(pixelOffset + 2) * 1.0f;
				alpha+= (textureBytesPerPixel == 4?textureTextureData.get(pixelOffset + 3):255.0f) * 1.0f;
				samples+=1.0f;
			}
			for (auto _y = -1; _y <= 1; _y++) {
				for (auto _x = -1; _x <= 1; _x++) {
					if ((Math::abs(_x) == 1 && Math::abs(_y) == 1) == false &&
						(x + _x >= 0 && x + _x < textureWidth && y + _y >= 0 && y + _y < textureHeight)) {
						auto pixelOffset = ((y + _y) * textureWidth * textureBytesPerPixel) + ((x + _x) * textureBytesPerPixel);
						red+= textureTextureData.get(pixelOffset + 0) * adjacentSampleWeight;
						green+= textureTextureData.get(pixelOffset + 1) * adjacentSampleWeight;
						blue+= textureTextureData.get(pixelOffset + 2) * adjacentSampleWeight;
						alpha+= (textureBytesPerPixel == 4?textureTextureData.get(pixelOffset + 3):255.0f) * adjacentSampleWeight;
						samples+= adjacentSampleWeight;
					}
				}
			}
			filteredTextureByteBuffer.put(static_cast<uint8_t>(red / samples));
			filteredTextureByteBuffer.put(static_cast<uint8_t>(green / samples));
			filteredTextureByteBuffer.put(static_cast<uint8_t>(blue / samples));
			filteredTextureByteBuffer.put(static_cast<uint8_t>(alpha / samples));
		}
	}

	//
	auto filteredTexture = new Texture(
		texture->getId() + idSuffix,
		Texture::TEXTUREDEPTH_RGBA,
		Texture::TEXTUREFORMAT_RGBA,
		textureWidth,
		textureHeight,
		textureWidth,
		textureHeight,
		Texture::TEXTUREFORMAT_RGBA,
		filteredTextureByteBuffer
	);
	filteredTexture->acquireReference();
	return filteredTexture;
}

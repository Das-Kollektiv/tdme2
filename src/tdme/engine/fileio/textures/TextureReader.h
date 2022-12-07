#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/ByteBuffer.h>

#include <ext/libpng/png.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::os::filesystem::FileSystemException;
using tdme::os::threading::Mutex;
using tdme::utilities::ByteBuffer;

/**
 * Texture reader class
 * @author Andreas Drewke
 */
class tdme::engine::fileio::textures::TextureReader final
{
	friend class tdme::engine::Texture;

public:
	/**
	 * @return texture extensions
	 */
	static const vector<string>& getTextureExtensions();

	/**
	 * Reads a texture
	 * @param pathName path name
	 * @param fileName file name
	 * @param useCache use cache
	 * @param powerOfTwo scale image to fit power of two dimensions
	 * @param idPrefix id prefix
	 * @return texture data instance or null
	 */
	static Texture* read(const string& pathName, const string& fileName, bool useCache = true, bool powerOfTwo = true, const string& idPrefix = string());

	/**
	 * Reads a texture with additional transparency texture
	 * @param texturePathName texture path name
	 * @param textureFileName texture file name
	 * @param transparencyTexturePathName transparency texture path name
	 * @param transparencyTextureFileName transparency texture file name
	 * @param useCache use cache
	 * @param powerOfTwo scale image to fit power of two dimensions
	 * @param idPrefix id prefix
	 * @return texture data instance or null
	 */
	static Texture* read2(const string& texturePathName, const string& textureFileName, const string& transparencyTexturePathName, const string& transparencyTextureFileName, bool useCache = true, bool powerOfTwo = true, const string& idPrefix = string());

	/**
	 * Read PNG header from memory
	 * @param data vector data to read PNG from
	 * @param width width
	 * @param height height
	 * @param bytes per pixel
	 * @return success
	 */
	static bool readPNGHeader(const vector<uint8_t>& data, int& width, int& height, uint8_t& bytesPerPixel);

	/**
	 * Read PNG from memory into texture byte buffer
	 * @param data vector data to read PNG from
	 * @param textureByteBuffer texture byte buffer
	 * @return success
	 */
	static bool readPNG(const vector<uint8_t>& data, ByteBuffer& textureByteBuffer);

	/**
	 * Read PNG from memory
	 * @param textureId texture id
	 * @param data vector data to read PNG from
	 * @param powerOfTwo scale image to fit power of two dimensions
	 * @param idPrefix id prefix
	 */
	static Texture* readPNG(const string& textureId, const vector<uint8_t>& data, bool powerOfTwo = true, const string& idPrefix = string());

	/**
	 * Rotate texture around center
	 * @param texture texture
	 * @param rotation rotation in degree
	 * @param idSuffix id suffix for generated texture
	 * @return rotation rotation
	 */
	static Texture* rotate(Texture* texture, float rotation, const string& idSuffix = ":rotated");

	/**
	 * Scale texture
	 * @param texture texture
	 * @param width width
	 * @param height height
	 * @param idSuffix id suffix for generated texture
	 * @return texture
	 */
	static Texture* scale(Texture* texture, int width, int height, const string& idSuffix = ":scaled");

	/**
	 * Smooth texture
	 * @param texture texture
	 * @param idSuffix id suffix for generated texture
	 * @param adjacentSampleWeight adjacent sample weight
	 * @return texture
	 */
	static Texture* smooth(Texture* texture, const string& idSuffix = ":smoothed", float adjacentSampleWeight = 0.05f);

private:
	/**
	 * PNG input stream
	 */
	class PNGInputStream {
	public:

		/**
		 * Public constructor
		 * @param data data
		 */
		PNGInputStream(const vector<uint8_t>* data): offset(0), data(data) {
		}

		/**
		 * Destructor
		 */
		~PNGInputStream() {
		}

		/**
		 * Read bytes
		 * @param outBytes out bytes
		 * @param outBytesToRead out bytes to read
		 */
		void readBytes(int8_t* outBytes, int32_t outBytesToRead) {
			for (int32_t i = 0; i < outBytesToRead && offset < data->size(); i++) {
				outBytes[i] = (*data)[offset++];
			}
		}

	private:
		int offset;
		const vector<uint8_t>* data;

	};

	/**
	 * Read PNG data from memory
	 * @param png_ptr png structure
	 * @param outBytes out bytes
	 * @param outBytesToRead out bytes to read
	 */
	static void readPNGDataFromMemory(png_structp png_ptr, png_bytep outBytes, png_size_t outBytesToRead);

	/**
	 * Remove texture from cache
	 * @param texture texture
	 */
	static void removeFromCache(Texture* texture);

	/**
	 * Scales a texture line
	 * @param pixelByteBuffer pixel byte buffer aka original texture
	 * @param pixelByteBufferScaled pixel byte buffer scaled aka new texture, its offset should point to start of line you want to write
	 * @param width orginal width
	 * @param textureWidth new texture width
	 * @param bytesPerPixel bytes per pixel
	 * @param y y position in original image
	 */
	static void scaleTextureLine(const ByteBuffer& pixelByteBuffer, ByteBuffer& pixelByteBufferScaled, int width, int textureWidth, int bytesPerPixel, int y);

	//
	STATIC_DLL_IMPEXT static vector<string> extensions;

	// maybe have a read write lock here for texture cache, but currently I have no multithreaded access to it
	STATIC_DLL_IMPEXT static map<string, Texture*>* textureCache;
	STATIC_DLL_IMPEXT static Mutex* textureCacheMutex;
};

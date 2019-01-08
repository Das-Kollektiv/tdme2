#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>

#include <ext/libpng/png.h>

using std::map;
using std::vector;
using std::string;

using tdme::engine::fileio::textures::Texture;
using tdme::os::filesystem::FileSystemException;

namespace tdme {
namespace engine {
namespace fileio {
namespace textures {

/**
 * PNG input stream
 */
class PNGInputStream {
public:

	/**
	 * Public constructor
	 * @author Andreas Drewke
	 * @version $Id$
	 */
	PNGInputStream(vector<uint8_t>* data) {
		this->offset = 0;
		this->data = data;
	}

	/**
	 * Destructor
	 */
	~PNGInputStream() {
	}

	/**
	 * Read byte
	 * @param outBytes out bytes
	 * @param outBytesToRead out bytes to read
	 */
	void readBytes(int8_t* outBytes, int32_t outBytesToRead) {
		for (int32_t i = 0; i < outBytesToRead && offset < data->size(); i++) {
			outBytes[i] = (*data)[offset++];
		}
	}

private:
	int32_t offset;
	vector<uint8_t>* data;

};

};
};
};
};

/** 
 * Texture loader class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::textures::TextureReader final
{
	friend class Texture;

public:
	/**
	 * @return texture extensions
	 */
	static const vector<string>& getTextureExtensions();

	/** 
	 * Loads a texture
	 * @param pathName path name
	 * @param fileName file name
	 * @param useCache use cache
	 * @return texture data instance or null
	 */
	static Texture* read(const string& pathName, const string& fileName, bool useCache = true);

private:
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
	 * Load PNG
	 * @param path path name
	 * @param fileName file name
	 */
	static Texture* loadPNG(const string& path, const string& fileName) throw (FileSystemException);

	//
	static vector<string> extensions;

	// maybe have a read write lock here for texture cache, but currently I have no multithreaded access to it
	static map<string, Texture*> textureCache;
};

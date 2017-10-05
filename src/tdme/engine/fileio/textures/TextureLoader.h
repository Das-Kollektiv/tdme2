// Generated from /tdme/src/tdme/engine/fileio/textures/TextureLoader.java

#pragma once

#include <string>
#include <vector>

#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>

#include <tdme/os/filesystem/_FileSystemException.h>

#include <ext/libpng/png.h>

using std::vector;
using std::wstring;

using tdme::engine::fileio::textures::Texture;
using tdme::os::filesystem::_FileSystemException;
using tdme::utils::_Console;

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
	 * @param out bytes
	 * @param out bytes to read
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
 * ImageLoader loader class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::fileio::textures::TextureLoader final
{
public:
	/** 
	 * Loads a texture
	 * @param path
	 * @param fileName
	 * @throws _FileSystemException
	 * @return texture data instance or null
	 */
	static Texture* loadTexture(const wstring& path, const wstring& fileName) throw (_FileSystemException);

private:
	/**
	 * Read PNG data from memory
	 * @param png structure
	 * @param out bytes
	 * @param out bytes to read
	 */
	static void readPNGDataFromMemory(png_structp png_ptr, png_bytep outBytes, png_size_t outBytesToRead);

	/**
	 * Load PNG
	 * @param path name
	 * @param file name
	 */
	static Texture* loadPNG(const wstring& path, const wstring& fileName) throw (_FileSystemException);
};

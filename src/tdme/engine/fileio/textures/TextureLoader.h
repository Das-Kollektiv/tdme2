// Generated from /tdme/src/tdme/engine/fileio/textures/TextureLoader.java

#pragma once

#include <java/lang/fwd-tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/os/fwd-tdme.h>
#include <java/lang/Object.h>
#include <Array.h>

#include <tdme/os/_FileSystemException.h>

#include <ext/libpng/png.h>

using java::lang::Object;
using java::lang::String;
using tdme::engine::fileio::textures::Texture;
using tdme::os::_FileSystemException;
using tdme::utils::_Console;

struct default_init_tag;

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
	PNGInputStream(int8_tArray* data) {
		this->offset = 0;
		this->data = data;
	}

	/**
	 * Destructor
	 */
	~PNGInputStream() {
		delete this->data;
	}

	/**
	 * Read byte
	 * @param out bytes
	 * @param out bytes to read
	 */
	void readBytes(int8_t* outBytes, int32_t outBytesToRead) {
		for (int32_t i = 0; i < outBytesToRead && offset < data->length; i++) {
			outBytes[i] = data->get(offset++);
		}
	}

private:
	int32_t offset;
	int8_tArray* data;

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
	: public Object
{

public:
	typedef Object super;

	/** 
	 * Loads a texture
	 * @param path
	 * @param fileName
	 * @throws _FileSystemException
	 * @return texture data instance or null
	 */
	static Texture* loadTexture(String* path, String* fileName) throw (_FileSystemException);

	// Generated
	TextureLoader();
protected:
	TextureLoader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

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
	static Texture* loadPNG(String* path, String* fileName) throw (_FileSystemException);

	//
	virtual ::java::lang::Class* getClass0();
};

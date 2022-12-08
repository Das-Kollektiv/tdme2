#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/os/filesystem/fwd-tdme.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/utilities/ByteBuffer.h>

#include <ext/libpng/png.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::os::filesystem::FileSystemException;
using tdme::utilities::ByteBuffer;

/**
 * PNG texture reader class
 * @author Andreas Drewke
 */
class tdme::engine::fileio::textures::PNGTextureReader final
{
	friend class tdme::engine::Texture;

public:
	/**
	 * Read PNG header from memory
	 * @param data vector data to read PNG from
	 * @param width width
	 * @param height height
	 * @param bytes per pixel
	 * @return success
	 */
	static bool readHeader(const vector<uint8_t>& data, int& width, int& height, uint8_t& bytesPerPixel);

	/**
	 * Read PNG from memory into texture byte buffer
	 * @param data vector data to read PNG from
	 * @param textureByteBuffer texture byte buffer
	 * @return success
	 */
	static bool read(const vector<uint8_t>& data, ByteBuffer& textureByteBuffer);

	/**
	 * Read PNG from memory
	 * @param textureId texture id
	 * @param data vector data to read PNG from
	 * @param powerOfTwo scale image to fit power of two dimensions
	 * @param idPrefix id prefix
	 */
	static Texture* read(const string& textureId, const vector<uint8_t>& data, bool powerOfTwo = true, const string& idPrefix = string());

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
	static void readDataFromMemory(png_structp png_ptr, png_bytep outBytes, png_size_t outBytesToRead);

};

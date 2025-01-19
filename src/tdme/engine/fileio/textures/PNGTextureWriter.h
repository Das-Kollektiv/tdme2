#pragma once

#include <ext/libpng/png.h>

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/utilities/ByteBuffer.h>

using std::string;
using std::vector;

using tdme::engine::Texture;
using tdme::utilities::ByteBuffer;

/**
 * PNG texture writer class
 * @author Andreas Drewke
 */
class tdme::engine::fileio::textures::PNGTextureWriter final
{
	friend class Texture;
private:
	/**
	 * PNG output stream
	 */
	class PNGOutputStream {
	public:

		/**
		 * Public constructor
		 */
		PNGOutputStream(vector<uint8_t>* data): data(data) {
		}

		/**
		 * Destructor
		 */
		~PNGOutputStream() {
		}

		/**
		 * Read byte
		 * @param inBytes in bytes to write
		 * @param inBytesToRead in bytes to read
		 */
		void writeBytes(int8_t* inBytes, int32_t inBytesToRead) {
			for (int32_t i = 0; i < inBytesToRead; i++) {
				data->push_back(inBytes[i]);
			}
		}

	private:
		vector<uint8_t>* data;
	};

	/**
	 * Write PNG data to memory
	 * @param png_ptr png structure
	 * @param inBytes in bytes
	 * @param inBytesToWrite in bytes to write
	 */
	static void writePNGDataToMemory(png_structp png_ptr, png_bytep inBytes, png_size_t inBytesToWrite);

	/**
	 * Flush PNG data
	 * @param png_ptr png structure
	 */
	static void flushPNGDataToMemory(png_structp png_ptr);

public:

	/**
	 * Writes a texture to PNG file
	 * @param texture texture
	 * @param pathName path name
	 * @param fileName file name
	 * @param removeAlphaChannel remove alpha channel
	 * @param flipY flip Y
	 * @returns success
	 */
	static bool write(Texture* texture, const string& pathName, const string& fileName, bool removeAlphaChannel = true, bool flipY = true);

	/**
	 * Writes a texture to PNG using a data vector
	 * @param texture texture
	 * @param pngData PNG data
	 * @param removeAlphaChannel remove alpha channel
	 * @param flipY flip Y
	 * @returns success
	 */
	static bool write(Texture* texture, vector<uint8_t>& pngData, bool removeAlphaChannel = true, bool flipY = true);

	/**
	 * Writes a texture to PNG using a data vector
	 * @param width width
	 * @param height height
	 * @param bytesPerPixel bytes per pixel
	 * @param textureByteBuffer texture RGB byte buffer
	 * @param pngData PNG data
	 * @param removeAlphaChannel remove alpha channel
	 * @returns success
	 */
	static bool write(int width, int height, int bytesPerPixel, const ByteBuffer& textureByteBuffer, vector<uint8_t>& pngData, bool removeAlphaChannel = true, bool flipY = false);

};

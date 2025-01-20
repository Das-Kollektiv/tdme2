#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/fileio/fwd-agui.h>
#include <agui/gui/textures/fwd-agui.h>
#include <agui/os/filesystem/fwd-agui.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/os/threading/Mutex.h>
#include <agui/utilities/ByteBuffer.h>

using std::string;
using std::unordered_map;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace fileio {
	using ::agui::gui::textures::GUITexture;
	using ::agui::os::filesystem::FileSystemException;
	using ::agui::os::threading::Mutex;
	using ::agui::utilities::ByteBuffer;
}
}
}

/**
 * Texture reader class
 * @author Andreas Drewke
 */
class agui::gui::fileio::TextureReader final
{
	friend class ::agui::gui::textures::GUITexture;
	friend class PNGTextureReader;

public:
	/**
	 * @returns texture extensions
	 */
	static const vector<string>& getTextureExtensions();

	/**
	 * Reads a texture
	 * @param pathName path name
	 * @param fileName file name
	 * @param useCache use cache
	 * @param powerOfTwo scale image to fit power of two dimensions
	 * @param idPrefix id prefix
	 * @returns texture data instance or null
	 */
	static GUITexture* read(const string& pathName, const string& fileName, bool useCache = true, bool powerOfTwo = true, const string& idPrefix = string());

	/**
	 * Reads a texture with additional transparency texture
	 * @param texturePathName texture path name
	 * @param textureFileName texture file name
	 * @param transparencyTexturePathName transparency texture path name
	 * @param transparencyTextureFileName transparency texture file name
	 * @param useCache use cache
	 * @param powerOfTwo scale image to fit power of two dimensions
	 * @param idPrefix id prefix
	 * @returns texture data instance or null
	 */
	static GUITexture* read2(const string& texturePathName, const string& textureFileName, const string& transparencyTexturePathName, const string& transparencyTextureFileName, bool useCache = true, bool powerOfTwo = true, const string& idPrefix = string());

	/**
	 * Rotate texture around center
	 * @param texture texture
	 * @param rotation rotation in degree
	 * @param idSuffix id suffix for generated texture
	 * @returns rotation rotation
	 */
	static GUITexture* rotate(GUITexture* texture, float rotation, const string& idSuffix = ":rotated");

	/**
	 * Scale texture
	 * @param texture texture
	 * @param width width
	 * @param height height
	 * @param idSuffix id suffix for generated texture
	 * @returns texture
	 */
	static GUITexture* scale(GUITexture* texture, int width, int height, const string& idSuffix = ":scaled");

	/**
	 * Smooth texture
	 * @param texture texture
	 * @param idSuffix id suffix for generated texture
	 * @param adjacentSampleWeight adjacent sample weight
	 * @returns texture
	 */
	static GUITexture* smooth(GUITexture* texture, const string& idSuffix = ":smoothed", float adjacentSampleWeight = 0.05f);

private:

	/**
	 * Remove texture from cache
	 * @param texture texture
	 */
	static void removeFromCache(GUITexture* texture);

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
	AGUI_STATIC_DLL_IMPEXT static vector<string> extensions;

	// maybe have a read write lock here for texture cache, but currently I have no multithreaded access to it
	AGUI_STATIC_DLL_IMPEXT static unordered_map<string, GUITexture*> textureCache;
	AGUI_STATIC_DLL_IMPEXT static Mutex textureCacheMutex;
};

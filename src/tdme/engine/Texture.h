#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Reference.h>

using std::string;

using tdme::utilities::ByteBuffer;
using tdme::utilities::Reference;

/**
 * Texture entity
 * @author Andreas Drewke
 */
class tdme::engine::Texture final: public Reference
{
public:

	enum TextureDepth {
		TEXTUREDEPTH_UNKNOWN,
		TEXTUREDEPTH_RGB,
		TEXTUREDEPTH_RGBA
	};

	enum TextureFormat {
		TEXTUREFORMAT_UNKNOWN,
		TEXTUREFORMAT_RGB,
		TEXTUREFORMAT_RGBA,
		TEXTUREFORMAT_RGB_PNG,
		TEXTUREFORMAT_RGBA_PNG
	};

	enum ClampMode { CLAMPMODE_EDGE, CLAMPMODE_TRANSPARENTPIXEL };

	/**
	 * Return RGB/A texture depth by bits per pixel
	 * @param bpp bits per pixel
	 * @return RGB/A texture depth by bits per pixel
	 */
	inline static TextureDepth getRGBDepthByPixelBitsPerPixel(int bpp) {
		switch (bpp) {
			case 24: return TEXTUREDEPTH_RGB;
			case 32: return TEXTUREDEPTH_RGBA;
			default: return TEXTUREDEPTH_UNKNOWN;
		}
	}

	/**
	 * Return RGB/A texture depth by bits per pixel
	 * @param bpp bits per pixel
	 * @return RGB/A texture depth by bits per pixel
	 */
	inline static TextureFormat getRGBFormatByPixelBitsPerPixel(int bpp) {
		switch (bpp) {
			case 24: return TEXTUREFORMAT_RGB;
			case 32: return TEXTUREFORMAT_RGBA;
			default: return TEXTUREFORMAT_UNKNOWN;
		}
	}

	/**
	 * Public constructor
	 * @param id id
	 * @param depth depth
	 * @param format texture backing format
	 * @param width width
	 * @param height height
	 * @param textureWidth texture width
	 * @param textureHeight texture height
	 * @param textureDataFormat texture data format
	 * @param textureData texture data
	 */
	inline Texture(
		const string& id,
		TextureDepth depth,
		TextureFormat format,
		uint16_t width, uint16_t height,
		uint16_t textureWidth, uint16_t textureHeight,
		TextureFormat textureDataFormat,
		const ByteBuffer& textureData):
		Reference(),
		id(id),
		depth(depth),
		format(format),
		width(width),
		height(height),
		textureWidth(textureWidth),
		textureHeight(textureHeight),
		useMipMap(true),
		repeat(true),
		clampMode(CLAMPMODE_EDGE),
		atlasSize(1) {
		//
		setTextureData(textureDataFormat, textureData);
	}

	/**
	 * @return id
	 */
	inline const string& getId() const  {
		return id;
	}

	/**
	 * @return depth
	 */
	inline TextureDepth getDepth() {
		return depth;
	}

	/**
	 * @return RGB depth in bits per pixel
	 */
	inline uint8_t getRGBDepthBitsPerPixel() const {
		switch (depth) {
			case TEXTUREDEPTH_RGB: return 24;
			case TEXTUREDEPTH_RGBA: return 32;
		}
		return 0;
	}

	/**
	 * @return image width
	 */
	inline uint16_t getWidth() const {
		return width;
	}

	/**
	 * @return image height
	 */
	inline uint16_t getHeight() const {
		return height;
	}

	/**
	 * @return texture height
	 */
	inline uint16_t getTextureHeight() const {
		return textureHeight;
	}

	/**
	 * @return texture width
	 */
	inline uint16_t getTextureWidth() const {
		return textureWidth;
	}

	/**
	 * @return RGB/RGBA texture data wrapped in a byte buffer
	 */
	inline ByteBuffer getRGBTextureData() {
		return getRGBTextureData(format, textureData);
	}

	/**
	 * Set RGB(A) texture data
	 * @param format texture data format
	 * @param textureData texture data
	 */
	void setTextureData(TextureFormat format, const ByteBuffer& textureData);

	/**
	 * @return backing texture data wrapped in a byte buffer
	 */
	inline ByteBuffer getTextureData() {
		return ByteBuffer(textureData);
	}

	/**
	 * @return use mip map
	 */
	inline bool isUseMipMap() const {
		return useMipMap;
	}

	/**
	 * Set if to use mip map
	 * @param useMipMap mip map enabled
	 */
	inline void setUseMipMap(bool useMipMap) {
		this->useMipMap = useMipMap;
	}

	/**
	 * @return is repeat
	 */
	inline bool isRepeat() const {
		return repeat;
	}

	/**
	 * Set repeat
	 * @param repeat repeat
	 */
	inline void setRepeat(bool repeat) {
		this->repeat = repeat;
	}

	/**
	 * @return clamp mode
	 */
	inline ClampMode getClampMode() const {
		return clampMode;
	}

	/**
	 * Set clamp mode
	 * @param clampMode clamp mode
	 */
	inline void setClampMode(ClampMode clampMode) {
		this->clampMode = clampMode;
	}

	/**
	 * @return atlas size
	 */
	inline uint16_t getAtlasSize() const {
		return atlasSize;
	}

	/**
	 * Set atlas size
	 * @param atlasSize atlas size
	 */
	inline void setAtlasSize(uint16_t atlasSize) {
		this->atlasSize = atlasSize;
	}

	// overridden methods
	virtual void onDelete() override;

private:
	string id;
	TextureDepth depth;
	TextureFormat format;
	uint16_t width;
	uint16_t height;
	uint16_t textureHeight;
	uint16_t textureWidth;
	ByteBuffer textureData;
	bool useMipMap;
	bool repeat;
	ClampMode clampMode;
	uint16_t atlasSize;

	/**
	 * Destructor
	 */
	inline virtual ~Texture() {
	}

	/**
	 * Get RGB/RGBA texture data wrapped in a byte buffer
	 * @param format texture data format
	 * @param textureData texture data
	 * @return RGB/RGBA texture data wrapped in a byte buffer
	 */
	ByteBuffer getRGBTextureData(TextureFormat format, const ByteBuffer& textureData);

};

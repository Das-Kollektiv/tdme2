#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Reference.h>

using std::string;
using std::vector;

using tdme::math::Math;
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
		TEXTUREFORMAT_RGBA_PNG,
		TEXTUREFORMAT_RGB_BC7,
		TEXTUREFORMAT_RGBA_BC7
	};

	enum TextureFilter {
		TEXTUREFILTER_NEAREST,
		TEXTUREFILTER_LINEAR,
		TEXTUREFILTER_NEAREST_MIPMAP_NEAREST,
		TEXTUREFILTER_LINEAR_MIPMAP_NEAREST,
		TEXTUREFILTER_NEAREST_MIPMAP_LINEAR,
		TEXTUREFILTER_LINEAR_MIPMAP_LINEAR
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
	 * Return RGB/A texture format by bits per pixel
	 * @param bpp bits per pixel
	 * @return RGB/A texture format by bits per pixel
	 */
	inline static TextureFormat getRGBFormatByPixelBitsPerPixel(int bpp) {
		switch (bpp) {
			case 24: return TEXTUREFORMAT_RGB;
			case 32: return TEXTUREFORMAT_RGBA;
			default: return TEXTUREFORMAT_UNKNOWN;
		}
	}

	/**
	 * Return PNG RGB/A texture format by bits per pixel
	 * @param bpp bits per pixel
	 * @return PNG RGB/A texture format by bits per pixel
	 */
	inline static TextureFormat getPNGFormatByPixelBitsPerPixel(int bpp) {
		switch (bpp) {
			case 24: return TEXTUREFORMAT_RGB_PNG;
			case 32: return TEXTUREFORMAT_RGBA_PNG;
			default: return TEXTUREFORMAT_UNKNOWN;
		}
	}

	/**
	 * Return BC7 RGB/A texture format by bits per pixel
	 * @param bpp bits per pixel
	 * @return BC7 RGB/A texture format by bits per pixel
	 */
	inline static TextureFormat getBC7FormatByPixelBitsPerPixel(int bpp) {
		switch (bpp) {
			case 24: return TEXTUREFORMAT_RGB_BC7;
			case 32: return TEXTUREFORMAT_RGBA_BC7;
			default: return TEXTUREFORMAT_UNKNOWN;
		}
	}

	/**
	 * Mip Map Texture
	 */
	struct MipMapTexture {
		MipMapTexture(
			TextureFormat format,
			uint16_t width,
			uint16_t height,
			ByteBuffer textureData)
		:
			format(format),
			width(width),
			height(height),
			textureData(textureData)
		{}
		TextureFormat format;
		uint16_t width;
		uint16_t height;
		ByteBuffer textureData;
	};

	// forbid class copy
	FORBID_CLASS_COPY(Texture)

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
		useCompression(true),
		useMipMap(true),
		repeat(true),
		clampMode(CLAMPMODE_EDGE),
		minFilter(TEXTUREFILTER_LINEAR_MIPMAP_LINEAR),
		magFilter(TEXTUREFILTER_LINEAR),
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
	 * @return texture format
	 */
	inline TextureFormat getTextureFormat() const {
		return format;
	}

	/**
	 * @return texture has RGB/RGBA raw texture format
	 */
	inline bool isRGBTextureFormat() const {
		return format == TEXTUREFORMAT_RGBA || format == TEXTUREFORMAT_RGB;
	}

	/**
	 * @return texture has PNG texture format
	 */
	inline bool isPNGTextureFormat() const {
		return format == TEXTUREFORMAT_RGBA_PNG || format == TEXTUREFORMAT_RGB_PNG;
	}

	/**
	 * @return texture has BC7 texture format
	 */
	inline bool isBC7TextureFormat() const {
		return format == TEXTUREFORMAT_RGBA_BC7 || format == TEXTUREFORMAT_RGB_BC7;
	}

	/**
	 * @return RGB/RGBA texture data wrapped in a byte buffer
	 */
	inline ByteBuffer getRGBTextureData() {
		return getRGBTextureData(format, textureData);
	}

	/**
	 * @return BC7 texture data wrapped in a byte buffer
	 */
	ByteBuffer getBC7TextureData();

	/**
	 * Set RGB(A) texture data
	 * @param format texture data format
	 * @param textureData texture data
	 */
	void setTextureData(TextureFormat format, const ByteBuffer& textureData);

	/**
	 * @return backing texture data wrapped in a byte buffer
	 */
	inline ByteBuffer* getTextureData() {
		return &textureData;
	}

	/**
	 * @return is use compression
	 */
	inline bool isUseCompression() const {
		return useCompression;
	}

	/**
	 * Set if to use compression
	 * @param useCompression use compression if available
	 */
	inline void setUseCompression(bool useCompression) {
		this->useCompression = useCompression;
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
	 * @return texture min filter
	 */
	inline TextureFilter getMinFilter() const {
		return minFilter;
	}

	/**
	 * Set texture min filter
	 * @param filter filter
	 */
	inline void setMinFilter(TextureFilter filter) {
		this->minFilter = filter;
	}

	/**
	 * @return texture mag filter
	 */
	inline TextureFilter getMagFilter() const {
		return magFilter;
	}

	/**
	 * Set texture mag filter
	 * @param filter filter
	 */
	inline void setMagFilter(TextureFilter filter) {
		this->magFilter = filter;
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

	/**
	 * @return mip levels
	 */
	inline int getMipLevels() {
		if (useMipMap == false) return 1;
		auto widthMipLevels = 1;
		auto heightMipLevels = 1;
		auto textureWidth = this->textureWidth;
		auto textureHeight = this->textureHeight;
		while (textureWidth > 16) {
			textureWidth/= 2;
			widthMipLevels++;
		}
		while (textureHeight > 16) {
			textureHeight/= 2;
			heightMipLevels++;
		}
		auto mipLevels = Math::min(widthMipLevels, heightMipLevels);
		if (atlasSize > 1) {
			auto borderSize = 32;
			auto maxLevel = 0;
			while (borderSize > 4) {
				maxLevel++;
				borderSize/= 2;
			}
			return Math::min(mipLevels, maxLevel);
		}
		//
		return mipLevels;
	}

	/**
	 * Set mip map textures
	 * @param mipMapTextures mip map textures
	 */
	inline void setMipMapTextures(const vector<MipMapTexture>& mipMapTextures) {
		this->mipMapTextures = mipMapTextures;
	}

	/**
	 * Get mip map textures
	 * @param bc7Encoded bc7 encoded if true or RGB/A if false
	 * @return mip map textures
	 */
	const vector<MipMapTexture>& getMipMapTextures(bool bc7Encoded);

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
	bool useCompression;
	bool useMipMap;
	bool repeat;
	ClampMode clampMode;
	TextureFilter minFilter;
	TextureFilter magFilter;
	uint16_t atlasSize;
	vector<MipMapTexture> mipMapTextures;

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

	/**
	 * Generate mip map texture
	 * @param textureWidth texture width
	 * @param textureHeight texture height
	 * @param bytesPerPixel bytes per pixel
	 * @param textureTextureData texture texture data
	 */
	ByteBuffer generateMipMap(int textureWidth, int textureHeight, int bytesPerPixel, const ByteBuffer& textureTextureData);

};

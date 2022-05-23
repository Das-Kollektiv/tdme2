#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/textures/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/Reference.h>

using std::string;

using tdme::utilities::ByteBuffer;
using tdme::utilities::Reference;

/**
 * Texture entity
 * @author Andreas Drewke
 */
class tdme::engine::fileio::textures::Texture final: public Reference
{
public:

	enum ClampMode { CLAMPMODE_EDGE, CLAMPMODE_TRANSPARENTPIXEL };

	/**
	 * Public constructor
	 * @param id id
	 * @param depth depth
	 * @param width width
	 * @param height height
	 * @param textureWidth texture width
	 * @param textureHeight texture height
	 * @param textureData texture data
	 */
	inline Texture(
		const string& id,
		uint8_t depth,
		uint16_t width, uint16_t height,
		uint16_t textureWidth, uint16_t textureHeight,
		ByteBuffer* textureData):
		Reference(),
		id(id),
		depth(depth),
		width(width),
		height(height),
		textureWidth(textureWidth),
		textureHeight(textureHeight),
		textureData(textureData),
		useMipMap(true),
		repeat(true),
		clampMode(CLAMPMODE_EDGE),
		atlasSize(1) {
		//
	}

	/**
	 * @return id
	 */
	inline const string& getId() const  {
		return id;
	}

	/**
	 * @return depth in bits per pixel
	 */
	inline uint8_t getDepth() const {
		return depth;
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
	 * @return texture data wrapped in a byte buffer
	 */
	inline ByteBuffer* getTextureData() {
		return textureData;
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
	inline virtual void onDelete() override;

private:
	string id;
	uint8_t depth;
	uint16_t width;
	uint16_t height;
	uint16_t textureHeight;
	uint16_t textureWidth;
	ByteBuffer* textureData;
	bool useMipMap;
	bool repeat;
	ClampMode clampMode;
	uint16_t atlasSize;

	/**
	 * Destructor
	 */
	~Texture();
};

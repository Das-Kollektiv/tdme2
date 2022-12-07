#pragma once

#include <tdme/tdme.h>
#include <tdme/engine/Texture.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/ColorTexture.h>
#include <tdme/utilities/ByteBuffer.h>

using tdme::engine::Texture;
using tdme::engine::ColorTexture;
using tdme::utilities::ByteBuffer;

/**
 * Dynamic color texture
 * @author Andreas Drewke
 */
class tdme::engine::DynamicColorTexture final: public ColorTexture
{
public:
	/**
	 * Public constructor
	 * @param width width
	 * @param height height
	 */
	inline DynamicColorTexture(int32_t width, int32_t height): width(width), height(height), colorBufferTextureId(0) {
		//
	}

	/**
	 * Destructor
	 */
	inline virtual ~DynamicColorTexture() {
	}

	/**
	 * @return width
	 */
	inline int32_t getWidth() {
		return width;
	}

	/**
	 * @return height
	 */
	inline int32_t getHeight() {
		return height;
	}

	/**
	 * @return underlying texture, the format is currently RGBA
	 */
	inline Texture* getTexture() {
		return texture;
	}

	/**
	 * @return underlying texture byte buffer, the format is currently RGBA
	 */
	inline ByteBuffer getByteBuffer() {
		return texture->getTextureData();
	}

	/**
	 * Initialize the texture
	 */
	void initialize();

	/**
	 * Disposes the texture
	 */
	void dispose();

	/**
	 * Resize the texture
	 * @param width width
	 * @param height height
	 */
	void reshape(int32_t width, int32_t height);

	/**
	 * Update texture
	 */
	void update();

	// overridden methods
	inline int32_t getColorTextureId() override {
		return colorBufferTextureId;
	}

private:
	STATIC_DLL_IMPEXT static uint32_t counter;

	int32_t width { -1 };
	int32_t height { -1 };
	int32_t colorBufferTextureId { -1 };
	Texture* texture { nullptr };

};

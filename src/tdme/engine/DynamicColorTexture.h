#pragma once

#include <agui/agui.h>
#include <agui/gui/misc/GUIRendererTexture.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/ColorTexture.h>
#include <tdme/engine/Texture.h>
#include <tdme/utilities/ByteBuffer.h>

using agui::gui::misc::GUIRendererTexture;

using tdme::engine::ColorTexture;
using tdme::engine::Texture;
using tdme::utilities::ByteBuffer;

/**
 * Dynamic color texture
 * @author Andreas Drewke
 */
class tdme::engine::DynamicColorTexture final: public ColorTexture
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(DynamicColorTexture)

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
	 * @returns width
	 */
	inline int32_t getWidth() {
		return width;
	}

	/**
	 * @returns height
	 */
	inline int32_t getHeight() {
		return height;
	}

	/**
	 * @returns underlying texture, the format is currently RGBA
	 */
	inline Texture* getTexture() {
		return texture;
	}

	/**
	 * @returns underlying texture byte buffer, the format is currently RGBA
	 */
	inline ByteBuffer* getByteBuffer() {
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

	/**
	 * @returns GUI renderer texture
	 */
	GUIRendererTexture* toGUIRendererTexture() {
		return
			new GUIRendererTexture(
				width,
				height,
				colorBufferTextureId
			);
	}

private:
	STATIC_DLL_IMPEXT static uint32_t counter;

	int32_t width { -1 };
	int32_t height { -1 };
	int32_t colorBufferTextureId { -1 };
	Texture* texture { nullptr };

};

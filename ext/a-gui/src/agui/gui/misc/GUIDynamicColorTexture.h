#pragma once

#include <agui/agui.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/gui/misc/fwd-agui.h>
#include <agui/utilities/ByteBuffer.h>

// namespaces
namespace agui {
namespace gui {
namespace misc {
	using ::agui::gui::textures::GUITexture;
	using ::agui::utilities::ByteBuffer;
}
}
}

/**
 * Dynamic color texture
 * @author Andreas Drewke
 */
class agui::gui::misc::GUIDynamicColorTexture final
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIDynamicColorTexture)

	/**
	 * Public constructor
	 * @param width width
	 * @param height height
	 */
	inline GUIDynamicColorTexture(int32_t width, int32_t height): width(width), height(height), textureId(0) {
		//
	}

	/**
	 * Destructor
	 */
	inline virtual ~GUIDynamicColorTexture() {
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
	inline GUITexture* getTexture() {
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

	/**
	 * @returns texture id
	 */
	inline int32_t getTextureId() {
		return textureId;
	}

private:
	AGUI_STATIC_DLL_IMPEXT static uint32_t counter;

	int32_t width { -1 };
	int32_t height { -1 };
	int32_t textureId { -1 };
	GUITexture* texture { nullptr };

};

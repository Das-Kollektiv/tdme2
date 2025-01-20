#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/misc/fwd-agui.h>

using std::string;

/**
 * GUI renderer texture
 * @author Andreas Drewke
 */
class agui::gui::misc::GUIRendererTexture final
{
public:

private:
	int32_t width;
	int32_t height;
	int32_t textureId;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIRendererTexture)

	/**
	 * Public constructor
	 * @param width width
	 * @param height height
	 * @param colorBufferTextureId color buffer texture id
	 */
	inline GUIRendererTexture(int32_t width, int32_t height, int32_t textureId):
		width(width),
		height(height),
		textureId(textureId) {
		//
	}

	/**
	 * Destructor
	 */
	virtual ~GUIRendererTexture() {}

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
	 * @returns texture id
	 */
	inline int32_t getTextureId() {
		return textureId;
	}

};

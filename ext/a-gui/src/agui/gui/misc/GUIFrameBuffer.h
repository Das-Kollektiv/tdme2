#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/misc/fwd-agui.h>
#include <agui/gui/misc/GUIColorTexture.h>

using std::string;

/**
 * Frame buffer class
 * @author Andreas Drewke
 */
class agui::gui::misc::GUIFrameBuffer final: public ::agui::gui::misc::GUIColorTexture
{
public:

private:
	int32_t width;
	int32_t height;
	int32_t colorBufferTextureId;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIFrameBuffer)

	/**
	 * Public constructor
	 * @param width width
	 * @param height height
	 * @param colorBufferTextureId color buffer texture id
	 */
	inline GUIFrameBuffer(int32_t width, int32_t height, int32_t colorBufferTextureId):
		width(width),
		height(height),
		colorBufferTextureId(colorBufferTextureId) {
		//
	}

	/**
	 * Destructor
	 */
	virtual ~GUIFrameBuffer() {}

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
	 * @return color buffer texture id
	 */
	inline int32_t getColorBufferTextureId() {
		return colorBufferTextureId;
	}

	// overridden methods
	inline int32_t getColorTextureId() override {
		return colorBufferTextureId;
	}

};

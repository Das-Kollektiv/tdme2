#pragma once

#include <vector>

#include <agui/agui.h>
#include <agui/gui/misc/fwd-agui.h>

/**
 * Color texture interface
 * @author Andreas Drewke
 */
struct agui::gui::misc::GUIColorTexture
{
	/**
	 * Destructor
	 */
	inline virtual ~GUIColorTexture() {}

	/**
	 * @return color texture id
	 */
	virtual int32_t getColorTextureId() = 0;

};

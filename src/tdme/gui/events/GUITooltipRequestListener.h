#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUINode;

/**
 * GUI tooltip request listener
 * @author Andreas Drewke
 */
struct tdme::gui::events::GUITooltipRequestListener
{
	/**
	 * Destructor
	 */
	virtual ~GUITooltipRequestListener() {}

	/**
	 * On tooltip show request
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 */
	virtual void onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) = 0;

	/**
	 * On tooltip close request
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 */
	virtual void onTooltipCloseRequest() = 0;

};

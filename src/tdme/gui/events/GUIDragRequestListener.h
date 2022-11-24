#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUIElementNode;

/**
 * GUI drag request listener
 * @author Andreas Drewke
 */
struct tdme::gui::events::GUIDragRequestListener
{
	/**
	 * Destructor
	 */
	virtual ~GUIDragRequestListener() {}

	/**
	 * On tooltip show request
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 */
	virtual void onDragRequest(GUIElementNode* node, int mouseX, int mouseY) = 0;

};

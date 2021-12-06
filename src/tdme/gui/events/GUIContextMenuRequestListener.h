#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUIElementNode;

/**
 * GUI context menu request listener
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::events::GUIContextMenuRequestListener
{
	/**
	 * Destructor
	 */
	virtual ~GUIContextMenuRequestListener() {}

	/**
	 * On mouse over
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 */
	virtual void onContextMenuRequested(GUIElementNode* node, int mouseX, int mouseY) = 0;
};

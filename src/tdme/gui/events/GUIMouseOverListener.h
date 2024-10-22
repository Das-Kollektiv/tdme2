#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUIElementNode;

/**
 * GUI mouse over listener
 * @author Andreas Drewke
 */
struct tdme::gui::events::GUIMouseOverListener
{
	/**
	 * Destructor
	 */
	virtual ~GUIMouseOverListener() {}

	/**
	 * On mouse over
	 * @param node node
	 */
	virtual void onMouseOver(GUIElementNode* node) = 0;
};

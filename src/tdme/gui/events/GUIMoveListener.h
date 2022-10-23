#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUINode;

/**
 * GUI move listener interface
 * @author Andreas Drewke
 */
struct tdme::gui::events::GUIMoveListener
{

	/**
	 * Destructor
	 */
	virtual ~GUIMoveListener() {}

	/**
	 * On moved
	 * @param node node
	 */
	virtual void onMoved(GUINode* node) = 0;
};

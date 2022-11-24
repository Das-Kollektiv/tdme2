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
	 * On move
	 * @param node node
	 */
	virtual void onMove(GUINode* node) = 0;

	/**
	 * On release
	 * @param node node
	 * @param mouseX unscaled mouse x
	 * @param mouseY unscaled mouse y
	 */
	virtual void onRelease(GUINode* node, int mouseX, int mouseY) = 0;

};

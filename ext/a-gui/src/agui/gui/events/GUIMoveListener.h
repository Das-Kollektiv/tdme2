#pragma once

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>

// namespaces
namespace agui {
namespace gui {
namespace events {
	using ::agui::gui::nodes::GUINode;
}
}
}

/**
 * GUI move listener interface
 * @author Andreas Drewke
 * TODO: seems like we can switch here to GUIElementNode instead of GUINode
 */
struct agui::gui::events::GUIMoveListener
{

	/**
	 * Destructor
	 */
	virtual ~GUIMoveListener() {}

	/**
	 * Accept move
	 * @param node node
	 * @returns if node has been accepted for move
	 */
	virtual bool accept(GUINode* node) = 0;

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

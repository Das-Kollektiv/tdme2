#pragma once

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>

// namespaces
namespace agui {
namespace gui {
namespace events {
	using ::agui::gui::nodes::GUIElementNode;
}
}
}

/**
 * GUI drag request listener
 * @author Andreas Drewke
 */
struct agui::gui::events::GUIDragRequestListener
{
	/**
	 * Destructor
	 */
	virtual ~GUIDragRequestListener() {}

	/**
	 * On drag request
	 * @param node node
	 * @param mouseX unscaled mouse X position
	 * @param mouseY unscaled mouse Y position
	 */
	virtual void onDragRequest(GUIElementNode* node, int mouseX, int mouseY) = 0;

};

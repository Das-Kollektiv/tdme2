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
 * GUI tooltip request listener
 * @author Andreas Drewke
 */
struct agui::gui::events::GUITooltipRequestListener
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

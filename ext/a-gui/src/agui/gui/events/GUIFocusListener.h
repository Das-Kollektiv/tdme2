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
 * GUI focus listener interface
 * @author Andreas Drewke
 */
struct agui::gui::events::GUIFocusListener
{

	/**
	 * Destructor
	 */
	virtual ~GUIFocusListener() {}

	/**
	 * On focus
	 * @param node node
	 */
	virtual void onFocus(GUIElementNode* node) = 0;

	/**
	 * On unfocus
	 * @param node node
	 */
	virtual void onUnfocus(GUIElementNode* node) = 0;

};

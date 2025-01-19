#pragma once

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>

// namespaces
namespace agui {
namespace gui {
namespace events {
	using ::agui::gui::nodes::GUIElementNode;
	enum GUIActionListenerType {
		PERFORMED,
		PERFORMING
	};
}
}
}

/**
 * GUI action listener interface
 * @author Andreas Drewke
 */
struct agui::gui::events::GUIActionListener
{
	/**
	 * Destructor
	 */
	virtual ~GUIActionListener() {}

	/**
	 * On action
	 * @param type type
	 * @param node element node
	 */
	virtual void onAction(GUIActionListenerType type, GUIElementNode* node) = 0;
};

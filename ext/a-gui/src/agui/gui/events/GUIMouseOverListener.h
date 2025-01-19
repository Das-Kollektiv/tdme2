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
 * GUI mouse over listener
 * @author Andreas Drewke
 */
struct agui::gui::events::GUIMouseOverListener
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

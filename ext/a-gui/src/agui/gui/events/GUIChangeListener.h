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
 * GUI change listener interface
 * @author Andreas Drewke
 */
struct agui::gui::events::GUIChangeListener
{

	/**
	 * Destructor
	 */
	virtual ~GUIChangeListener() {}

	/**
	 * On change
	 * @param node node
	 */
	virtual void onChange(GUIElementNode* node) = 0;
};

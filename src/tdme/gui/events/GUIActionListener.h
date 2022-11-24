#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::nodes::GUIElementNode;

namespace tdme {
namespace gui {
namespace events {
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
struct tdme::gui::events::GUIActionListener
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

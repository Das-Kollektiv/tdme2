#pragma once

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIElementController.h>

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::nodes::GUIElementController;
	using ::agui::gui::nodes::GUINode;
}
}
}

/**
 * GUI button controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIButtonController final
	: public GUIElementController
{
	friend class GUIButton;
	friend class GUIImageButton;

private:
	// forbid class copy
	FORBID_CLASS_COPY(GUIButtonController)

	/**
	 * Constructor
	 */
	GUIButtonController(GUINode* node);
};

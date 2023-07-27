#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>

using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUINode;

/**
 * GUI button controller
 * @author Andreas Drewke
 */
class tdme::gui::elements::GUIButtonController final
	: public GUIElementController
{
	friend class GUIButton;
	friend class GUIImageButton;

private:
	// forbid class copy
	CLASS_FORBID_COPY(GUIButtonController)

	/**
	 * Constructor
	 */
	GUIButtonController(GUINode* node);
};

#pragma once

#include <tdme/gui/elements/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIElementController.h>

using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUINode;

/** 
 * GUI button controller
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::elements::GUIButtonController final
	: public GUIElementController
{

public: /* protected */
	GUIButtonController(GUINode* node);
};

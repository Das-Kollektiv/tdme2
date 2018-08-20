#pragma once

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>

using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;

/** 
 * GUI action listener
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::events::GUIActionListener
{

	/** 
	 * On action performed
	 * @param type type
	 * @param node element node
	 */
	virtual void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) = 0;
};

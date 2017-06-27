// Generated from /tdme/src/tdme/gui/events/GUIActionListener.java

#pragma once

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;



/** 
 * GUI action listener
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::events::GUIActionListener
	: public virtual Object
{

	/** 
	 * On action performed
	 * @param element node
	 */
	virtual void onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

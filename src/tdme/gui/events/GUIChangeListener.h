// Generated from /tdme/src/tdme/gui/events/GUIChangeListener.java

#pragma once

#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::gui::nodes::GUIElementNode;



/** 
 * GUI change listener
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::events::GUIChangeListener
	: public virtual Object
{

	/** 
	 * On value changed
	 * @param node
	 */
	virtual void onValueChanged(GUIElementNode* node) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

// Generated from /tdme/src/tdme/gui/events/Action.java

#pragma once

#include <tdme/gui/events/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;



/** 
 * Action Interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::events::Action
	: public virtual Object
{

	/** 
	 * Perform action
	 */
	virtual void performAction() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

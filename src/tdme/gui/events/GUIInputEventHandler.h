// Generated from /tdme/src/tdme/gui/events/GUIInputEventHandler.java

#pragma once

#include <tdme/gui/events/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;



/** 
 * GUI input event handler
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::gui::events::GUIInputEventHandler
	: public virtual Object
{

	/** 
	 * Handle input events that have not yet been processed
	 */
	virtual void handleInputEvents() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

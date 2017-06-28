// Generated from /tdme/src/tdme/tools/shared/views/View.java

#pragma once

#include <tdme/tools/shared/views/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;

/** 
 * View interface, this combines application logic, regarding a application view, with screen controllers
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::tools::shared::views::View
	: public virtual Object
{

	/** 
	 * Initiates the view
	 */
	virtual void initialize() = 0;

	/** 
	 * Activate view
	 */
	virtual void activate() = 0;

	/** 
	 * Renders the view
	 */
	virtual void display() = 0;

	/** 
	 * Deactivate view
	 */
	virtual void deactivate() = 0;

	/** 
	 * Disposes the view
	 */
	virtual void dispose() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

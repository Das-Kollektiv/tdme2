// Generated from /tdme/src/tdme/engine/EntityPickingFilter.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::Entity;



/** 
 * Entity picking filter
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::EntityPickingFilter
	: public virtual Object
{

	/** 
	 * Filter entity
	 * @param entity
	 * @return if allowed or not
	 */
	virtual bool filterEntity(Entity* entity) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

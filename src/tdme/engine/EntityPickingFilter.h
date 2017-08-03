// Generated from /tdme/src/tdme/engine/EntityPickingFilter.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>

using tdme::engine::Entity;

/** 
 * Entity picking filter
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::EntityPickingFilter
{

	/** 
	 * Filter entity
	 * @param entity
	 * @return if allowed or not
	 */
	virtual bool filterEntity(Entity* entity) = 0;
};

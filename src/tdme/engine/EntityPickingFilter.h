#pragma once

#include <tdme.h>
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

	/**
	 * Destructor
	 */
	virtual ~EntityPickingFilter() {};
};

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>

#include <tdme/utils/VectorIteratorMultiple.h>

using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;

/** 
 * Partition interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::Partition
{
	/** 
	 * Reset
	 */
	virtual void reset() = 0;

	/** 
	 * Adds a entity
	 * @param entity entity
	 */
	virtual void addEntity(Entity* entity) = 0;

	/** 
	 * Updates a entity
	 * @param entity entity
	 */
	virtual void updateEntity(Entity* entity) = 0;

	/** 
	 * Removes a entity
	 * @param entity entity
	 */
	virtual void removeEntity(Entity* entity) = 0;

	/** 
	 * Get visible entities
	 * @param frustum frustum
	 * @return visible entities
	 */
	virtual const vector<Entity*>& getVisibleEntities(Frustum* frustum) = 0;

	/**
	 * Destructor
	 */
	virtual ~Partition() {}
};

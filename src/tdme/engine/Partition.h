#pragma once

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>

using std::vector;

using tdme::engine::Entity;
using tdme::engine::Frustum;

/**
 * Partition interface
 * @author Andreas Drewke
 */
struct tdme::engine::Partition
{
	/**
	 * Destructor
	 */
	virtual ~Partition() {}

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
	 * @returns visible entities
	 */
	virtual const vector<Entity*>& getVisibleEntities(Frustum* frustum) = 0;

	/**
	 * Check if entity is visible
	 * @param frustum frustum
	 * @param entity entity
	 * @returns if entity has been determined to be visible by last getVisibleEntities() call
	 */
	virtual bool isVisibleEntity(Entity* entity) = 0;

};

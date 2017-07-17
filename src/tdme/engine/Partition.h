// Generated from /tdme/src/tdme/engine/Partition.java

#pragma once

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <java/lang/Object.h>

#include <tdme/utils/ArrayListIteratorMultiple.h>

using java::lang::Object;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::ArrayListIteratorMultiple;
using tdme::utils::_ArrayList;


struct default_init_tag;

/** 
 * PartitionQuadTree interface
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Partition
	: public virtual Object
{

public:
	typedef Object super;

public: /* protected */

	/** 
	 * Reset
	 */
	virtual void reset() = 0;

	/** 
	 * Adds a entity
	 * @param entity
	 */
	virtual void addEntity(Entity* entity) = 0;

	/** 
	 * Updates a entity
	 * @param entity
	 */
	virtual void updateEntity(Entity* entity) = 0;

	/** 
	 * Removes a entity
	 * @param entity
	 */
	virtual void removeEntity(Entity* entity) = 0;

public:

	/** 
	 * Get visible entities
	 * @param frustum
	 * @return visible entities
	 */
	virtual const vector<Entity*>* getVisibleEntities(Frustum* frustum) = 0;

	/** 
	 * Get objects near to bounding volume
	 * @param cbv
	 * @return objects near to cbv
	 */
	virtual ArrayListIteratorMultiple<Entity*>* getObjectsNearTo(BoundingVolume* cbv) = 0;

	/** 
	 * Get objects near to given world position
	 * @param center
	 * @return objects near to given world position
	 */
	virtual ArrayListIteratorMultiple<Entity*>* getObjectsNearTo(Vector3* center) = 0;

	// Generated
	Partition();
protected:
	Partition(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

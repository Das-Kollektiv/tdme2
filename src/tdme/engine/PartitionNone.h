#pragma once

#include <vector>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Partition.h>
#include <tdme/utils/VectorIteratorMultiple.h>

using std::vector;

using tdme::engine::Partition;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;

/** 
 * PartitionQuadTree none implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::PartitionNone final
	: public Partition
{
private:
	vector<Entity*> entities;
	VectorIteratorMultiple<Entity*> arrayListIteratorMultiple;

private:
	void reset() override;
	void addEntity(Entity* entity) override;
	void updateEntity(Entity* entity) override;
	void removeEntity(Entity* entity) override;

public:
	const vector<Entity*>* getVisibleEntities(Frustum* frustum) override;
	VectorIteratorMultiple<Entity*>* getObjectsNearTo(BoundingVolume* cbv) override;
	VectorIteratorMultiple<Entity*>* getObjectsNearTo(const Vector3& center, const Vector3& halfExtension = Vector3(0.1f, 0.1f, 0.1f)) override;

	/**
	 * Public constructor
	 */
	PartitionNone();
};

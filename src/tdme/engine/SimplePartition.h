#pragma once

#include <vector>

#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Partition.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>
#include <tdme/utilities/VectorIteratorMultiple.h>

using std::vector;

using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Entity;
using tdme::engine::Frustum;
using tdme::engine::Partition;
using tdme::math::Vector3;
using tdme::utilities::VectorIteratorMultiple;

/**
 * Bogus/Simple partition implementation
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::SimplePartition final: public Partition
{
private:
	vector<Entity*> entities;
	VectorIteratorMultiple<Entity*> arrayListIteratorMultiple;

private:
	// overridden methods
	void reset() override;
	void addEntity(Entity* entity) override;
	void updateEntity(Entity* entity) override;
	void removeEntity(Entity* entity) override;

public:
	/**
	 * Public constructor
	 */
	SimplePartition();

	// overridden methods
	const vector<Entity*>& getVisibleEntities(Frustum* frustum) override;
	bool isVisibleEntity(Entity* entity) override;

};
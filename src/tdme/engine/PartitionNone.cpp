#include <tdme/engine/PartitionNone.h>

#include <vector>

#include <tdme/engine/Entity.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>

using std::vector;

using tdme::engine::PartitionNone;
using tdme::engine::Entity;
using tdme::utils::ArrayListIteratorMultiple;

PartitionNone::PartitionNone() 
{
	arrayListIteratorMultiple.addArrayList(&entities);
}

void PartitionNone::reset()
{
}

void PartitionNone::addEntity(Entity* entity)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities.at(i) == entity) return;
	}

	entities.push_back(entity);
}

void PartitionNone::updateEntity(Entity* entity)
{
}

void PartitionNone::removeEntity(Entity* entity)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities.at(i) == entity) {
			entities.erase(entities.begin() + i);
			return;
		}
	}
}

const vector<Entity*>* PartitionNone::getVisibleEntities(Frustum* frustum)
{
	return &entities;
}

ArrayListIteratorMultiple<Entity*>* PartitionNone::getObjectsNearTo(BoundingVolume* cbv)
{
	return &arrayListIteratorMultiple;
}

ArrayListIteratorMultiple<Entity*>* PartitionNone::getObjectsNearTo(const Vector3& center)
{
	return &arrayListIteratorMultiple;
}

#include <tdme/engine/SimplePartition.h>

#include <algorithm>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/Entity.h>

using std::find;
using std::vector;

using tdme::engine::Entity;
using tdme::engine::SimplePartition;

SimplePartition::SimplePartition()
{
}

void SimplePartition::reset()
{
	entities.clear();
}

void SimplePartition::addEntity(Entity* entity)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == entity) return;
	}

	entities.push_back(entity);
}

void SimplePartition::updateEntity(Entity* entity)
{
}

void SimplePartition::removeEntity(Entity* entity)
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == entity) {
			entities.erase(entities.begin() + i);
			return;
		}
	}
}

const vector<Entity*>& SimplePartition::getVisibleEntities(Frustum* frustum)
{
	return entities;
}

bool SimplePartition::isVisibleEntity(Entity* entity) {
	return find(entities.begin(), entities.end(), entity) != entities.end();
}

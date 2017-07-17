// Generated from /tdme/src/tdme/engine/PartitionNone.java
#include <tdme/engine/PartitionNone.h>

#include <vector>

#include <java/lang/Object.h>
#include <tdme/engine/Entity.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>
#include <tdme/utils/_ArrayList.h>

using std::vector;

using tdme::engine::PartitionNone;
using java::lang::Object;
using tdme::engine::Entity;
using tdme::utils::ArrayListIteratorMultiple;
using tdme::utils::_ArrayList;

PartitionNone::PartitionNone(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PartitionNone::PartitionNone() 
	: PartitionNone(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void PartitionNone::init()
{
}

void PartitionNone::ctor()
{
	super::ctor();
	init();
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

ArrayListIteratorMultiple<Entity*>* PartitionNone::getObjectsNearTo(Vector3* center)
{
	return &arrayListIteratorMultiple;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PartitionNone::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.PartitionNone", 25);
    return c;
}

java::lang::Class* PartitionNone::getClass0()
{
	return class_();
}


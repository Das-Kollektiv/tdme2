// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionNone.java
#include <tdme/engine/physics/PhysicsPartitionNone.h>

#include <vector>
#include <algorithm>

#include <java/lang/Object.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>

using std::find;
using std::vector;
using std::remove;

using tdme::engine::physics::PhysicsPartitionNone;
using java::lang::Object;
using tdme::engine::physics::RigidBody;
using tdme::utils::ArrayListIteratorMultiple;

PhysicsPartitionNone::PhysicsPartitionNone(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PhysicsPartitionNone::PhysicsPartitionNone() 
	: PhysicsPartitionNone(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void PhysicsPartitionNone::init()
{
	arrayListIteratorMultiple.addArrayList(&bodies);
}

void PhysicsPartitionNone::ctor()
{
	super::ctor();
	init();
}

void PhysicsPartitionNone::reset()
{
}

void PhysicsPartitionNone::addRigidBody(RigidBody* rigidBody)
{
	if (find(bodies.begin(), bodies.end(), rigidBody) != bodies.end()) return;
	bodies.push_back(rigidBody);
}

void PhysicsPartitionNone::updateRigidBody(RigidBody* rigidBody)
{
}

void PhysicsPartitionNone::removeRigidBody(RigidBody* rigidBody)
{
	bodies.erase(remove(bodies.begin(), bodies.end(), rigidBody), bodies.end());
}

ArrayListIteratorMultiple<RigidBody*>* PhysicsPartitionNone::getObjectsNearTo(BoundingVolume* cbv)
{
	return &arrayListIteratorMultiple;
}

ArrayListIteratorMultiple<RigidBody*>* PhysicsPartitionNone::getObjectsNearTo(Vector3* center)
{
	return &arrayListIteratorMultiple;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsPartitionNone::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.PhysicsPartitionNone", 40);
    return c;
}

java::lang::Class* PhysicsPartitionNone::getClass0()
{
	return class_();
}


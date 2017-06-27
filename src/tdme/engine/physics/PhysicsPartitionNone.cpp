// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionNone.java
#include <tdme/engine/physics/PhysicsPartitionNone.h>

#include <java/lang/Object.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>
#include <tdme/utils/_ArrayList.h>

using tdme::engine::physics::PhysicsPartitionNone;
using java::lang::Object;
using tdme::engine::physics::RigidBody;
using tdme::utils::ArrayListIteratorMultiple;
using tdme::utils::_ArrayList;

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
	bodies = new _ArrayList();
	arrayListIteratorMultiple = new ArrayListIteratorMultiple();
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
	if (bodies->contains(rigidBody))
		return;

	bodies->add(rigidBody);
}

void PhysicsPartitionNone::updateRigidBody(RigidBody* rigidBody)
{
}

void PhysicsPartitionNone::removeRigidBody(RigidBody* rigidBody)
{
	bodies->remove(static_cast< Object* >(rigidBody));
}

ArrayListIteratorMultiple* PhysicsPartitionNone::getObjectsNearTo(BoundingVolume* cbv)
{
	arrayListIteratorMultiple->clear();
	arrayListIteratorMultiple->addArrayList(bodies);
	return arrayListIteratorMultiple;
}

ArrayListIteratorMultiple* PhysicsPartitionNone::getObjectsNearTo(Vector3* center)
{
	arrayListIteratorMultiple->clear();
	arrayListIteratorMultiple->addArrayList(bodies);
	return arrayListIteratorMultiple;
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


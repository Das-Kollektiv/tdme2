// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionNone.java
#include <tdme/engine/physics/PhysicsPartitionNone.h>

#include <vector>
#include <algorithm>

#include <tdme/engine/physics/RigidBody.h>
#include <tdme/utils/ArrayListIteratorMultiple.h>

using std::find;
using std::vector;
using std::remove;

using tdme::engine::physics::PhysicsPartitionNone;
using java::lang::Object;
using tdme::engine::physics::RigidBody;
using tdme::utils::ArrayListIteratorMultiple;

PhysicsPartitionNone::PhysicsPartitionNone() 
{
	arrayListIteratorMultiple.addArrayList(&bodies);
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

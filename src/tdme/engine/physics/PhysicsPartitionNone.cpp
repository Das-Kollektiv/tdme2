#include <tdme/engine/physics/PhysicsPartitionNone.h>

#include <vector>
#include <algorithm>

#include <tdme/engine/physics/RigidBody.h>
#include <tdme/utils/VectorIteratorMultiple.h>

using std::find;
using std::vector;
using std::remove;

using tdme::engine::physics::PhysicsPartitionNone;
using tdme::engine::physics::RigidBody;
using tdme::utils::VectorIteratorMultiple;

PhysicsPartitionNone::PhysicsPartitionNone() 
{
	arrayListIteratorMultiple.addVector(&bodies);
}

void PhysicsPartitionNone::reset()
{
	bodies.clear();
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

VectorIteratorMultiple<RigidBody*>* PhysicsPartitionNone::getObjectsNearTo(BoundingVolume* cbv)
{
	return &arrayListIteratorMultiple;
}

VectorIteratorMultiple<RigidBody*>* PhysicsPartitionNone::getObjectsNearTo(const Vector3& center)
{
	return &arrayListIteratorMultiple;
}

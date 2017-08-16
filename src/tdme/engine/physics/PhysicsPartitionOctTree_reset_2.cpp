// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java
#include <tdme/engine/physics/PhysicsPartitionOctTree_reset_2.h>

#include <tdme/engine/physics/PhysicsPartitionOctTree.h>
#include <tdme/engine/primitives/BoundingBox.h>

using tdme::engine::physics::PhysicsPartitionOctTree_reset_2;
using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::engine::primitives::BoundingBox;

PhysicsPartitionOctTree_reset_2::PhysicsPartitionOctTree_reset_2()
{
}

BoundingBox* PhysicsPartitionOctTree_reset_2::instantiate()
{
	return new BoundingBox();
}

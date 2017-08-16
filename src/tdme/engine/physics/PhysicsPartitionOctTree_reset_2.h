// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java

#pragma once

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/primitives/BoundingBox.h>

using tdme::utils::Pool;
using tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::engine::primitives::BoundingBox;

class tdme::engine::physics::PhysicsPartitionOctTree_reset_2
	: public Pool<BoundingBox*>
{

public: /* protected */
	BoundingBox* instantiate() override;

	// Generated

public:
	PhysicsPartitionOctTree_reset_2();
};

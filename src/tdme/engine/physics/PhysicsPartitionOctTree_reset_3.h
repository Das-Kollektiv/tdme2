// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java

#pragma once

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree_PartitionTreeNode.h>

using tdme::utils::Pool;
using tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::PhysicsPartitionOctTree;


struct default_init_tag;
class tdme::engine::physics::PhysicsPartitionOctTree_reset_3
	: public Pool<PhysicsPartitionOctTree_PartitionTreeNode*>
{

public:
	typedef Pool super;

public: /* protected */
	PhysicsPartitionOctTree_PartitionTreeNode* instantiate() override;

	// Generated

public:
	PhysicsPartitionOctTree_reset_3(PhysicsPartitionOctTree *PhysicsPartitionOctTree_this);
	static ::java::lang::Class *class_();
	PhysicsPartitionOctTree *PhysicsPartitionOctTree_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class PhysicsPartitionOctTree;
	friend class PhysicsPartitionOctTree_PartitionTreeNode;
	friend class PhysicsPartitionOctTree_reset_1;
	friend class PhysicsPartitionOctTree_reset_2;
	friend class PhysicsPartitionOctTree_reset_4;
	friend class PhysicsPartitionOctTree_reset_5;
	friend class PhysicsPartitionOctTree_reset_6;
};

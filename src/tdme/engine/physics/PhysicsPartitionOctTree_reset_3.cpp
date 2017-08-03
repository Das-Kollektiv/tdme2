// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java
#include <tdme/engine/physics/PhysicsPartitionOctTree_reset_3.h>

#include <tdme/engine/physics/PhysicsPartitionOctTree_PartitionTreeNode.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree.h>

using tdme::engine::physics::PhysicsPartitionOctTree_reset_3;
using tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode;
using tdme::engine::physics::PhysicsPartitionOctTree;

PhysicsPartitionOctTree_reset_3::PhysicsPartitionOctTree_reset_3(PhysicsPartitionOctTree *PhysicsPartitionOctTree_this)
	: super()
	, PhysicsPartitionOctTree_this(PhysicsPartitionOctTree_this)
{
	ctor();
}

PhysicsPartitionOctTree_PartitionTreeNode* PhysicsPartitionOctTree_reset_3::instantiate()
{
	return new PhysicsPartitionOctTree_PartitionTreeNode();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsPartitionOctTree_reset_3::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PhysicsPartitionOctTree_reset_3::getClass0()
{
	return class_();
}


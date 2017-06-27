// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java
#include <tdme/engine/physics/PhysicsPartitionOctTree_PartitionTreeNode.h>

using tdme::engine::physics::PhysicsPartitionOctTree_PartitionTreeNode;
PhysicsPartitionOctTree_PartitionTreeNode::PhysicsPartitionOctTree_PartitionTreeNode(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PhysicsPartitionOctTree_PartitionTreeNode::PhysicsPartitionOctTree_PartitionTreeNode()
	: PhysicsPartitionOctTree_PartitionTreeNode(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsPartitionOctTree_PartitionTreeNode::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.PhysicsPartitionOctTree.PartitionTreeNode", 61);
    return c;
}

java::lang::Class* PhysicsPartitionOctTree_PartitionTreeNode::getClass0()
{
	return class_();
}


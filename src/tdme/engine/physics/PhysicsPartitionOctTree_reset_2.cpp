// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java
#include <tdme/engine/physics/PhysicsPartitionOctTree_reset_2.h>

#include <tdme/engine/physics/PhysicsPartitionOctTree.h>
#include <tdme/engine/primitives/BoundingBox.h>

using tdme::engine::physics::PhysicsPartitionOctTree_reset_2;
using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::engine::primitives::BoundingBox;

PhysicsPartitionOctTree_reset_2::PhysicsPartitionOctTree_reset_2(PhysicsPartitionOctTree *PhysicsPartitionOctTree_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, PhysicsPartitionOctTree_this(PhysicsPartitionOctTree_this)
{
	clinit();
	ctor();
}

BoundingBox* PhysicsPartitionOctTree_reset_2::instantiate()
{
	return new BoundingBox();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsPartitionOctTree_reset_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PhysicsPartitionOctTree_reset_2::getClass0()
{
	return class_();
}


// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java
#include <tdme/engine/physics/PhysicsPartitionOctTree_reset_6.h>

#include <tdme/engine/physics/PhysicsPartitionOctTree.h>
#include <tdme/utils/Key.h>

using tdme::engine::physics::PhysicsPartitionOctTree_reset_6;
using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::utils::Key;

PhysicsPartitionOctTree_reset_6::PhysicsPartitionOctTree_reset_6(PhysicsPartitionOctTree *PhysicsPartitionOctTree_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, PhysicsPartitionOctTree_this(PhysicsPartitionOctTree_this)
{
	clinit();
	ctor();
}

Key* PhysicsPartitionOctTree_reset_6::instantiate()
{
	return new Key();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsPartitionOctTree_reset_6::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PhysicsPartitionOctTree_reset_6::getClass0()
{
	return class_();
}


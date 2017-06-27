// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java
#include <tdme/engine/physics/PhysicsPartitionOctTree_reset_5.h>

#include <tdme/engine/physics/PhysicsPartitionOctTree.h>
#include <tdme/utils/_ArrayList.h>

using tdme::engine::physics::PhysicsPartitionOctTree_reset_5;
using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::utils::_ArrayList;

PhysicsPartitionOctTree_reset_5::PhysicsPartitionOctTree_reset_5(PhysicsPartitionOctTree *PhysicsPartitionOctTree_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, PhysicsPartitionOctTree_this(PhysicsPartitionOctTree_this)
{
	clinit();
	ctor();
}

_ArrayList* PhysicsPartitionOctTree_reset_5::instantiate()
{
	return new _ArrayList();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsPartitionOctTree_reset_5::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PhysicsPartitionOctTree_reset_5::getClass0()
{
	return class_();
}


// Generated from /tdme/src/tdme/engine/physics/PhysicsPartitionOctTree.java
#include <tdme/engine/physics/PhysicsPartitionOctTree_reset_1.h>

#include <tdme/engine/physics/PhysicsPartitionOctTree.h>
#include <tdme/utils/_ArrayList.h>

using tdme::engine::physics::PhysicsPartitionOctTree_reset_1;
using tdme::engine::physics::PhysicsPartitionOctTree;
using tdme::utils::_ArrayList;

PhysicsPartitionOctTree_reset_1::PhysicsPartitionOctTree_reset_1(PhysicsPartitionOctTree *PhysicsPartitionOctTree_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, PhysicsPartitionOctTree_this(PhysicsPartitionOctTree_this)
{
	clinit();
	ctor();
}

_ArrayList* PhysicsPartitionOctTree_reset_1::instantiate()
{
	return new _ArrayList();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsPartitionOctTree_reset_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* PhysicsPartitionOctTree_reset_1::getClass0()
{
	return class_();
}


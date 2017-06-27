// Generated from /tdme/src/tdme/engine/physics/PhysicsPartition.java
#include <tdme/engine/physics/PhysicsPartition.h>

using tdme::engine::physics::PhysicsPartition;
PhysicsPartition::PhysicsPartition(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

PhysicsPartition::PhysicsPartition()
	: PhysicsPartition(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* PhysicsPartition::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.PhysicsPartition", 36);
    return c;
}

java::lang::Class* PhysicsPartition::getClass0()
{
	return class_();
}


// Generated from /tdme/src/tdme/engine/physics/World.java
#include <tdme/engine/physics/World_2.h>

#include <tdme/engine/physics/World.h>
#include <tdme/utils/Key.h>

using tdme::engine::physics::World_2;
using tdme::engine::physics::World;
using tdme::utils::Key;

World_2::World_2(World *World_this)
	: super()
	, World_this(World_this)
{
	ctor();
}

Key* World_2::instantiate()
{
	return new Key();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* World_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* World_2::getClass0()
{
	return class_();
}


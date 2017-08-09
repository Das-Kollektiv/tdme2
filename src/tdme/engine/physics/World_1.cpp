// Generated from /tdme/src/tdme/engine/physics/World.java
#include <tdme/engine/physics/World_1.h>

#include <tdme/engine/physics/World.h>
#include <tdme/utils/Key.h>

using tdme::engine::physics::World_1;
using tdme::engine::physics::World;
using tdme::utils::Key;

World_1::World_1(World *World_this)
	: super()
	, World_this(World_this)
{
}

Key* World_1::instantiate()
{
	return new Key();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* World_1::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* World_1::getClass0()
{
	return class_();
}


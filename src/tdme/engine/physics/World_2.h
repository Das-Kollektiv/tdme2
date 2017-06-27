// Generated from /tdme/src/tdme/engine/physics/World.java

#pragma once

#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/Key.h>

using tdme::utils::Pool;
using tdme::engine::physics::World;
using tdme::utils::Key;


struct default_init_tag;
class tdme::engine::physics::World_2
	: public Pool
{

public:
	typedef Pool super;

public: /* protected */
	Key* instantiate() override;

	// Generated

public:
	World_2(World *World_this);
	static ::java::lang::Class *class_();
	World *World_this;

private:
	virtual ::java::lang::Class* getClass0();
	friend class World;
	friend class World_1;
};

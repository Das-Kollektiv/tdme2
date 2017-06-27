// Generated from /tdme/src/tdme/engine/subsystems/object/AnimationState.java
#include <tdme/engine/subsystems/object/AnimationState.h>

using tdme::engine::subsystems::object::AnimationState;
AnimationState::AnimationState(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

AnimationState::AnimationState()
	: AnimationState(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void AnimationState::ctor()
{
	super::ctor();
	init();
}

void AnimationState::init()
{
	setup = nullptr;
	currentAtTime = 0;
	lastAtTime = 0;
	finished = false;
	time = 0.0f;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AnimationState::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.AnimationState", 44);
    return c;
}

java::lang::Class* AnimationState::getClass0()
{
	return class_();
}


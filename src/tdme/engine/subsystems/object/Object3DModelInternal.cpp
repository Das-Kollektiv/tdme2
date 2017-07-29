// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DModelInternal.java
#include <tdme/engine/subsystems/object/Object3DModelInternal.h>

using tdme::engine::subsystems::object::Object3DModelInternal;

Object3DModelInternal::Object3DModelInternal(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Object3DModelInternal::Object3DModelInternal(Model* model) 
	: Object3DModelInternal(*static_cast< ::default_init_tag* >(0))
{
	ctor(model);
}

void Object3DModelInternal::ctor(Model* model)
{
	super::ctor(model, false, Engine::AnimationProcessingTarget::CPU_NORENDERING);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DModelInternal::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object.Object3DModelInternal", 51);
    return c;
}

java::lang::Class* Object3DModelInternal::getClass0()
{
	return class_();
}


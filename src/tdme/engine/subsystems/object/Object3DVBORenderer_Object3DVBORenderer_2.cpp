// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DVBORenderer.java
#include <tdme/engine/subsystems/object/Object3DVBORenderer_Object3DVBORenderer_2.h>

#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/utils/Key.h>

using tdme::engine::subsystems::object::Object3DVBORenderer_Object3DVBORenderer_2;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::utils::Key;

Object3DVBORenderer_Object3DVBORenderer_2::Object3DVBORenderer_Object3DVBORenderer_2(Object3DVBORenderer *Object3DVBORenderer_this)
	: super(*static_cast< ::default_init_tag* >(0))
	, Object3DVBORenderer_this(Object3DVBORenderer_this)
{
	clinit();
	ctor();
}

Key* Object3DVBORenderer_Object3DVBORenderer_2::instantiate()
{
	return new Key();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DVBORenderer_Object3DVBORenderer_2::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* Object3DVBORenderer_Object3DVBORenderer_2::getClass0()
{
	return class_();
}


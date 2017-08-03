// Generated from /tdme/src/tdme/engine/subsystems/object/Object3DVBORenderer.java
#include <tdme/engine/subsystems/object/Object3DVBORenderer_Object3DVBORenderer_3.h>

#include <tdme/engine/subsystems/object/Object3DVBORenderer.h>
#include <tdme/engine/subsystems/object/TransparentRenderFacesGroup.h>

using tdme::engine::subsystems::object::Object3DVBORenderer_Object3DVBORenderer_3;
using tdme::engine::subsystems::object::Object3DVBORenderer;
using tdme::engine::subsystems::object::TransparentRenderFacesGroup;

Object3DVBORenderer_Object3DVBORenderer_3::Object3DVBORenderer_Object3DVBORenderer_3(Object3DVBORenderer *Object3DVBORenderer_this)
	: super()
	, Object3DVBORenderer_this(Object3DVBORenderer_this)
{
	ctor();
}

TransparentRenderFacesGroup* Object3DVBORenderer_Object3DVBORenderer_3::instantiate()
{
	return new TransparentRenderFacesGroup();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object3DVBORenderer_Object3DVBORenderer_3::class_()
{
    static ::java::lang::Class* c = ::class_(u"", 0);
    return c;
}

java::lang::Class* Object3DVBORenderer_Object3DVBORenderer_3::getClass0()
{
	return class_();
}


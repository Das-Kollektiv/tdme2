// Generated from /tdme/src/tdme/engine/subsystems/renderer/GLRenderer.java
#include <tdme/engine/subsystems/renderer/GLRenderer_Material.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using tdme::engine::subsystems::renderer::GLRenderer_Material;
using tdme::engine::subsystems::renderer::GLRenderer;

GLRenderer_Material::GLRenderer_Material(GLRenderer *GLRenderer_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, GLRenderer_this(GLRenderer_this)
{
	clinit();
}

GLRenderer_Material::GLRenderer_Material(GLRenderer *GLRenderer_this)
	: GLRenderer_Material(GLRenderer_this, *static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GLRenderer_Material::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.renderer.GLRenderer.Material", 51);
    return c;
}

java::lang::Class* GLRenderer_Material::getClass0()
{
	return class_();
}


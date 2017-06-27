// Generated from /tdme/src/tdme/engine/subsystems/renderer/GLRenderer.java
#include <tdme/engine/subsystems/renderer/GLRenderer_Light.h>

#include <tdme/engine/subsystems/renderer/GLRenderer.h>

using tdme::engine::subsystems::renderer::GLRenderer_Light;
using tdme::engine::subsystems::renderer::GLRenderer;

GLRenderer_Light::GLRenderer_Light(GLRenderer *GLRenderer_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, GLRenderer_this(GLRenderer_this)
{
	clinit();
}

GLRenderer_Light::GLRenderer_Light(GLRenderer *GLRenderer_this)
	: GLRenderer_Light(GLRenderer_this, *static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GLRenderer_Light::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.renderer.GLRenderer.Light", 48);
    return c;
}

java::lang::Class* GLRenderer_Light::getClass0()
{
	return class_();
}


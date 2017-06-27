// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/DebugGLES2.h>

using com::jogamp::opengl::DebugGLES2;
extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::DebugGLES2::DebugGLES2(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::opengl::DebugGLES2::DebugGLES2(GLES2* arg0)
	: DebugGLES2(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void DebugGLES2::ctor(GLES2* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void DebugGLES2::ctor(GLES2* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DebugGLES2::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.DebugGLES2", 28);
    return c;
}

java::lang::Class* DebugGLES2::getClass0()
{
	return class_();
}


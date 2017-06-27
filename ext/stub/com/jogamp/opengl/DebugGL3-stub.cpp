// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/DebugGL3.h>

using com::jogamp::opengl::DebugGL3;
extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::DebugGL3::DebugGL3(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::opengl::DebugGL3::DebugGL3(GL3* arg0)
	: DebugGL3(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void DebugGL3::ctor(GL3* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void DebugGL3::ctor(GL3* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DebugGL3::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.DebugGL3", 26);
    return c;
}

java::lang::Class* DebugGL3::getClass0()
{
	return class_();
}


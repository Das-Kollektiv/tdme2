// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/DebugGL2.h>

using com::jogamp::opengl::DebugGL2;
extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::DebugGL2::DebugGL2(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::opengl::DebugGL2::DebugGL2(GL2* arg0)
	: DebugGL2(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void DebugGL2::ctor(GL2* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void DebugGL2::ctor(GL2* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* DebugGL2::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.DebugGL2", 26);
    return c;
}

java::lang::Class* DebugGL2::getClass0()
{
	return class_();
}


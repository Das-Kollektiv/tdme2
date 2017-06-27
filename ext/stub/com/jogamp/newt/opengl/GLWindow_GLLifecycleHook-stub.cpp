// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/newt/opengl/GLWindow_GLLifecycleHook.h>

#include <com/jogamp/newt/opengl/GLWindow.h>

using com::jogamp::newt::opengl::GLWindow_GLLifecycleHook;
using com::jogamp::newt::opengl::GLWindow;

extern void unimplemented_(const char16_t* name);
com::jogamp::newt::opengl::GLWindow_GLLifecycleHook::GLWindow_GLLifecycleHook(GLWindow *GLWindow_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, GLWindow_this(GLWindow_this)
{
	clinit();
}

com::jogamp::newt::opengl::GLWindow_GLLifecycleHook::GLWindow_GLLifecycleHook(GLWindow *GLWindow_this)
	: GLWindow_GLLifecycleHook(GLWindow_this, *static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void GLWindow_GLLifecycleHook::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void GLWindow_GLLifecycleHook::ctor()");
}

void GLWindow_GLLifecycleHook::destroyActionInLock()
{ /* stub */
	unimplemented_(u"void GLWindow_GLLifecycleHook::destroyActionInLock()");
}

void GLWindow_GLLifecycleHook::destroyActionPreLock()
{ /* stub */
	unimplemented_(u"void GLWindow_GLLifecycleHook::destroyActionPreLock()");
}

bool GLWindow_GLLifecycleHook::pauseRenderingAction()
{ /* stub */
	unimplemented_(u"bool GLWindow_GLLifecycleHook::pauseRenderingAction()");
	return 0;
}

void GLWindow_GLLifecycleHook::preserveGLStateAtDestroy(bool arg0)
{ /* stub */
	unimplemented_(u"void GLWindow_GLLifecycleHook::preserveGLStateAtDestroy(bool arg0)");
}

void GLWindow_GLLifecycleHook::resetCounter()
{ /* stub */
	unimplemented_(u"void GLWindow_GLLifecycleHook::resetCounter()");
}

void GLWindow_GLLifecycleHook::resumeRenderingAction()
{ /* stub */
	unimplemented_(u"void GLWindow_GLLifecycleHook::resumeRenderingAction()");
}

void GLWindow_GLLifecycleHook::setVisibleActionPost(bool arg0, bool arg1)
{ /* stub */
	unimplemented_(u"void GLWindow_GLLifecycleHook::setVisibleActionPost(bool arg0, bool arg1)");
}

void GLWindow_GLLifecycleHook::shutdownRenderingAction()
{ /* stub */
	unimplemented_(u"void GLWindow_GLLifecycleHook::shutdownRenderingAction()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GLWindow_GLLifecycleHook::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.newt.opengl.GLWindow.GLLifecycleHook", 47);
    return c;
}

java::lang::Class* GLWindow_GLLifecycleHook::getClass0()
{
	return class_();
}


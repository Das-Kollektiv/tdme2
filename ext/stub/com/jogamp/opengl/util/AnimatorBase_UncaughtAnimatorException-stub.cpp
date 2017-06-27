// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/util/AnimatorBase_UncaughtAnimatorException.h>

using com::jogamp::opengl::util::AnimatorBase_UncaughtAnimatorException;
extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::util::AnimatorBase_UncaughtAnimatorException::AnimatorBase_UncaughtAnimatorException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::opengl::util::AnimatorBase_UncaughtAnimatorException::AnimatorBase_UncaughtAnimatorException(GLAutoDrawable* arg0, Throwable* arg1)
	: AnimatorBase_UncaughtAnimatorException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}


void AnimatorBase_UncaughtAnimatorException::ctor(GLAutoDrawable* arg0, Throwable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AnimatorBase_UncaughtAnimatorException::ctor(GLAutoDrawable* arg0, Throwable* arg1)");
}

GLAutoDrawable* AnimatorBase_UncaughtAnimatorException::getGLAutoDrawable()
{ /* stub */
	unimplemented_(u"GLAutoDrawable* AnimatorBase_UncaughtAnimatorException::getGLAutoDrawable()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AnimatorBase_UncaughtAnimatorException::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.util.AnimatorBase.UncaughtAnimatorException", 61);
    return c;
}

java::lang::Class* AnimatorBase_UncaughtAnimatorException::getClass0()
{
	return class_();
}


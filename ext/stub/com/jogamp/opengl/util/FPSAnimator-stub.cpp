// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/util/FPSAnimator.h>

using com::jogamp::opengl::util::FPSAnimator;
extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::util::FPSAnimator::FPSAnimator(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::opengl::util::FPSAnimator::FPSAnimator(int32_t arg0)
	: FPSAnimator(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

com::jogamp::opengl::util::FPSAnimator::FPSAnimator(int32_t arg0, bool arg1)
	: FPSAnimator(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

com::jogamp::opengl::util::FPSAnimator::FPSAnimator(GLAutoDrawable* arg0, int32_t arg1)
	: FPSAnimator(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

com::jogamp::opengl::util::FPSAnimator::FPSAnimator(GLAutoDrawable* arg0, int32_t arg1, bool arg2)
	: FPSAnimator(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}

int32_t com::jogamp::opengl::util::FPSAnimator::timerNo;

void FPSAnimator::ctor(int32_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FPSAnimator::ctor(int32_t arg0)");
}

void FPSAnimator::ctor(int32_t arg0, bool arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FPSAnimator::ctor(int32_t arg0, bool arg1)");
}

void FPSAnimator::ctor(GLAutoDrawable* arg0, int32_t arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FPSAnimator::ctor(GLAutoDrawable* arg0, int32_t arg1)");
}

void FPSAnimator::ctor(GLAutoDrawable* arg0, int32_t arg1, bool arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FPSAnimator::ctor(GLAutoDrawable* arg0, int32_t arg1, bool arg2)");
}

String* FPSAnimator::getBaseName(String* arg0)
{ /* stub */
	unimplemented_(u"String* FPSAnimator::getBaseName(String* arg0)");
	return 0;
}

int32_t FPSAnimator::getFPS()
{ /* stub */
	unimplemented_(u"int32_t FPSAnimator::getFPS()");
	return 0;
}

bool FPSAnimator::isAnimating()
{ /* stub */
	unimplemented_(u"bool FPSAnimator::isAnimating()");
	return 0;
}

/* private: bool FPSAnimator::isAnimatingImpl() */
bool FPSAnimator::isPaused()
{ /* stub */
	unimplemented_(u"bool FPSAnimator::isPaused()");
	return 0;
}

bool FPSAnimator::pause()
{ /* stub */
	unimplemented_(u"bool FPSAnimator::pause()");
	return 0;
}

bool FPSAnimator::resume()
{ /* stub */
	unimplemented_(u"bool FPSAnimator::resume()");
	return 0;
}

void FPSAnimator::setFPS(int32_t arg0)
{ /* stub */
	unimplemented_(u"void FPSAnimator::setFPS(int32_t arg0)");
}

bool FPSAnimator::start()
{ /* stub */
	unimplemented_(u"bool FPSAnimator::start()");
	return 0;
}

bool FPSAnimator::stop()
{ /* stub */
	unimplemented_(u"bool FPSAnimator::stop()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FPSAnimator::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.util.FPSAnimator", 34);
    return c;
}

java::lang::Class* FPSAnimator::getClass0()
{
	return class_();
}


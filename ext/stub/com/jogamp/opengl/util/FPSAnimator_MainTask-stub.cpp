// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/util/FPSAnimator_MainTask.h>

#include <com/jogamp/opengl/util/FPSAnimator.h>

using com::jogamp::opengl::util::FPSAnimator_MainTask;
using com::jogamp::opengl::util::FPSAnimator;

extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::util::FPSAnimator_MainTask::FPSAnimator_MainTask(FPSAnimator *FPSAnimator_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, FPSAnimator_this(FPSAnimator_this)
{
	clinit();
}

com::jogamp::opengl::util::FPSAnimator_MainTask::FPSAnimator_MainTask(FPSAnimator *FPSAnimator_this)
	: FPSAnimator_MainTask(FPSAnimator_this, *static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void FPSAnimator_MainTask::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FPSAnimator_MainTask::ctor()");
}

bool FPSAnimator_MainTask::isActive()
{ /* stub */
	unimplemented_(u"bool FPSAnimator_MainTask::isActive()");
	return 0;
}

void FPSAnimator_MainTask::run()
{ /* stub */
	unimplemented_(u"void FPSAnimator_MainTask::run()");
}

void FPSAnimator_MainTask::start(Timer* arg0)
{ /* stub */
	unimplemented_(u"void FPSAnimator_MainTask::start(Timer* arg0)");
}

String* FPSAnimator_MainTask::toString()
{ /* stub */
	unimplemented_(u"String* FPSAnimator_MainTask::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FPSAnimator_MainTask::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.util.FPSAnimator.MainTask", 43);
    return c;
}

java::lang::Class* FPSAnimator_MainTask::getClass0()
{
	return class_();
}


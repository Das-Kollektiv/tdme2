// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/util/AnimatorBase.h>

using com::jogamp::opengl::util::AnimatorBase;
extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::util::AnimatorBase::AnimatorBase(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::opengl::util::AnimatorBase::AnimatorBase()
	: AnimatorBase(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

bool com::jogamp::opengl::util::AnimatorBase::DEBUG;
constexpr int32_t com::jogamp::opengl::util::AnimatorBase::MODE_EXPECT_AWT_RENDERING_THREAD;
constexpr int64_t com::jogamp::opengl::util::AnimatorBase::POLLP_WAIT_FOR_FINISH_LIFECYCLE_ACTION;
constexpr int64_t com::jogamp::opengl::util::AnimatorBase::TO_WAIT_FOR_FINISH_LIFECYCLE_ACTION;
Class* com::jogamp::opengl::util::AnimatorBase::awtAnimatorImplClazz;
int32_t com::jogamp::opengl::util::AnimatorBase::seqInstanceNumber;

void AnimatorBase::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AnimatorBase::ctor()");
}

void AnimatorBase::add(GLAutoDrawable* arg0)
{ /* stub */
	unimplemented_(u"void AnimatorBase::add(GLAutoDrawable* arg0)");
}

void AnimatorBase::display()
{ /* stub */
	unimplemented_(u"void AnimatorBase::display()");
}

bool AnimatorBase::finishLifecycleAction(AnimatorBase_Condition* arg0, int64_t arg1)
{ /* stub */
	unimplemented_(u"bool AnimatorBase::finishLifecycleAction(AnimatorBase_Condition* arg0, int64_t arg1)");
	return 0;
}

void AnimatorBase::flushGLRunnables()
{ /* stub */
	unimplemented_(u"void AnimatorBase::flushGLRunnables()");
}

Thread* AnimatorBase::getExclusiveContextThread()
{ /* stub */
	unimplemented_(u"Thread* AnimatorBase::getExclusiveContextThread()");
	return 0;
}

int64_t AnimatorBase::getFPSStartTime()
{ /* stub */
	unimplemented_(u"int64_t AnimatorBase::getFPSStartTime()");
	return 0;
}

float AnimatorBase::getLastFPS()
{ /* stub */
	unimplemented_(u"float AnimatorBase::getLastFPS()");
	return 0;
}

int64_t AnimatorBase::getLastFPSPeriod()
{ /* stub */
	unimplemented_(u"int64_t AnimatorBase::getLastFPSPeriod()");
	return 0;
}

int64_t AnimatorBase::getLastFPSUpdateTime()
{ /* stub */
	unimplemented_(u"int64_t AnimatorBase::getLastFPSUpdateTime()");
	return 0;
}

int32_t AnimatorBase::getModeBits()
{ /* stub */
return modeBits ; /* getter */
}

Thread* AnimatorBase::getThread()
{ /* stub */
	unimplemented_(u"Thread* AnimatorBase::getThread()");
	return 0;
}

String* AnimatorBase::getThreadName()
{ /* stub */
	clinit();
	unimplemented_(u"String* AnimatorBase::getThreadName()");
	return 0;
}

float AnimatorBase::getTotalFPS()
{ /* stub */
	unimplemented_(u"float AnimatorBase::getTotalFPS()");
	return 0;
}

int64_t AnimatorBase::getTotalFPSDuration()
{ /* stub */
	unimplemented_(u"int64_t AnimatorBase::getTotalFPSDuration()");
	return 0;
}

int32_t AnimatorBase::getTotalFPSFrames()
{ /* stub */
	unimplemented_(u"int32_t AnimatorBase::getTotalFPSFrames()");
	return 0;
}

GLAnimatorControl_UncaughtExceptionHandler* AnimatorBase::getUncaughtExceptionHandler()
{ /* stub */
return uncaughtExceptionHandler ; /* getter */
}

int32_t AnimatorBase::getUpdateFPSFrames()
{ /* stub */
	unimplemented_(u"int32_t AnimatorBase::getUpdateFPSFrames()");
	return 0;
}

bool AnimatorBase::handleUncaughtException(AnimatorBase_UncaughtAnimatorException* arg0)
{ /* stub */
	unimplemented_(u"bool AnimatorBase::handleUncaughtException(AnimatorBase_UncaughtAnimatorException* arg0)");
	return 0;
}

void AnimatorBase::initImpl(bool arg0)
{ /* stub */
	unimplemented_(u"void AnimatorBase::initImpl(bool arg0)");
}

bool AnimatorBase::isExclusiveContextEnabled()
{ /* stub */
	unimplemented_(u"bool AnimatorBase::isExclusiveContextEnabled()");
	return 0;
}

bool AnimatorBase::isStarted()
{ /* stub */
	unimplemented_(u"bool AnimatorBase::isStarted()");
	return 0;
}

void AnimatorBase::remove(GLAutoDrawable* arg0)
{ /* stub */
	unimplemented_(u"void AnimatorBase::remove(GLAutoDrawable* arg0)");
}

void AnimatorBase::resetFPSCounter()
{ /* stub */
	unimplemented_(u"void AnimatorBase::resetFPSCounter()");
}

void AnimatorBase::setDrawablesExclCtxState(bool arg0)
{ /* stub */
	unimplemented_(u"void AnimatorBase::setDrawablesExclCtxState(bool arg0)");
}

Thread* AnimatorBase::setExclusiveContext(Thread* arg0)
{ /* stub */
}

bool AnimatorBase::setExclusiveContext(bool arg0)
{ /* stub */
}

void AnimatorBase::setIgnoreExceptions(bool arg0)
{ /* stub */
	this->ignoreExceptions = arg0; /* setter */
}

void AnimatorBase::setModeBits(bool arg0, int32_t arg1)
{ /* stub */
}

void AnimatorBase::setPrintExceptions(bool arg0)
{ /* stub */
	this->printExceptions = arg0; /* setter */
}

void AnimatorBase::setUncaughtExceptionHandler(GLAnimatorControl_UncaughtExceptionHandler* arg0)
{ /* stub */
	this->uncaughtExceptionHandler = arg0; /* setter */
}

void AnimatorBase::setUpdateFPSFrames(int32_t arg0, PrintStream* arg1)
{ /* stub */
	unimplemented_(u"void AnimatorBase::setUpdateFPSFrames(int32_t arg0, PrintStream* arg1)");
}

String* AnimatorBase::toString()
{ /* stub */
	unimplemented_(u"String* AnimatorBase::toString()");
	return 0;
}

/* private: bool AnimatorBase::useAWTAnimatorImpl(int32_t arg0) */
bool AnimatorBase::validateDrawablesExclCtxState(Thread* arg0)
{ /* stub */
	unimplemented_(u"bool AnimatorBase::validateDrawablesExclCtxState(Thread* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AnimatorBase::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.util.AnimatorBase", 35);
    return c;
}

java::lang::Class* AnimatorBase::getClass0()
{
	return class_();
}


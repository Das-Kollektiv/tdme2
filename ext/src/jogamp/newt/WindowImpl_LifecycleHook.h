// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <jogamp/newt/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct jogamp::newt::WindowImpl_LifecycleHook
	: public virtual Object
{

	virtual void destroyActionInLock() = 0;
	virtual void destroyActionPreLock() = 0;
	virtual bool pauseRenderingAction() = 0;
	virtual void preserveGLStateAtDestroy(bool arg0) = 0;
	virtual void resetCounter() = 0;
	virtual void resumeRenderingAction() = 0;
	virtual void setVisibleActionPost(bool arg0, bool arg1) = 0;
	virtual void shutdownRenderingAction() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

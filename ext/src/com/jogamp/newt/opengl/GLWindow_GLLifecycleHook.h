// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/Object.h>
#include <jogamp/newt/WindowImpl_LifecycleHook.h>

using java::lang::Object;
using jogamp::newt::WindowImpl_LifecycleHook;
using com::jogamp::newt::opengl::GLWindow;
using com::jogamp::opengl::GLAnimatorControl;


struct default_init_tag;
class com::jogamp::newt::opengl::GLWindow_GLLifecycleHook
	: public virtual Object
	, public virtual WindowImpl_LifecycleHook
{

public:
	typedef Object super;

private:
	GLAnimatorControl* savedAnimator {  };

public: /* package */
	GLWindow* this$0 {  };

protected:
	void ctor();

public:
	void destroyActionInLock() override;
	void destroyActionPreLock() override;
	bool pauseRenderingAction() override;
	void preserveGLStateAtDestroy(bool arg0) override;
	void resetCounter() override;
	void resumeRenderingAction() override;
	void setVisibleActionPost(bool arg0, bool arg1) override;
	void shutdownRenderingAction() override;

	// Generated

public: /* protected */
	GLWindow_GLLifecycleHook(GLWindow *GLWindow_this);
protected:
	GLWindow_GLLifecycleHook(GLWindow *GLWindow_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	GLWindow *GLWindow_this;

private:
	virtual ::java::lang::Class* getClass0();
};

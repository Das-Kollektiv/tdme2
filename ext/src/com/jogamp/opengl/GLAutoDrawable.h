// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/common/util/locks/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <com/jogamp/opengl/GLDrawable.h>

using com::jogamp::opengl::GLDrawable;
using com::jogamp::common::util::locks::RecursiveLock;
using com::jogamp::opengl::GL;
using com::jogamp::opengl::GLAnimatorControl;
using com::jogamp::opengl::GLContext;
using com::jogamp::opengl::GLEventListener;
using com::jogamp::opengl::GLRunnable;
using java::lang::Object;
using java::lang::Thread;
using java::util::List;


struct com::jogamp::opengl::GLAutoDrawable
	: public virtual GLDrawable
{
	static bool SCREEN_CHANGE_ACTION_ENABLED;

	virtual void addGLEventListener(GLEventListener* arg0) = 0;
	virtual void addGLEventListener(int32_t arg0, GLEventListener* arg1) = 0;
	virtual bool areAllGLEventListenerInitialized() = 0;
	/*GLContext* createContext(GLContext* arg0); (already declared) */
	virtual void destroy() = 0;
	virtual void display() = 0;
	virtual GLEventListener* disposeGLEventListener(GLEventListener* arg0, bool arg1) = 0;
	virtual void flushGLRunnables() = 0;
	virtual GLAnimatorControl* getAnimator() = 0;
	virtual bool getAutoSwapBufferMode() = 0;
	virtual GLContext* getContext() = 0;
	virtual int32_t getContextCreationFlags() = 0;
	virtual GLDrawable* getDelegatedDrawable() = 0;
	virtual Thread* getExclusiveContextThread() = 0;
	virtual GL* getGL() = 0;
	virtual GLEventListener* getGLEventListener(int32_t arg0) = 0;
	virtual int32_t getGLEventListenerCount() = 0;
	virtual bool getGLEventListenerInitState(GLEventListener* arg0) = 0;
	virtual RecursiveLock* getUpstreamLock() = 0;
	virtual Object* getUpstreamWidget() = 0;
	virtual bool invoke(bool arg0, GLRunnable* arg1) = 0;
	virtual bool invoke(bool arg0, List* arg1) = 0;
	virtual bool isThreadGLCapable() = 0;
	virtual GLEventListener* removeGLEventListener(GLEventListener* arg0) = 0;
	virtual void setAnimator(GLAnimatorControl* arg0) = 0;
	virtual void setAutoSwapBufferMode(bool arg0) = 0;
	virtual GLContext* setContext(GLContext* arg0, bool arg1) = 0;
	virtual void setContextCreationFlags(int32_t arg0) = 0;
	virtual Thread* setExclusiveContextThread(Thread* arg0) = 0;
	virtual GL* setGL(GL* arg0) = 0;
	virtual void setGLEventListenerInitState(GLEventListener* arg0, bool arg1) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

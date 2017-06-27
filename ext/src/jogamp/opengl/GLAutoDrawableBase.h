// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <com/jogamp/common/util/fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <jogamp/opengl/fwd-tdme.h>
#include <java/lang/Object.h>
#include <com/jogamp/opengl/GLAutoDrawable.h>
#include <com/jogamp/opengl/GLStateKeeper.h>
#include <com/jogamp/opengl/FPSCounter.h>
#include <com/jogamp/opengl/GLSharedContextSetter.h>

using java::lang::Object;
using com::jogamp::opengl::GLAutoDrawable;
using com::jogamp::opengl::GLStateKeeper;
using com::jogamp::opengl::FPSCounter;
using com::jogamp::opengl::GLSharedContextSetter;
using com::jogamp::common::util::RunnableTask;
using com::jogamp::nativewindow::NativeSurface;
using com::jogamp::opengl::GL;
using com::jogamp::opengl::GLAnimatorControl;
using com::jogamp::opengl::GLCapabilitiesImmutable;
using com::jogamp::opengl::GLContext;
using com::jogamp::opengl::GLDrawable;
using com::jogamp::opengl::GLEventListener;
using com::jogamp::opengl::GLEventListenerState;
using com::jogamp::opengl::GLProfile;
using com::jogamp::opengl::GLRunnable;
using com::jogamp::opengl::GLStateKeeper_Listener;
using java::io::PrintStream;
using java::lang::Runnable;
using java::lang::String;
using java::lang::Thread;
using java::lang::ThreadGroup;
using java::util::List;
using jogamp::opengl::FPSCounterImpl;
using jogamp::opengl::GLContextImpl;
using jogamp::opengl::GLDrawableHelper;
using jogamp::opengl::GLDrawableImpl;


struct default_init_tag;
class jogamp::opengl::GLAutoDrawableBase
	: public virtual Object
	, public virtual GLAutoDrawable
	, public virtual GLStateKeeper
	, public virtual FPSCounter
	, public virtual GLSharedContextSetter
{

public:
	typedef Object super;
	static bool DEBUG;

public: /* protected */
	int32_t additionalCtxCreationFlags {  };
	std::atomic< GLContextImpl* > context {  };
	Runnable* defaultDisplayAction {  };
	Runnable* defaultInitAction {  };
	std::atomic< GLDrawableImpl* > drawable {  };
	FPSCounterImpl* fpsCounter {  };
	GLStateKeeper_Listener* glStateKeeperListener {  };
	GLEventListenerState* glels {  };
	GLDrawableHelper* helper {  };
	bool ownsDevice {  };
	bool preserveGLELSAtDestroy {  };
	std::atomic< bool > sendDestroy {  };
	std::atomic< bool > sendReshape {  };

protected:
	void ctor(GLDrawableImpl* arg0, GLContextImpl* arg1, bool arg2);

public:
	void addGLEventListener(GLEventListener* arg0) override;
	void addGLEventListener(int32_t arg0, GLEventListener* arg1) override;
	bool areAllGLEventListenerInitialized() override;
	GLEventListenerState* clearPreservedGLState() override;
	GLContext* createContext(GLContext* arg0) override;

public: /* protected */
	void defaultDestroy();
	void defaultDisplay();
	GLEventListener* defaultDisposeGLEventListener(GLEventListener* arg0, bool arg1);

public:
	void defaultSwapBuffers();

public: /* protected */
	void defaultWindowDestroyNotifyOp();
	void defaultWindowRepaintOp();
	void defaultWindowResizedOp(int32_t arg0, int32_t arg1);
	void destroyAvoidAwareOfLocking();
	virtual void destroyImplInLock();

public:
	GLEventListener* disposeGLEventListener(GLEventListener* arg0, bool arg1) override;
	void flushGLRunnables() override;
	GLAnimatorControl* getAnimator() override;
	bool getAutoSwapBufferMode() override;
	GLCapabilitiesImmutable* getChosenGLCapabilities() override;
	GLContext* getContext() override;
	int32_t getContextCreationFlags() override;
	GLDrawable* getDelegatedDrawable() override;
	Thread* getExclusiveContextThread() override;
	int64_t getFPSStartTime() override;
	GL* getGL() override;
	GLEventListener* getGLEventListener(int32_t arg0) override;
	int32_t getGLEventListenerCount() override;
	bool getGLEventListenerInitState(GLEventListener* arg0) override;
	GLProfile* getGLProfile() override;
	int64_t getHandle() override;
	float getLastFPS() override;
	int64_t getLastFPSPeriod() override;
	int64_t getLastFPSUpdateTime() override;
	NativeSurface* getNativeSurface() override;
	GLEventListenerState* getPreservedGLState() override;
	GLCapabilitiesImmutable* getRequestedGLCapabilities() override;
	int32_t getSurfaceHeight() override;
	int32_t getSurfaceWidth() override;

public: /* protected */
	static String* getThreadName();

public:
	float getTotalFPS() override;
	int64_t getTotalFPSDuration() override;
	int32_t getTotalFPSFrames() override;
	int32_t getUpdateFPSFrames() override;
	bool invoke(bool arg0, GLRunnable* arg1) override;
	bool invoke(bool arg0, List* arg1) override;
	void invokeOnCurrentThread(Runnable* arg0);
	RunnableTask* invokeOnNewThread(ThreadGroup* arg0, bool arg1, Runnable* arg2);
	bool isGLOriented() override;
	bool isGLStatePreservationSupported() override;
	bool isRealized() override;
	bool isThreadGLCapable() override;

public: /* protected */
	bool preserveGLEventListenerState();

public:
	bool preserveGLStateAtDestroy(bool arg0) override;
	GLEventListener* removeGLEventListener(GLEventListener* arg0) override;
	void resetFPSCounter() override;

public: /* protected */
	bool restoreGLEventListenerState();

public:
	void setAnimator(GLAnimatorControl* arg0) override;
	void setAutoSwapBufferMode(bool arg0) override;
	GLContext* setContext(GLContext* arg0, bool arg1) override;
	void setContextCreationFlags(int32_t arg0) override;
	Thread* setExclusiveContextThread(Thread* arg0) override;
	GL* setGL(GL* arg0) override;
	void setGLEventListenerInitState(GLEventListener* arg0, bool arg1) override;
	GLStateKeeper_Listener* setGLStateKeeperListener(GLStateKeeper_Listener* arg0) override;
	void setRealized(bool arg0) override;
	void setSharedAutoDrawable(GLAutoDrawable* arg0) override;
	void setSharedContext(GLContext* arg0) override;
	void setUpdateFPSFrames(int32_t arg0, PrintStream* arg1) override;
	String* toString() override;

	// Generated
	GLAutoDrawableBase(GLDrawableImpl* arg0, GLContextImpl* arg1, bool arg2);
protected:
	GLAutoDrawableBase(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

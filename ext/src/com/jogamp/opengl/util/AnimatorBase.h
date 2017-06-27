// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/util/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <jogamp/opengl/fwd-tdme.h>
#include <java/lang/Object.h>
#include <com/jogamp/opengl/GLAnimatorControl.h>

using java::lang::Object;
using com::jogamp::opengl::GLAnimatorControl;
using com::jogamp::opengl::GLAnimatorControl_UncaughtExceptionHandler;
using com::jogamp::opengl::GLAutoDrawable;
using com::jogamp::opengl::util::AnimatorBase_AnimatorImpl;
using com::jogamp::opengl::util::AnimatorBase_Condition;
using com::jogamp::opengl::util::AnimatorBase_UncaughtAnimatorException;
using java::io::PrintStream;
using java::lang::Class;
using java::lang::String;
using java::lang::Thread;
using java::util::ArrayList;
using jogamp::opengl::FPSCounterImpl;


struct default_init_tag;
class com::jogamp::opengl::util::AnimatorBase
	: public virtual Object
	, public virtual GLAnimatorControl
{

public:
	typedef Object super;

public: /* protected */
	static bool DEBUG;

public:
	static constexpr int32_t MODE_EXPECT_AWT_RENDERING_THREAD { 1 };

public: /* protected */
	static constexpr int64_t POLLP_WAIT_FOR_FINISH_LIFECYCLE_ACTION { 32LL };
	static constexpr int64_t TO_WAIT_FOR_FINISH_LIFECYCLE_ACTION { 1000LL };
	Thread* animThread {  };

private:
	static Class* awtAnimatorImplClazz;

public: /* protected */
	String* baseName {  };
	ArrayList* drawables {  };
	bool drawablesEmpty {  };
	bool exclusiveContext {  };
	FPSCounterImpl* fpsCounter {  };
	bool ignoreExceptions {  };
	AnimatorBase_AnimatorImpl* impl {  };
	int32_t modeBits {  };
	bool printExceptions {  };

private:
	static int32_t seqInstanceNumber;

public: /* protected */
	GLAnimatorControl_UncaughtExceptionHandler* uncaughtExceptionHandler {  };
	Thread* userExclusiveContextThread {  };

private:
	AnimatorBase_Condition* waitForNotAnimatingIfEmptyCondition {  };

protected:
	void ctor();

public:
	void add(GLAutoDrawable* arg0) override;

public: /* protected */
	void display();
	bool finishLifecycleAction(AnimatorBase_Condition* arg0, int64_t arg1);
	void flushGLRunnables();
	virtual String* getBaseName(String* arg0) = 0;

public:
	Thread* getExclusiveContextThread();
	int64_t getFPSStartTime() override;
	float getLastFPS() override;
	int64_t getLastFPSPeriod() override;
	int64_t getLastFPSUpdateTime() override;
	virtual int32_t getModeBits();
	Thread* getThread() override;

public: /* protected */
	static String* getThreadName();

public:
	float getTotalFPS() override;
	int64_t getTotalFPSDuration() override;
	int32_t getTotalFPSFrames() override;
	GLAnimatorControl_UncaughtExceptionHandler* getUncaughtExceptionHandler() override;
	int32_t getUpdateFPSFrames() override;

public: /* protected */
	bool handleUncaughtException(AnimatorBase_UncaughtAnimatorException* arg0);
	void initImpl(bool arg0);

public:
	bool isExclusiveContextEnabled();
	bool isStarted() override;
	void remove(GLAutoDrawable* arg0) override;
	void resetFPSCounter() override;

public: /* protected */
	void setDrawablesExclCtxState(bool arg0);

public:
	Thread* setExclusiveContext(Thread* arg0);
	bool setExclusiveContext(bool arg0);
	void setIgnoreExceptions(bool arg0);
	void setModeBits(bool arg0, int32_t arg1);
	void setPrintExceptions(bool arg0);
	void setUncaughtExceptionHandler(GLAnimatorControl_UncaughtExceptionHandler* arg0) override;
	void setUpdateFPSFrames(int32_t arg0, PrintStream* arg1) override;
	String* toString() override;
	/*static bool useAWTAnimatorImpl(int32_t arg0); (private) */

public: /* protected */
	bool validateDrawablesExclCtxState(Thread* arg0);

	// Generated

public:
	AnimatorBase();
protected:
	AnimatorBase(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

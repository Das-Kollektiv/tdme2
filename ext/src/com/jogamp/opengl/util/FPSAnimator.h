// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/util/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <com/jogamp/opengl/util/AnimatorBase.h>

using com::jogamp::opengl::util::AnimatorBase;
using com::jogamp::opengl::GLAutoDrawable;
using com::jogamp::opengl::util::AnimatorBase_Condition;
using com::jogamp::opengl::util::FPSAnimator_MainTask;
using java::lang::String;
using java::util::Timer;


struct default_init_tag;
class com::jogamp::opengl::util::FPSAnimator
	: public AnimatorBase
{

public:
	typedef AnimatorBase super;

private:
	int32_t fps {  };
	bool isAnimating_ {  };
	std::atomic< bool > pauseIssued {  };
	bool scheduleAtFixedRate {  };
	std::atomic< bool > stopIssued {  };
	FPSAnimator_MainTask* task {  };
	Timer* timer {  };

public: /* package */
	static int32_t timerNo;

private:
	AnimatorBase_Condition* waitForPausedCondition {  };
	AnimatorBase_Condition* waitForResumeCondition {  };
	AnimatorBase_Condition* waitForStartedAddedCondition {  };
	AnimatorBase_Condition* waitForStartedEmptyCondition {  };
	AnimatorBase_Condition* waitForStoppedCondition {  };

protected:
	void ctor(int32_t arg0);
	void ctor(int32_t arg0, bool arg1);
	void ctor(GLAutoDrawable* arg0, int32_t arg1);
	void ctor(GLAutoDrawable* arg0, int32_t arg1, bool arg2);

public: /* protected */
	String* getBaseName(String* arg0) override;

public:
	int32_t getFPS();
	bool isAnimating() override;
	/*bool isAnimatingImpl(); (private) */
	bool isPaused() override;
	bool pause() override;
	bool resume() override;
	void setFPS(int32_t arg0);
	bool start() override;
	bool stop() override;

	// Generated
	FPSAnimator(int32_t arg0);
	FPSAnimator(int32_t arg0, bool arg1);
	FPSAnimator(GLAutoDrawable* arg0, int32_t arg1);
	FPSAnimator(GLAutoDrawable* arg0, int32_t arg1, bool arg2);
protected:
	FPSAnimator(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

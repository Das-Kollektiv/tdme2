// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/util/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/TimerTask.h>

using java::util::TimerTask;
using com::jogamp::opengl::util::FPSAnimator;
using java::lang::String;
using java::util::Timer;


struct default_init_tag;
class com::jogamp::opengl::util::FPSAnimator_MainTask
	: public TimerTask
{

public:
	typedef TimerTask super;

private:
	bool alreadyPaused {  };
	bool alreadyStopped {  };
	bool justStarted {  };

public: /* package */
	FPSAnimator* this$0 {  };

protected:
	void ctor();

public:
	virtual bool isActive();
	void run() override;
	virtual void start(Timer* arg0);
	String* toString() override;

	// Generated
	FPSAnimator_MainTask(FPSAnimator *FPSAnimator_this);
protected:
	FPSAnimator_MainTask(FPSAnimator *FPSAnimator_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	FPSAnimator *FPSAnimator_this;

private:
	virtual ::java::lang::Class* getClass0();
};

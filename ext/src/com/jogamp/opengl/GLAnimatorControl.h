// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/opengl/FPSCounter.h>

using com::jogamp::opengl::FPSCounter;
using com::jogamp::opengl::GLAnimatorControl_UncaughtExceptionHandler;
using com::jogamp::opengl::GLAutoDrawable;
using java::lang::Thread;


struct com::jogamp::opengl::GLAnimatorControl
	: public virtual FPSCounter
{

	virtual void add(GLAutoDrawable* arg0) = 0;
	virtual Thread* getThread() = 0;
	virtual GLAnimatorControl_UncaughtExceptionHandler* getUncaughtExceptionHandler() = 0;
	virtual bool isAnimating() = 0;
	virtual bool isPaused() = 0;
	virtual bool isStarted() = 0;
	virtual bool pause() = 0;
	virtual void remove(GLAutoDrawable* arg0) = 0;
	virtual bool resume() = 0;
	virtual void setUncaughtExceptionHandler(GLAnimatorControl_UncaughtExceptionHandler* arg0) = 0;
	virtual bool start() = 0;
	virtual bool stop() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

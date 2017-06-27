// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::opengl::GLAnimatorControl;
using com::jogamp::opengl::GLAutoDrawable;
using java::lang::Throwable;


struct com::jogamp::opengl::GLAnimatorControl_UncaughtExceptionHandler
	: public virtual Object
{

	virtual void uncaughtException(GLAnimatorControl* arg0, GLAutoDrawable* arg1, Throwable* arg2) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/util/EventListener.h>

using java::util::EventListener;
using com::jogamp::opengl::GLAutoDrawable;


struct com::jogamp::opengl::GLEventListener
	: public virtual EventListener
{

	virtual void display(GLAutoDrawable* arg0) = 0;
	virtual void dispose(GLAutoDrawable* arg0) = 0;
	virtual void init_(GLAutoDrawable* arg0) = 0;
	virtual void reshape(GLAutoDrawable* arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

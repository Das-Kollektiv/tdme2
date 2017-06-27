// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/GLAutoDrawable.h>

using com::jogamp::opengl::GLAutoDrawable;
using com::jogamp::opengl::GLContext;


struct com::jogamp::opengl::GLSharedContextSetter
	: public virtual GLAutoDrawable
{

	virtual void setSharedAutoDrawable(GLAutoDrawable* arg0) = 0;
	virtual void setSharedContext(GLContext* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

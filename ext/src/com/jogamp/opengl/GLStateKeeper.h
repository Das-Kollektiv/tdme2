// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::opengl::GLEventListenerState;
using com::jogamp::opengl::GLStateKeeper_Listener;


struct com::jogamp::opengl::GLStateKeeper
	: public virtual Object
{

	virtual GLEventListenerState* clearPreservedGLState() = 0;
	virtual GLEventListenerState* getPreservedGLState() = 0;
	virtual bool isGLStatePreservationSupported() = 0;
	virtual bool preserveGLStateAtDestroy(bool arg0) = 0;
	virtual GLStateKeeper_Listener* setGLStateKeeperListener(GLStateKeeper_Listener* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

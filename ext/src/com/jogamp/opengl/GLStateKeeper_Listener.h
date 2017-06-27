// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::opengl::GLStateKeeper;


struct com::jogamp::opengl::GLStateKeeper_Listener
	: public virtual Object
{

	virtual void glStatePreserveNotify(GLStateKeeper* arg0) = 0;
	virtual void glStateRestored(GLStateKeeper* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

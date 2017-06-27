// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct com::jogamp::opengl::util::AnimatorBase_Condition
	: public virtual Object
{

	virtual bool eval() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

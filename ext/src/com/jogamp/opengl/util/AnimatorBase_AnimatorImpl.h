// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/util/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Thread;
using java::util::ArrayList;


struct com::jogamp::opengl::util::AnimatorBase_AnimatorImpl
	: public virtual Object
{

	virtual bool blockUntilDone(Thread* arg0) = 0;
	virtual void display(ArrayList* arg0, bool arg1, bool arg2) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

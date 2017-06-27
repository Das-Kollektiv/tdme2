// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::nativewindow::NativeSurface;


struct com::jogamp::nativewindow::SurfaceUpdatedListener
	: public virtual Object
{

	virtual void surfaceUpdated(Object* arg0, NativeSurface* arg1, int64_t arg2) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

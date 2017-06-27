// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::nativewindow::NativeSurface;


struct com::jogamp::nativewindow::NativeSurfaceHolder
	: public virtual Object
{

	virtual NativeSurface* getNativeSurface() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

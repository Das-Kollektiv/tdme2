// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::nativewindow::VisualIDHolder_VIDType;


struct com::jogamp::nativewindow::VisualIDHolder
	: public virtual Object
{
	static constexpr int32_t VID_UNDEFINED { 0 };

	virtual int32_t getVisualID(VisualIDHolder_VIDType* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

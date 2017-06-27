// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <com/jogamp/nativewindow/util/fwd-tdme.h>
#include <com/jogamp/nativewindow/NativeSurface.h>
#include <com/jogamp/nativewindow/NativeSurfaceHolder.h>

using com::jogamp::nativewindow::NativeSurface;
using com::jogamp::nativewindow::NativeSurfaceHolder;
using com::jogamp::nativewindow::util::InsetsImmutable;
using com::jogamp::nativewindow::util::Point;


struct com::jogamp::nativewindow::NativeWindow
	: public virtual NativeSurface
	, public virtual NativeSurfaceHolder
{

	virtual void destroy() = 0;
	virtual int32_t getHeight() = 0;
	virtual InsetsImmutable* getInsets() = 0;
	virtual Point* getLocationOnScreen(Point* arg0) = 0;
	/*NativeSurface* getNativeSurface(); (already declared) */
	virtual NativeWindow* getParent() = 0;
	virtual int32_t getWidth() = 0;
	virtual int64_t getWindowHandle() = 0;
	virtual int32_t getX() = 0;
	virtual int32_t getY() = 0;
	virtual bool hasFocus() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

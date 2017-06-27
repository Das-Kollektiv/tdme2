// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/nativewindow/SurfaceUpdatedListener.h>

using com::jogamp::nativewindow::SurfaceUpdatedListener;
using com::jogamp::nativewindow::AbstractGraphicsConfiguration;
using java::lang::Thread;


struct com::jogamp::nativewindow::NativeSurface
	: public virtual SurfaceUpdatedListener
{
	static constexpr int32_t LOCK_SUCCESS { 3 };
	static constexpr int32_t LOCK_SURFACE_CHANGED { 2 };
	static constexpr int32_t LOCK_SURFACE_NOT_READY { 1 };
	static constexpr int32_t LOCK_SURFACE_UNLOCKED { 0 };

	virtual void addSurfaceUpdatedListener(SurfaceUpdatedListener* arg0) = 0;
	virtual void addSurfaceUpdatedListener(int32_t arg0, SurfaceUpdatedListener* arg1) = 0;
	virtual int32_tArray* convertToPixelUnits(int32_tArray* arg0) = 0;
	virtual int32_tArray* convertToWindowUnits(int32_tArray* arg0) = 0;
	virtual int64_t getDisplayHandle() = 0;
	virtual AbstractGraphicsConfiguration* getGraphicsConfiguration() = 0;
	virtual int32_t getScreenIndex() = 0;
	virtual int64_t getSurfaceHandle() = 0;
	virtual int32_t getSurfaceHeight() = 0;
	virtual Thread* getSurfaceLockOwner() = 0;
	virtual int32_t getSurfaceWidth() = 0;
	virtual bool isSurfaceLockedByOtherThread() = 0;
	virtual int32_t lockSurface() = 0;
	virtual void removeSurfaceUpdatedListener(SurfaceUpdatedListener* arg0) = 0;
	virtual bool surfaceSwap() = 0;
	virtual void unlockSurface() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

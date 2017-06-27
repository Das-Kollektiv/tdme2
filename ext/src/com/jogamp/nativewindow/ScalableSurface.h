// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct com::jogamp::nativewindow::ScalableSurface
	: public virtual Object
{
	static constexpr float AUTOMAX_PIXELSCALE { 0.0f };
	static constexpr float IDENTITY_PIXELSCALE { 1.0f };

	virtual floatArray* getCurrentSurfaceScale(floatArray* arg0) = 0;
	virtual floatArray* getMaximumSurfaceScale(floatArray* arg0) = 0;
	virtual floatArray* getMinimumSurfaceScale(floatArray* arg0) = 0;
	virtual floatArray* getRequestedSurfaceScale(floatArray* arg0) = 0;
	virtual bool setSurfaceScale(floatArray* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

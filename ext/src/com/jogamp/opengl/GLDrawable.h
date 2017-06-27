// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/nativewindow/NativeSurfaceHolder.h>

using com::jogamp::nativewindow::NativeSurfaceHolder;
using com::jogamp::nativewindow::NativeSurface;
using com::jogamp::opengl::GLCapabilitiesImmutable;
using com::jogamp::opengl::GLContext;
using com::jogamp::opengl::GLDrawableFactory;
using com::jogamp::opengl::GLProfile;
using java::lang::String;


struct com::jogamp::opengl::GLDrawable
	: public virtual NativeSurfaceHolder
{

	virtual GLContext* createContext(GLContext* arg0) = 0;
	virtual GLCapabilitiesImmutable* getChosenGLCapabilities() = 0;
	virtual GLDrawableFactory* getFactory() = 0;
	virtual GLProfile* getGLProfile() = 0;
	virtual int64_t getHandle() = 0;
	/*NativeSurface* getNativeSurface(); (already declared) */
	virtual GLCapabilitiesImmutable* getRequestedGLCapabilities() = 0;
	virtual int32_t getSurfaceHeight() = 0;
	virtual int32_t getSurfaceWidth() = 0;
	virtual bool isGLOriented() = 0;
	virtual bool isRealized() = 0;
	virtual void setRealized(bool arg0) = 0;
	virtual void swapBuffers() = 0;
	/*virtual String* toString(); (already declared) */

	// Generated
	static ::java::lang::Class *class_();
};

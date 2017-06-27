// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/nativewindow/CapabilitiesImmutable.h>

using com::jogamp::nativewindow::CapabilitiesImmutable;
using com::jogamp::opengl::GLProfile;
using java::lang::Object;
using java::lang::String;


struct com::jogamp::opengl::GLCapabilitiesImmutable
	: public virtual CapabilitiesImmutable
{
	static String* DEFAULT_SAMPLE_EXTENSION;

	/*bool equals(Object* arg0); (already declared) */
	virtual int32_t getAccumAlphaBits() = 0;
	virtual int32_t getAccumBlueBits() = 0;
	virtual int32_t getAccumGreenBits() = 0;
	virtual int32_t getAccumRedBits() = 0;
	virtual int32_t getDepthBits() = 0;
	virtual bool getDoubleBuffered() = 0;
	virtual GLProfile* getGLProfile() = 0;
	virtual bool getHardwareAccelerated() = 0;
	virtual int32_t getNumSamples() = 0;
	virtual bool getSampleBuffers() = 0;
	virtual String* getSampleExtension() = 0;
	virtual int32_t getStencilBits() = 0;
	virtual bool getStereo() = 0;
	/*int32_t hashCode(); (already declared) */
	virtual bool isFBO() = 0;
	virtual bool isPBuffer() = 0;
	/*String* toString(); (already declared) */

	// Generated
	static ::java::lang::Class *class_();
};

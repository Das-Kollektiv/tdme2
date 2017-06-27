// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::opengl::GL2;
using com::jogamp::opengl::GL2ES1;
using com::jogamp::opengl::GL2ES2;
using com::jogamp::opengl::GL2ES3;
using com::jogamp::opengl::GL2GL3;
using com::jogamp::opengl::GL3;
using com::jogamp::opengl::GL3ES3;
using com::jogamp::opengl::GL3bc;
using com::jogamp::opengl::GL4;
using com::jogamp::opengl::GL4ES3;
using com::jogamp::opengl::GL4bc;
using com::jogamp::opengl::GL;
using com::jogamp::opengl::GLBufferStorage;
using com::jogamp::opengl::GLContext;
using com::jogamp::opengl::GLES1;
using com::jogamp::opengl::GLES2;
using com::jogamp::opengl::GLES3;
using com::jogamp::opengl::GLProfile;
using java::lang::String;


struct com::jogamp::opengl::GLBase
	: public virtual Object
{

	virtual int32_t getBoundBuffer(int32_t arg0) = 0;
	virtual int32_t getBoundFramebuffer(int32_t arg0) = 0;
	virtual GLBufferStorage* getBufferStorage(int32_t arg0) = 0;
	virtual GLContext* getContext() = 0;
	virtual int32_t getDefaultDrawFramebuffer() = 0;
	virtual int32_t getDefaultReadBuffer() = 0;
	virtual int32_t getDefaultReadFramebuffer() = 0;
	virtual GL* getDownstreamGL() = 0;
	virtual Object* getExtension(String* arg0) = 0;
	virtual GL* getGL() = 0;
	virtual GL2* getGL2() = 0;
	virtual GL2ES1* getGL2ES1() = 0;
	virtual GL2ES2* getGL2ES2() = 0;
	virtual GL2ES3* getGL2ES3() = 0;
	virtual GL2GL3* getGL2GL3() = 0;
	virtual GL3* getGL3() = 0;
	virtual GL3ES3* getGL3ES3() = 0;
	virtual GL3bc* getGL3bc() = 0;
	virtual GL4* getGL4() = 0;
	virtual GL4ES3* getGL4ES3() = 0;
	virtual GL4bc* getGL4bc() = 0;
	virtual GLES1* getGLES1() = 0;
	virtual GLES2* getGLES2() = 0;
	virtual GLES3* getGLES3() = 0;
	virtual GLProfile* getGLProfile() = 0;
	virtual int32_t getMaxRenderbufferSamples() = 0;
	virtual Object* getPlatformGLExtensions() = 0;
	virtual GL* getRootGL() = 0;
	virtual int32_t getSwapInterval() = 0;
	virtual void glClearDepth(double arg0) = 0;
	virtual void glDepthRange(double arg0, double arg1) = 0;
	virtual bool hasBasicFBOSupport() = 0;
	virtual bool hasFullFBOSupport() = 0;
	virtual bool hasGLSL() = 0;
	virtual bool isExtensionAvailable(String* arg0) = 0;
	virtual bool isFunctionAvailable(String* arg0) = 0;
	virtual bool isGL() = 0;
	virtual bool isGL2() = 0;
	virtual bool isGL2ES1() = 0;
	virtual bool isGL2ES2() = 0;
	virtual bool isGL2ES3() = 0;
	virtual bool isGL2GL3() = 0;
	virtual bool isGL3() = 0;
	virtual bool isGL3ES3() = 0;
	virtual bool isGL3bc() = 0;
	virtual bool isGL3core() = 0;
	virtual bool isGL4() = 0;
	virtual bool isGL4ES3() = 0;
	virtual bool isGL4bc() = 0;
	virtual bool isGL4core() = 0;
	virtual bool isGLES() = 0;
	virtual bool isGLES1() = 0;
	virtual bool isGLES2() = 0;
	virtual bool isGLES2Compatible() = 0;
	virtual bool isGLES3() = 0;
	virtual bool isGLES31Compatible() = 0;
	virtual bool isGLES32Compatible() = 0;
	virtual bool isGLES3Compatible() = 0;
	virtual bool isGLcore() = 0;
	virtual bool isNPOTTextureAvailable() = 0;
	virtual bool isTextureFormatBGRA8888Available() = 0;
	virtual bool isVBOArrayBound() = 0;
	virtual bool isVBOElementArrayBound() = 0;
	virtual GLBufferStorage* mapBuffer(int32_t arg0, int32_t arg1) = 0;
	virtual GLBufferStorage* mapBufferRange(int32_t arg0, int64_t arg1, int64_t arg2, int32_t arg3) = 0;
	virtual void setSwapInterval(int32_t arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

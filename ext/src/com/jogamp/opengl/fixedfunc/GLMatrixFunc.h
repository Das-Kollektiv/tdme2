// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fixedfunc/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;


struct com::jogamp::opengl::fixedfunc::GLMatrixFunc
	: public virtual Object
{
	static constexpr int32_t GL_MATRIX_MODE { 2976 };
	static constexpr int32_t GL_MODELVIEW { 5888 };
	static constexpr int32_t GL_MODELVIEW_MATRIX { 2982 };
	static constexpr int32_t GL_PROJECTION { 5889 };
	static constexpr int32_t GL_PROJECTION_MATRIX { 2983 };
	static constexpr int32_t GL_TEXTURE_MATRIX { 2984 };

	virtual void glFrustumf(float arg0, float arg1, float arg2, float arg3, float arg4, float arg5) = 0;
	virtual void glGetFloatv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void glGetFloatv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void glGetIntegerv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glGetIntegerv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glLoadIdentity() = 0;
	virtual void glLoadMatrixf(FloatBuffer* arg0) = 0;
	virtual void glLoadMatrixf(floatArray* arg0, int32_t arg1) = 0;
	virtual void glMatrixMode(int32_t arg0) = 0;
	virtual void glMultMatrixf(FloatBuffer* arg0) = 0;
	virtual void glMultMatrixf(floatArray* arg0, int32_t arg1) = 0;
	virtual void glOrthof(float arg0, float arg1, float arg2, float arg3, float arg4, float arg5) = 0;
	virtual void glPopMatrix() = 0;
	virtual void glPushMatrix() = 0;
	virtual void glRotatef(float arg0, float arg1, float arg2, float arg3) = 0;
	virtual void glScalef(float arg0, float arg1, float arg2) = 0;
	virtual void glTranslatef(float arg0, float arg1, float arg2) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

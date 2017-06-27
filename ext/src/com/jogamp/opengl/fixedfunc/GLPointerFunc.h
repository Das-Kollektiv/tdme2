// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/fixedfunc/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::opengl::GLArrayData;
using java::nio::Buffer;


struct com::jogamp::opengl::fixedfunc::GLPointerFunc
	: public virtual Object
{
	static constexpr int32_t GL_COLOR_ARRAY { 32886 };
	static constexpr int32_t GL_NORMAL_ARRAY { 32885 };
	static constexpr int32_t GL_TEXTURE_COORD_ARRAY { 32888 };
	static constexpr int32_t GL_VERTEX_ARRAY { 32884 };

	virtual void glColor4f(float arg0, float arg1, float arg2, float arg3) = 0;
	virtual void glColorPointer(GLArrayData* arg0) = 0;
	virtual void glColorPointer(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3) = 0;
	virtual void glColorPointer(int32_t arg0, int32_t arg1, int32_t arg2, int64_t arg3) = 0;
	virtual void glDisableClientState(int32_t arg0) = 0;
	virtual void glEnableClientState(int32_t arg0) = 0;
	virtual void glNormalPointer(GLArrayData* arg0) = 0;
	virtual void glNormalPointer(int32_t arg0, int32_t arg1, Buffer* arg2) = 0;
	virtual void glNormalPointer(int32_t arg0, int32_t arg1, int64_t arg2) = 0;
	virtual void glTexCoordPointer(GLArrayData* arg0) = 0;
	virtual void glTexCoordPointer(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3) = 0;
	virtual void glTexCoordPointer(int32_t arg0, int32_t arg1, int32_t arg2, int64_t arg3) = 0;
	virtual void glVertexPointer(GLArrayData* arg0) = 0;
	virtual void glVertexPointer(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3) = 0;
	virtual void glVertexPointer(int32_t arg0, int32_t arg1, int32_t arg2, int64_t arg3) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <com/jogamp/opengl/GLES2.h>
#include <com/jogamp/opengl/GL4ES3.h>

using com::jogamp::opengl::GLES2;
using com::jogamp::opengl::GL4ES3;
using java::nio::Buffer;


struct com::jogamp::opengl::GLES3
	: public virtual GLES2
	, public virtual GL4ES3
{

	virtual void glDrawElementsInstanced(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3, int32_t arg4) = 0;
	virtual void glDrawRangeElements(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, Buffer* arg5) = 0;
	virtual void glVertexAttribIPointer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, Buffer* arg4) = 0;
	/*void glVertexAttribPointer(int32_t arg0, int32_t arg1, int32_t arg2, bool arg3, int32_t arg4, Buffer* arg5); (already declared) */

	// Generated
	static ::java::lang::Class *class_();
	virtual void glDrawElementsInstanced(int32_t arg0, int32_t arg1, int32_t arg2, int64_t arg3, int32_t arg4) = 0;
	virtual void glDrawRangeElements(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int64_t arg5) = 0;
	virtual void glVertexAttribIPointer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int64_t arg4) = 0;
};

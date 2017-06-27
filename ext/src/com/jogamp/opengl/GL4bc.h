// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <com/jogamp/opengl/GL3bc.h>
#include <com/jogamp/opengl/GL4.h>

using com::jogamp::opengl::GL3bc;
using com::jogamp::opengl::GL4;
using java::nio::Buffer;


struct com::jogamp::opengl::GL4bc
	: public virtual GL3bc
	, public virtual GL4
{

	/*void glDrawArraysIndirect(int32_t arg0, Buffer* arg1); (already declared) */
	/*void glDrawElementsIndirect(int32_t arg0, int32_t arg1, Buffer* arg2); (already declared) */
	virtual void glDrawElementsInstancedBaseInstance(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3, int32_t arg4, int32_t arg5) = 0;
	virtual void glDrawElementsInstancedBaseVertexBaseInstance(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3, int32_t arg4, int32_t arg5, int32_t arg6) = 0;
	virtual void glMultiDrawArraysIndirect(int32_t arg0, Buffer* arg1, int32_t arg2, int32_t arg3) = 0;
	virtual void glVertexAttribLPointer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, Buffer* arg4) = 0;

	// Generated
	static ::java::lang::Class *class_();
	virtual void glVertexAttribLPointer(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int64_t arg4) = 0;
	virtual void glDrawElementsInstancedBaseInstance(int32_t arg0, int32_t arg1, int32_t arg2, int64_t arg3, int32_t arg4, int32_t arg5) = 0;
	virtual void glDrawElementsInstancedBaseVertexBaseInstance(int32_t arg0, int32_t arg1, int32_t arg2, int64_t arg3, int32_t arg4, int32_t arg5, int32_t arg6) = 0;
	virtual void glMultiDrawArraysIndirect(int32_t arg0, int64_t arg1, int32_t arg2, int32_t arg3) = 0;
};

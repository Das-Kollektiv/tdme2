// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <com/jogamp/opengl/GL2.h>
#include <com/jogamp/opengl/GL3.h>

using com::jogamp::opengl::GL2;
using com::jogamp::opengl::GL3;
using java::nio::Buffer;
using java::nio::IntBuffer;


struct com::jogamp::opengl::GL3bc
	: public virtual GL2
	, public virtual GL3
{

	virtual void glColorP3ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glColorP3uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glColorP3uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glColorP4ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glColorP4uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glColorP4uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	/*void glDrawElementsBaseVertex(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3, int32_t arg4); (already declared) */
	/*void glDrawElementsInstancedBaseVertex(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3, int32_t arg4, int32_t arg5); (already declared) */
	/*void glDrawRangeElementsBaseVertex(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, Buffer* arg5, int32_t arg6); (already declared) */
	virtual void glMultiTexCoordP1ui(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void glMultiTexCoordP1uiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glMultiTexCoordP1uiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void glMultiTexCoordP2ui(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void glMultiTexCoordP2uiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glMultiTexCoordP2uiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void glMultiTexCoordP3ui(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void glMultiTexCoordP3uiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glMultiTexCoordP3uiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void glMultiTexCoordP4ui(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void glMultiTexCoordP4uiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glMultiTexCoordP4uiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void glNormalP3ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glNormalP3uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glNormalP3uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glSecondaryColorP3ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glSecondaryColorP3uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glSecondaryColorP3uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glTexCoordP1ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glTexCoordP1uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glTexCoordP1uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glTexCoordP2ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glTexCoordP2uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glTexCoordP2uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glTexCoordP3ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glTexCoordP3uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glTexCoordP3uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glTexCoordP4ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glTexCoordP4uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glTexCoordP4uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glVertexP2ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glVertexP2uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glVertexP2uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glVertexP3ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glVertexP3uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glVertexP3uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glVertexP4ui(int32_t arg0, int32_t arg1) = 0;
	virtual void glVertexP4uiv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glVertexP4uiv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

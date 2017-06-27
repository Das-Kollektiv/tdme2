// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/common/nio/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <com/jogamp/opengl/GL3ES3.h>
#include <com/jogamp/opengl/GL2GL3.h>

using com::jogamp::opengl::GL3ES3;
using com::jogamp::opengl::GL2GL3;
using com::jogamp::common::nio::PointerBuffer;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using java::nio::Buffer;
using java::nio::ByteBuffer;
using java::nio::DoubleBuffer;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct com::jogamp::opengl::GL3
	: public virtual GL3ES3
	, public virtual GL2GL3
{
	static constexpr int32_t GL_ACTIVE_SUBROUTINES { 36325 };
	static constexpr int32_t GL_ACTIVE_SUBROUTINE_MAX_LENGTH { 36424 };
	static constexpr int32_t GL_ACTIVE_SUBROUTINE_UNIFORMS { 36326 };
	static constexpr int32_t GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS { 36423 };
	static constexpr int32_t GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH { 36425 };
	static constexpr int32_t GL_COMPATIBLE_SUBROUTINES { 36427 };
	static constexpr int32_t GL_COMPRESSED_RGBA_BPTC_UNORM_ARB { 36492 };
	static constexpr int32_t GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB { 36494 };
	static constexpr int32_t GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB { 36495 };
	static constexpr int32_t GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB { 36493 };
	static constexpr int32_t GL_CONTEXT_COMPATIBILITY_PROFILE_BIT { 2 };
	static constexpr int32_t GL_CONTEXT_CORE_PROFILE_BIT { 1 };
	static constexpr int32_t GL_CONTEXT_PROFILE_MASK { 37158 };
	static constexpr int32_t GL_DEPTH_CLAMP { 34383 };
	static constexpr int32_t GL_DOUBLE_MAT2 { 36678 };
	static constexpr int32_t GL_DOUBLE_MAT2x3 { 36681 };
	static constexpr int32_t GL_DOUBLE_MAT2x4 { 36682 };
	static constexpr int32_t GL_DOUBLE_MAT3 { 36679 };
	static constexpr int32_t GL_DOUBLE_MAT3x2 { 36683 };
	static constexpr int32_t GL_DOUBLE_MAT3x4 { 36684 };
	static constexpr int32_t GL_DOUBLE_MAT4 { 36680 };
	static constexpr int32_t GL_DOUBLE_MAT4x2 { 36685 };
	static constexpr int32_t GL_DOUBLE_MAT4x3 { 36686 };
	static constexpr int32_t GL_DOUBLE_VEC2 { 36860 };
	static constexpr int32_t GL_DOUBLE_VEC3 { 36861 };
	static constexpr int32_t GL_DOUBLE_VEC4 { 36862 };
	static constexpr int32_t GL_FRAMEBUFFER_ATTACHMENT_LAYERED_ARB { 36263 };
	static constexpr int32_t GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB { 36265 };
	static constexpr int32_t GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_ARB { 36264 };
	static constexpr int32_t GL_GEOMETRY_INPUT_TYPE_ARB { 36315 };
	static constexpr int32_t GL_GEOMETRY_OUTPUT_TYPE_ARB { 36316 };
	static constexpr int32_t GL_GEOMETRY_SHADER_ARB { 36313 };
	static constexpr int32_t GL_GEOMETRY_VERTICES_OUT_ARB { 36314 };
	static constexpr int32_t GL_LINES_ADJACENCY_ARB { 10 };
	static constexpr int32_t GL_LINE_STRIP_ADJACENCY_ARB { 11 };
	static constexpr int32_t GL_MAX_DUAL_SOURCE_DRAW_BUFFERS { 35068 };
	static constexpr int32_t GL_MAX_GEOMETRY_OUTPUT_VERTICES_ARB { 36320 };
	static constexpr int32_t GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB { 35881 };
	static constexpr int32_t GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_ARB { 36321 };
	static constexpr int32_t GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_ARB { 36319 };
	static constexpr int32_t GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB { 36317 };
	static constexpr int32_t GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS { 36767 };
	static constexpr int32_t GL_MAX_SUBROUTINES { 36327 };
	static constexpr int32_t GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS { 36328 };
	static constexpr int32_t GL_MAX_VERTEX_VARYING_COMPONENTS_ARB { 36318 };
	static constexpr int32_t GL_MAX_VIEWPORTS { 33371 };
	static constexpr int32_t GL_NAMED_STRING_LENGTH_ARB { 36329 };
	static constexpr int32_t GL_NAMED_STRING_TYPE_ARB { 36330 };
	static constexpr int32_t GL_NUM_COMPATIBLE_SUBROUTINES { 36426 };
	static constexpr int32_t GL_ONE_MINUS_SRC1_ALPHA { 35067 };
	static constexpr int32_t GL_ONE_MINUS_SRC1_COLOR { 35066 };
	static constexpr int32_t GL_PATCH_DEFAULT_INNER_LEVEL { 36467 };
	static constexpr int32_t GL_PATCH_DEFAULT_OUTER_LEVEL { 36468 };
	static constexpr int32_t GL_PROGRAM_POINT_SIZE { 34370 };
	static constexpr int32_t GL_PROGRAM_POINT_SIZE_ARB { 34370 };
	static constexpr int32_t GL_SHADER_INCLUDE_ARB { 36270 };
	static constexpr int32_t GL_SRC1_COLOR { 35065 };
	static constexpr int32_t GL_SYNC_CL_EVENT_ARB { 33344 };
	static constexpr int32_t GL_SYNC_CL_EVENT_COMPLETE_ARB { 33345 };
	static constexpr int32_t GL_TRIANGLES_ADJACENCY_ARB { 12 };
	static constexpr int32_t GL_TRIANGLE_STRIP_ADJACENCY_ARB { 13 };
	static constexpr int32_t GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER { 34032 };
	static constexpr int32_t GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER { 34033 };
	static constexpr int32_t GL_VIEWPORT_BOUNDS_RANGE { 33373 };
	static constexpr int32_t GL_VIEWPORT_INDEX_PROVOKING_VERTEX { 33375 };
	static constexpr int32_t GL_VIEWPORT_SUBPIXEL_BITS { 33372 };

	virtual void glBindFragDataLocationIndexed(int32_t arg0, int32_t arg1, int32_t arg2, String* arg3) = 0;
	virtual void glCompileShaderIncludeARB(int32_t arg0, int32_t arg1, StringArray* arg2, IntBuffer* arg3) = 0;
	virtual void glCompileShaderIncludeARB(int32_t arg0, int32_t arg1, StringArray* arg2, int32_tArray* arg3, int32_t arg4) = 0;
	virtual int64_t glCreateSyncFromCLeventARB(int64_t arg0, int64_t arg1, int32_t arg2) = 0;
	virtual void glDeleteNamedStringARB(int32_t arg0, String* arg1) = 0;
	virtual void glDepthRangeArrayv(int32_t arg0, int32_t arg1, DoubleBuffer* arg2) = 0;
	virtual void glDepthRangeArrayv(int32_t arg0, int32_t arg1, doubleArray* arg2, int32_t arg3) = 0;
	virtual void glDepthRangeIndexed(int32_t arg0, double arg1, double arg2) = 0;
	virtual void glDrawTransformFeedbackInstanced(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void glDrawTransformFeedbackStreamInstanced(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) = 0;
	virtual void glFramebufferTextureARB(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) = 0;
	virtual void glFramebufferTextureFaceARB(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) = 0;
	virtual void glFramebufferTextureLayerARB(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) = 0;
	virtual void glGetActiveSubroutineName(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, IntBuffer* arg4, ByteBuffer* arg5) = 0;
	virtual void glGetActiveSubroutineName(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5, int8_tArray* arg6, int32_t arg7) = 0;
	virtual void glGetActiveSubroutineUniformName(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, IntBuffer* arg4, ByteBuffer* arg5) = 0;
	virtual void glGetActiveSubroutineUniformName(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5, int8_tArray* arg6, int32_t arg7) = 0;
	virtual void glGetActiveSubroutineUniformiv(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, IntBuffer* arg4) = 0;
	virtual void glGetActiveSubroutineUniformiv(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5) = 0;
	virtual void glGetDoublei_v(int32_t arg0, int32_t arg1, DoubleBuffer* arg2) = 0;
	virtual void glGetDoublei_v(int32_t arg0, int32_t arg1, doubleArray* arg2, int32_t arg3) = 0;
	virtual void glGetFloati_v(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void glGetFloati_v(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual int32_t glGetFragDataIndex(int32_t arg0, String* arg1) = 0;
	virtual void glGetNamedStringARB(int32_t arg0, String* arg1, int32_t arg2, IntBuffer* arg3, ByteBuffer* arg4) = 0;
	virtual void glGetNamedStringARB(int32_t arg0, String* arg1, int32_t arg2, int32_tArray* arg3, int32_t arg4, int8_tArray* arg5, int32_t arg6) = 0;
	virtual void glGetNamedStringivARB(int32_t arg0, String* arg1, int32_t arg2, IntBuffer* arg3) = 0;
	virtual void glGetNamedStringivARB(int32_t arg0, String* arg1, int32_t arg2, int32_tArray* arg3, int32_t arg4) = 0;
	virtual void glGetProgramStageiv(int32_t arg0, int32_t arg1, int32_t arg2, IntBuffer* arg3) = 0;
	virtual void glGetProgramStageiv(int32_t arg0, int32_t arg1, int32_t arg2, int32_tArray* arg3, int32_t arg4) = 0;
	virtual int32_t glGetSubroutineIndex(int32_t arg0, int32_t arg1, String* arg2) = 0;
	virtual int32_t glGetSubroutineUniformLocation(int32_t arg0, int32_t arg1, String* arg2) = 0;
	virtual void glGetUniformSubroutineuiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glGetUniformSubroutineuiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void glGetUniformdv(int32_t arg0, int32_t arg1, DoubleBuffer* arg2) = 0;
	virtual void glGetUniformdv(int32_t arg0, int32_t arg1, doubleArray* arg2, int32_t arg3) = 0;
	virtual bool glIsNamedStringARB(int32_t arg0, String* arg1) = 0;
	virtual void glMultiDrawArraysIndirect(int32_t arg0, int64_t arg1, int32_t arg2, int32_t arg3) = 0;
	virtual void glMultiDrawElementsBaseVertex(int32_t arg0, IntBuffer* arg1, int32_t arg2, PointerBuffer* arg3, int32_t arg4, IntBuffer* arg5) = 0;
	virtual void glMultiDrawElementsIndirect(int32_t arg0, int32_t arg1, Buffer* arg2, int32_t arg3, int32_t arg4) = 0;
	virtual void glNamedStringARB(int32_t arg0, int32_t arg1, String* arg2, int32_t arg3, String* arg4) = 0;
	virtual void glPatchParameterfv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void glPatchParameterfv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void glProgramParameteriARB(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void glScissorArrayv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glScissorArrayv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void glScissorIndexed(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) = 0;
	virtual void glScissorIndexedv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glScissorIndexedv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glUniform1d(int32_t arg0, double arg1) = 0;
	virtual void glUniform1dv(int32_t arg0, int32_t arg1, DoubleBuffer* arg2) = 0;
	virtual void glUniform1dv(int32_t arg0, int32_t arg1, doubleArray* arg2, int32_t arg3) = 0;
	virtual void glUniform2d(int32_t arg0, double arg1, double arg2) = 0;
	virtual void glUniform2dv(int32_t arg0, int32_t arg1, DoubleBuffer* arg2) = 0;
	virtual void glUniform2dv(int32_t arg0, int32_t arg1, doubleArray* arg2, int32_t arg3) = 0;
	virtual void glUniform3d(int32_t arg0, double arg1, double arg2, double arg3) = 0;
	virtual void glUniform3dv(int32_t arg0, int32_t arg1, DoubleBuffer* arg2) = 0;
	virtual void glUniform3dv(int32_t arg0, int32_t arg1, doubleArray* arg2, int32_t arg3) = 0;
	virtual void glUniform4d(int32_t arg0, double arg1, double arg2, double arg3, double arg4) = 0;
	virtual void glUniform4dv(int32_t arg0, int32_t arg1, DoubleBuffer* arg2) = 0;
	virtual void glUniform4dv(int32_t arg0, int32_t arg1, doubleArray* arg2, int32_t arg3) = 0;
	virtual void glUniformMatrix2dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix2dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformMatrix2x3dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix2x3dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformMatrix2x4dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix2x4dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformMatrix3dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix3dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformMatrix3x2dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix3x2dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformMatrix3x4dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix3x4dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformMatrix4dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix4dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformMatrix4x2dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix4x2dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformMatrix4x3dv(int32_t arg0, int32_t arg1, bool arg2, DoubleBuffer* arg3) = 0;
	virtual void glUniformMatrix4x3dv(int32_t arg0, int32_t arg1, bool arg2, doubleArray* arg3, int32_t arg4) = 0;
	virtual void glUniformSubroutinesuiv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glUniformSubroutinesuiv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void glVertexAttribP1ui(int32_t arg0, int32_t arg1, bool arg2, int32_t arg3) = 0;
	virtual void glVertexAttribP1uiv(int32_t arg0, int32_t arg1, bool arg2, IntBuffer* arg3) = 0;
	virtual void glVertexAttribP1uiv(int32_t arg0, int32_t arg1, bool arg2, int32_tArray* arg3, int32_t arg4) = 0;
	virtual void glVertexAttribP2ui(int32_t arg0, int32_t arg1, bool arg2, int32_t arg3) = 0;
	virtual void glVertexAttribP2uiv(int32_t arg0, int32_t arg1, bool arg2, IntBuffer* arg3) = 0;
	virtual void glVertexAttribP2uiv(int32_t arg0, int32_t arg1, bool arg2, int32_tArray* arg3, int32_t arg4) = 0;
	virtual void glVertexAttribP3ui(int32_t arg0, int32_t arg1, bool arg2, int32_t arg3) = 0;
	virtual void glVertexAttribP3uiv(int32_t arg0, int32_t arg1, bool arg2, IntBuffer* arg3) = 0;
	virtual void glVertexAttribP3uiv(int32_t arg0, int32_t arg1, bool arg2, int32_tArray* arg3, int32_t arg4) = 0;
	virtual void glVertexAttribP4ui(int32_t arg0, int32_t arg1, bool arg2, int32_t arg3) = 0;
	virtual void glVertexAttribP4uiv(int32_t arg0, int32_t arg1, bool arg2, IntBuffer* arg3) = 0;
	virtual void glVertexAttribP4uiv(int32_t arg0, int32_t arg1, bool arg2, int32_tArray* arg3, int32_t arg4) = 0;
	virtual void glViewportArrayv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void glViewportArrayv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void glViewportIndexedf(int32_t arg0, float arg1, float arg2, float arg3, float arg4) = 0;
	virtual void glViewportIndexedfv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void glViewportIndexedfv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

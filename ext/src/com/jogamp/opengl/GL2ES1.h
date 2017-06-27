// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <com/jogamp/opengl/GL.h>
#include <com/jogamp/opengl/fixedfunc/GLMatrixFunc.h>
#include <com/jogamp/opengl/fixedfunc/GLPointerFunc.h>
#include <com/jogamp/opengl/fixedfunc/GLLightingFunc.h>

using com::jogamp::opengl::GL;
using com::jogamp::opengl::fixedfunc::GLMatrixFunc;
using com::jogamp::opengl::fixedfunc::GLPointerFunc;
using com::jogamp::opengl::fixedfunc::GLLightingFunc;
using java::nio::Buffer;
using java::nio::FloatBuffer;
using java::nio::IntBuffer;


struct com::jogamp::opengl::GL2ES1
	: public virtual GL
	, public virtual GLMatrixFunc
	, public virtual GLPointerFunc
	, public virtual GLLightingFunc
{
	static constexpr int32_t GL_ADD { 260 };
	static constexpr int32_t GL_ADD_SIGNED { 34164 };
	static constexpr int32_t GL_ALPHA_SCALE { 3356 };
	static constexpr int32_t GL_ALPHA_TEST { 3008 };
	static constexpr int32_t GL_ALPHA_TEST_FUNC { 3009 };
	static constexpr int32_t GL_ALPHA_TEST_REF { 3010 };
	static constexpr int32_t GL_CLIENT_ACTIVE_TEXTURE { 34017 };
	static constexpr int32_t GL_CLIP_PLANE0 { 12288 };
	static constexpr int32_t GL_CLIP_PLANE1 { 12289 };
	static constexpr int32_t GL_CLIP_PLANE2 { 12290 };
	static constexpr int32_t GL_CLIP_PLANE3 { 12291 };
	static constexpr int32_t GL_CLIP_PLANE4 { 12292 };
	static constexpr int32_t GL_CLIP_PLANE5 { 12293 };
	static constexpr int32_t GL_COLOR_ARRAY_BUFFER_BINDING { 34968 };
	static constexpr int32_t GL_COLOR_ARRAY_POINTER { 32912 };
	static constexpr int32_t GL_COLOR_ARRAY_SIZE { 32897 };
	static constexpr int32_t GL_COLOR_ARRAY_STRIDE { 32899 };
	static constexpr int32_t GL_COLOR_ARRAY_TYPE { 32898 };
	static constexpr int32_t GL_COMBINE { 34160 };
	static constexpr int32_t GL_COMBINE_ALPHA { 34162 };
	static constexpr int32_t GL_COMBINE_RGB { 34161 };
	static constexpr int32_t GL_CONSTANT { 34166 };
	static constexpr int32_t GL_CONTEXT_ROBUST_ACCESS { 37107 };
	static constexpr int32_t GL_COORD_REPLACE { 34914 };
	static constexpr int32_t GL_CURRENT_COLOR { 2816 };
	static constexpr int32_t GL_CURRENT_NORMAL { 2818 };
	static constexpr int32_t GL_CURRENT_TEXTURE_COORDS { 2819 };
	static constexpr int32_t GL_DECAL { 8449 };
	static constexpr int32_t GL_DOT3_RGB { 34478 };
	static constexpr int32_t GL_DOT3_RGBA { 34479 };
	static constexpr int32_t GL_EXP { 2048 };
	static constexpr int32_t GL_EXP2 { 2049 };
	static constexpr int32_t GL_FOG { 2912 };
	static constexpr int32_t GL_FOG_COLOR { 2918 };
	static constexpr int32_t GL_FOG_DENSITY { 2914 };
	static constexpr int32_t GL_FOG_END { 2916 };
	static constexpr int32_t GL_FOG_HINT { 3156 };
	static constexpr int32_t GL_FOG_MODE { 2917 };
	static constexpr int32_t GL_FOG_START { 2915 };
	static constexpr int32_t GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING { 33296 };
	static constexpr int32_t GL_GENERATE_MIPMAP { 33169 };
	static constexpr int32_t GL_INTERPOLATE { 34165 };
	static constexpr int32_t GL_LIGHT_MODEL_AMBIENT { 2899 };
	static constexpr int32_t GL_LIGHT_MODEL_TWO_SIDE { 2898 };
	static constexpr int32_t GL_MAX_CLIP_PLANES { 3378 };
	static constexpr int32_t GL_MAX_LIGHTS { 3377 };
	static constexpr int32_t GL_MAX_MODELVIEW_STACK_DEPTH { 3382 };
	static constexpr int32_t GL_MAX_PROJECTION_STACK_DEPTH { 3384 };
	static constexpr int32_t GL_MAX_TEXTURE_STACK_DEPTH { 3385 };
	static constexpr int32_t GL_MAX_TEXTURE_UNITS { 34018 };
	static constexpr int32_t GL_MODELVIEW_STACK_DEPTH { 2979 };
	static constexpr int32_t GL_MODULATE { 8448 };
	static constexpr int32_t GL_NORMAL_ARRAY_BUFFER_BINDING { 34967 };
	static constexpr int32_t GL_NORMAL_ARRAY_POINTER { 32911 };
	static constexpr int32_t GL_NORMAL_ARRAY_STRIDE { 32895 };
	static constexpr int32_t GL_NORMAL_ARRAY_TYPE { 32894 };
	static constexpr int32_t GL_OPERAND0_ALPHA { 34200 };
	static constexpr int32_t GL_OPERAND0_RGB { 34192 };
	static constexpr int32_t GL_OPERAND1_ALPHA { 34201 };
	static constexpr int32_t GL_OPERAND1_RGB { 34193 };
	static constexpr int32_t GL_OPERAND2_ALPHA { 34202 };
	static constexpr int32_t GL_OPERAND2_RGB { 34194 };
	static constexpr int32_t GL_PERSPECTIVE_CORRECTION_HINT { 3152 };
	static constexpr int32_t GL_POINT_DISTANCE_ATTENUATION { 33065 };
	static constexpr int32_t GL_POINT_SIZE_MAX { 33063 };
	static constexpr int32_t GL_POINT_SIZE_MIN { 33062 };
	static constexpr int32_t GL_POINT_SMOOTH { 2832 };
	static constexpr int32_t GL_POINT_SMOOTH_HINT { 3153 };
	static constexpr int32_t GL_POINT_SPRITE { 34913 };
	static constexpr int32_t GL_PREVIOUS { 34168 };
	static constexpr int32_t GL_PRIMARY_COLOR { 34167 };
	static constexpr int32_t GL_PROJECTION_STACK_DEPTH { 2980 };
	static constexpr int32_t GL_RESCALE_NORMAL { 32826 };
	static constexpr int32_t GL_RGB_SCALE { 34163 };
	static constexpr int32_t GL_SHADE_MODEL { 2900 };
	static constexpr int32_t GL_SRC0_ALPHA { 34184 };
	static constexpr int32_t GL_SRC0_RGB { 34176 };
	static constexpr int32_t GL_SRC1_ALPHA { 34185 };
	static constexpr int32_t GL_SRC1_RGB { 34177 };
	static constexpr int32_t GL_SRC2_ALPHA { 34186 };
	static constexpr int32_t GL_SRC2_RGB { 34178 };
	static constexpr int32_t GL_STACK_OVERFLOW { 1283 };
	static constexpr int32_t GL_STACK_UNDERFLOW { 1284 };
	static constexpr int32_t GL_SUBTRACT { 34023 };
	static constexpr int32_t GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING { 34970 };
	static constexpr int32_t GL_TEXTURE_COORD_ARRAY_POINTER { 32914 };
	static constexpr int32_t GL_TEXTURE_COORD_ARRAY_SIZE { 32904 };
	static constexpr int32_t GL_TEXTURE_COORD_ARRAY_STRIDE { 32906 };
	static constexpr int32_t GL_TEXTURE_COORD_ARRAY_TYPE { 32905 };
	static constexpr int32_t GL_TEXTURE_ENV { 8960 };
	static constexpr int32_t GL_TEXTURE_ENV_COLOR { 8705 };
	static constexpr int32_t GL_TEXTURE_ENV_MODE { 8704 };
	static constexpr int32_t GL_TEXTURE_STACK_DEPTH { 2981 };
	static constexpr int32_t GL_VERTEX_ARRAY_BUFFER_BINDING { 34966 };
	static constexpr int32_t GL_VERTEX_ARRAY_POINTER { 32910 };
	static constexpr int32_t GL_VERTEX_ARRAY_SIZE { 32890 };
	static constexpr int32_t GL_VERTEX_ARRAY_STRIDE { 32892 };
	static constexpr int32_t GL_VERTEX_ARRAY_TYPE { 32891 };

	virtual void glAlphaFunc(int32_t arg0, float arg1) = 0;
	virtual void glClientActiveTexture(int32_t arg0) = 0;
	virtual void glColor4ub(int8_t arg0, int8_t arg1, int8_t arg2, int8_t arg3) = 0;
	virtual void glDrawElements(int32_t arg0, int32_t arg1, int32_t arg2, Buffer* arg3) = 0;
	virtual void glFogf(int32_t arg0, float arg1) = 0;
	virtual void glFogfv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void glFogfv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void glFrustum(double arg0, double arg1, double arg2, double arg3, double arg4, double arg5) = 0;
	virtual void glGetLightfv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void glGetLightfv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void glGetMaterialfv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void glGetMaterialfv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void glGetTexEnvfv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void glGetTexEnvfv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void glGetTexEnviv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glGetTexEnviv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;
	virtual void glLightModelf(int32_t arg0, float arg1) = 0;
	virtual void glLightModelfv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void glLightModelfv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void glLightf(int32_t arg0, int32_t arg1, float arg2) = 0;
	virtual void glLogicOp(int32_t arg0) = 0;
	virtual void glMultiTexCoord4f(int32_t arg0, float arg1, float arg2, float arg3, float arg4) = 0;
	virtual void glNormal3f(float arg0, float arg1, float arg2) = 0;
	virtual void glOrtho(double arg0, double arg1, double arg2, double arg3, double arg4, double arg5) = 0;
	virtual void glPointParameterf(int32_t arg0, float arg1) = 0;
	virtual void glPointParameterfv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void glPointParameterfv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void glPointSize(float arg0) = 0;
	virtual void glTexEnvf(int32_t arg0, int32_t arg1, float arg2) = 0;
	virtual void glTexEnvfv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void glTexEnvfv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void glTexEnvi(int32_t arg0, int32_t arg1, int32_t arg2) = 0;
	virtual void glTexEnviv(int32_t arg0, int32_t arg1, IntBuffer* arg2) = 0;
	virtual void glTexEnviv(int32_t arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3) = 0;

	// Generated
	static ::java::lang::Class *class_();
	virtual void glGetFloatv(int32_t arg0, FloatBuffer* arg1) = 0;
	virtual void glGetFloatv(int32_t arg0, floatArray* arg1, int32_t arg2) = 0;
	virtual void glGetIntegerv(int32_t arg0, IntBuffer* arg1) = 0;
	virtual void glGetIntegerv(int32_t arg0, int32_tArray* arg1, int32_t arg2) = 0;
	virtual void glColor4f(float arg0, float arg1, float arg2, float arg3) = 0;
	virtual void glDrawElements(int32_t arg0, int32_t arg1, int32_t arg2, int64_t arg3) = 0;
};

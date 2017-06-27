// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fixedfunc/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::nio::FloatBuffer;


struct com::jogamp::opengl::fixedfunc::GLLightingFunc
	: public virtual Object
{
	static constexpr int32_t GL_AMBIENT { 4608 };
	static constexpr int32_t GL_AMBIENT_AND_DIFFUSE { 5634 };
	static constexpr int32_t GL_COLOR_MATERIAL { 2903 };
	static constexpr int32_t GL_CONSTANT_ATTENUATION { 4615 };
	static constexpr int32_t GL_DIFFUSE { 4609 };
	static constexpr int32_t GL_EMISSION { 5632 };
	static constexpr int32_t GL_FLAT { 7424 };
	static constexpr int32_t GL_LIGHT0 { 16384 };
	static constexpr int32_t GL_LIGHT1 { 16385 };
	static constexpr int32_t GL_LIGHT2 { 16386 };
	static constexpr int32_t GL_LIGHT3 { 16387 };
	static constexpr int32_t GL_LIGHT4 { 16388 };
	static constexpr int32_t GL_LIGHT5 { 16389 };
	static constexpr int32_t GL_LIGHT6 { 16390 };
	static constexpr int32_t GL_LIGHT7 { 16391 };
	static constexpr int32_t GL_LIGHTING { 2896 };
	static constexpr int32_t GL_LINEAR_ATTENUATION { 4616 };
	static constexpr int32_t GL_NORMALIZE { 2977 };
	static constexpr int32_t GL_POSITION { 4611 };
	static constexpr int32_t GL_QUADRATIC_ATTENUATION { 4617 };
	static constexpr int32_t GL_SHININESS { 5633 };
	static constexpr int32_t GL_SMOOTH { 7425 };
	static constexpr int32_t GL_SPECULAR { 4610 };
	static constexpr int32_t GL_SPOT_CUTOFF { 4614 };
	static constexpr int32_t GL_SPOT_DIRECTION { 4612 };
	static constexpr int32_t GL_SPOT_EXPONENT { 4613 };

	virtual void glColor4f(float arg0, float arg1, float arg2, float arg3) = 0;
	virtual void glLightfv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void glLightfv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void glMaterialf(int32_t arg0, int32_t arg1, float arg2) = 0;
	virtual void glMaterialfv(int32_t arg0, int32_t arg1, FloatBuffer* arg2) = 0;
	virtual void glMaterialfv(int32_t arg0, int32_t arg1, floatArray* arg2, int32_t arg3) = 0;
	virtual void glShadeModel(int32_t arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

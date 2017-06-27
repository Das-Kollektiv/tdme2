// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/DebugGLES3.h>

using com::jogamp::opengl::DebugGLES3;
using com::jogamp::opengl::GLES2;


struct default_init_tag;
class com::jogamp::opengl::DebugGLES2
	: public DebugGLES3
{

public:
	typedef DebugGLES3 super;

protected:
	void ctor(GLES2* arg0);

	// Generated

public:
	DebugGLES2(GLES2* arg0);
protected:
	DebugGLES2(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

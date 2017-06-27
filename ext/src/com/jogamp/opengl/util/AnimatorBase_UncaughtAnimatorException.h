// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/util/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/RuntimeException.h>

using java::lang::RuntimeException;
using com::jogamp::opengl::GLAutoDrawable;
using java::lang::Throwable;


struct default_init_tag;
class com::jogamp::opengl::util::AnimatorBase_UncaughtAnimatorException
	: public RuntimeException
{

public:
	typedef RuntimeException super;

public: /* package */
	GLAutoDrawable* drawable {  };

protected:
	void ctor(GLAutoDrawable* arg0, Throwable* arg1);

public:
	GLAutoDrawable* getGLAutoDrawable();

	// Generated
	AnimatorBase_UncaughtAnimatorException(GLAutoDrawable* arg0, Throwable* arg1);
protected:
	AnimatorBase_UncaughtAnimatorException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

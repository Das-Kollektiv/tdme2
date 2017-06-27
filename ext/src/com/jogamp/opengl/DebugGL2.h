// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/opengl/fwd-tdme.h>
#include <com/jogamp/opengl/DebugGL4bc.h>

using com::jogamp::opengl::DebugGL4bc;
using com::jogamp::opengl::GL2;


struct default_init_tag;
class com::jogamp::opengl::DebugGL2
	: public DebugGL4bc
{

public:
	typedef DebugGL4bc super;

protected:
	void ctor(GL2* arg0);

	// Generated

public:
	DebugGL2(GL2* arg0);
protected:
	DebugGL2(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

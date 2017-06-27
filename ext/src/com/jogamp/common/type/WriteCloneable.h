// Generated from /tdme/lib/gluegen-rt.jar

#pragma once

#include <com/jogamp/common/type/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct com::jogamp::common::type::WriteCloneable
	: public virtual Object
{

	virtual Object* cloneMutable() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

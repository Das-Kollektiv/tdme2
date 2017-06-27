// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::CharSequence;


struct java::lang::Appendable
	: public virtual Object
{

	virtual Appendable* append(CharSequence* arg0) = 0;
	virtual Appendable* append(char16_t arg0) = 0;
	virtual Appendable* append(CharSequence* arg0, int32_t arg1, int32_t arg2) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

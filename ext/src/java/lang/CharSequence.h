// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct java::lang::CharSequence
	: public virtual Object
{

	virtual char16_t charAt(int32_t arg0) = 0;
	virtual int32_t length() = 0;
	virtual CharSequence* subSequence(int32_t arg0, int32_t arg1) = 0;
	/*virtual String* toString(); (already declared) */

	// Generated
	static ::java::lang::Class *class_();

};

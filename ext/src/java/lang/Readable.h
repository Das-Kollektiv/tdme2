// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::nio::CharBuffer;


struct java::lang::Readable
	: public virtual Object
{

	virtual int32_t read(CharBuffer* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

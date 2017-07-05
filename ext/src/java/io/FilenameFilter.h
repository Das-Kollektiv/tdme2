// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::File;
using java::lang::String;


struct java::io::FilenameFilter
	: public virtual Object
{

	virtual bool accept(String* path, String* file) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

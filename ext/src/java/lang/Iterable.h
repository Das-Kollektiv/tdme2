// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::util::Iterator;


struct java::lang::Iterable
	: public virtual Object
{

	virtual Iterator* iterator() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

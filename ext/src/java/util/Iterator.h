// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct java::util::Iterator
	: public virtual Object
{

	virtual bool hasNext() = 0;
	virtual Object* next() = 0;
	virtual void remove() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

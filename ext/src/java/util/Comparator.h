// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct java::util::Comparator
	: public virtual Object
{

	virtual int32_t compare(Object* o1, Object* o2) = 0;
	/*virtual bool equals(Object* obj); (already declared) */

	// Generated
	static ::java::lang::Class *class_();
};

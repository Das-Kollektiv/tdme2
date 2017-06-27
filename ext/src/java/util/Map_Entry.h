// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct java::util::Map_Entry
	: public virtual Object
{

	/*virtual bool equals(Object* arg0); (already declared) */
	virtual Object* getKey() = 0;
	virtual Object* getValue() = 0;
	/*virtual int32_t hashCode(); (already declared) */
	virtual Object* setValue(Object* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

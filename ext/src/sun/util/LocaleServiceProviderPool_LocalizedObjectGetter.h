// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <sun/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::util::Locale;

using java::lang::ObjectArray;

struct sun::util::LocaleServiceProviderPool_LocalizedObjectGetter
	: public virtual Object
{

	virtual Object* getObject(Object* arg0, Locale* arg1, String* arg2, ObjectArray* arg3) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

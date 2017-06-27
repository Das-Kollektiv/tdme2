// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Thread;
using java::lang::Throwable;


struct java::lang::Thread_UncaughtExceptionHandler
	: public virtual Object
{

	virtual void uncaughtException(Thread* arg0, Throwable* arg1) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

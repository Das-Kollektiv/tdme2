// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/concurrent/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::util::Date;
using java::util::concurrent::TimeUnit;


struct java::util::concurrent::locks::Condition
	: public virtual Object
{

	virtual void await() = 0;
	virtual bool await(int64_t arg0, TimeUnit* arg1) = 0;
	virtual int64_t awaitNanos(int64_t arg0) = 0;
	virtual void awaitUninterruptibly() = 0;
	virtual bool awaitUntil(Date* arg0) = 0;
	virtual void signal() = 0;
	virtual void signalAll() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

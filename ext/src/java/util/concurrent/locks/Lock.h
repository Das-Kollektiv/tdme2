// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/util/concurrent/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::util::concurrent::TimeUnit;
using java::util::concurrent::locks::Condition;


struct java::util::concurrent::locks::Lock
	: public virtual Object
{

	virtual void lock() = 0;
	virtual void lockInterruptibly() = 0;
	virtual Condition* newCondition() = 0;
	virtual bool tryLock() = 0;
	virtual bool tryLock(int64_t arg0, TimeUnit* arg1) = 0;
	virtual void unlock() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

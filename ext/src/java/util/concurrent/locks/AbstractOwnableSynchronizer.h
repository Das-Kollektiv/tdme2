// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Thread;


struct default_init_tag;
class java::util::concurrent::locks::AbstractOwnableSynchronizer
	: public virtual Object
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	Thread* exclusiveOwnerThread {  };
	static constexpr int64_t serialVersionUID { 3737899427754241961LL };

protected:
	void ctor();

public: /* protected */
	Thread* getExclusiveOwnerThread();
	void setExclusiveOwnerThread(Thread* arg0);

	// Generated
	AbstractOwnableSynchronizer();
protected:
	AbstractOwnableSynchronizer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

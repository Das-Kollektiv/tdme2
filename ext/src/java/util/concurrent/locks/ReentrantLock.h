// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/concurrent/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/concurrent/locks/Lock.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::util::concurrent::locks::Lock;
using java::io::Serializable;
using java::lang::String;
using java::lang::Thread;
using java::util::Collection;
using java::util::concurrent::TimeUnit;
using java::util::concurrent::locks::Condition;
using java::util::concurrent::locks::ReentrantLock_Sync;


struct default_init_tag;
class java::util::concurrent::locks::ReentrantLock
	: public virtual Object
	, public virtual Lock
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	static constexpr int64_t serialVersionUID { 7373984872572414699LL };
	ReentrantLock_Sync* sync {  };

protected:
	void ctor();
	void ctor(bool arg0);

public:
	virtual int32_t getHoldCount();

public: /* protected */
	virtual Thread* getOwner();

public:
	int32_t getQueueLength();

public: /* protected */
	virtual Collection* getQueuedThreads();

public:
	virtual int32_t getWaitQueueLength(Condition* arg0);

public: /* protected */
	virtual Collection* getWaitingThreads(Condition* arg0);

public:
	bool hasQueuedThread(Thread* arg0);
	bool hasQueuedThreads();
	virtual bool hasWaiters(Condition* arg0);
	bool isFair();
	virtual bool isHeldByCurrentThread();
	virtual bool isLocked();
	void lock() override;
	void lockInterruptibly() override;
	Condition* newCondition() override;
	String* toString() override;
	bool tryLock() override;
	bool tryLock(int64_t arg0, TimeUnit* arg1) override;
	void unlock() override;

	// Generated
	ReentrantLock();
	ReentrantLock(bool arg0);
protected:
	ReentrantLock(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

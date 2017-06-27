// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <java/util/concurrent/locks/AbstractQueuedSynchronizer.h>

using java::util::concurrent::locks::AbstractQueuedSynchronizer;
using java::io::ObjectInputStream;
using java::lang::Thread;
using java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject;


struct default_init_tag;
class java::util::concurrent::locks::ReentrantLock_Sync
	: public AbstractQueuedSynchronizer
{

public:
	typedef AbstractQueuedSynchronizer super;

private:
	static constexpr int64_t serialVersionUID { -5179523762034025860LL };

protected:
	void ctor();

public: /* package */
	int32_t getHoldCount();
	Thread* getOwner();

public: /* protected */
	bool isHeldExclusively() override;

public: /* package */
	bool isLocked();
	virtual void lock() = 0;
	AbstractQueuedSynchronizer_ConditionObject* newCondition();
	bool nonfairTryAcquire(int32_t arg0);
	/*void readObject(ObjectInputStream* arg0); (private) */

public: /* protected */
	bool tryRelease(int32_t arg0) override;

	// Generated

public: /* package */
	ReentrantLock_Sync();
protected:
	ReentrantLock_Sync(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

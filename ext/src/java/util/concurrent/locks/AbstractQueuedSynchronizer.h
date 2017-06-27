// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/concurrent/locks/fwd-tdme.h>
#include <sun/misc/fwd-tdme.h>
#include <java/util/concurrent/locks/AbstractOwnableSynchronizer.h>
#include <java/io/Serializable.h>

using java::util::concurrent::locks::AbstractOwnableSynchronizer;
using java::io::Serializable;
using java::lang::String;
using java::lang::Thread;
using java::util::Collection;
using java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject;
using java::util::concurrent::locks::AbstractQueuedSynchronizer_Node;
using sun::misc::Unsafe;


struct default_init_tag;
class java::util::concurrent::locks::AbstractQueuedSynchronizer
	: public AbstractOwnableSynchronizer
	, public virtual Serializable
{

public:
	typedef AbstractOwnableSynchronizer super;

private:
	std::atomic< AbstractQueuedSynchronizer_Node* > head {  };
	static int64_t headOffset;
	static int64_t nextOffset;
	static constexpr int64_t serialVersionUID { 7373984972572414691LL };

public: /* package */
	static constexpr int64_t spinForTimeoutThreshold { 1000LL };

private:
	std::atomic< int32_t > state {  };
	static int64_t stateOffset;
	std::atomic< AbstractQueuedSynchronizer_Node* > tail {  };
	static int64_t tailOffset;
	static Unsafe* unsafe;
	static int64_t waitStatusOffset;

protected:
	void ctor();

public:
	void acquire(int32_t arg0);
	void acquireInterruptibly(int32_t arg0);

public: /* package */
	bool acquireQueued(AbstractQueuedSynchronizer_Node* arg0, int32_t arg1);

public:
	void acquireShared(int32_t arg0);
	void acquireSharedInterruptibly(int32_t arg0);
	/*AbstractQueuedSynchronizer_Node* addWaiter(AbstractQueuedSynchronizer_Node* arg0); (private) */

public: /* package */
	bool apparentlyFirstQueuedIsExclusive();
	/*void cancelAcquire(AbstractQueuedSynchronizer_Node* arg0); (private) */
	/*bool compareAndSetHead(AbstractQueuedSynchronizer_Node* arg0); (private) */
	/*static bool compareAndSetNext(AbstractQueuedSynchronizer_Node* arg0, AbstractQueuedSynchronizer_Node* arg1, AbstractQueuedSynchronizer_Node* arg2); (private) */

public: /* protected */
	bool compareAndSetState(int32_t arg0, int32_t arg1);
	/*bool compareAndSetTail(AbstractQueuedSynchronizer_Node* arg0, AbstractQueuedSynchronizer_Node* arg1); (private) */
	/*static bool compareAndSetWaitStatus(AbstractQueuedSynchronizer_Node* arg0, int32_t arg1, int32_t arg2); (private) */
	/*void doAcquireInterruptibly(int32_t arg0); (private) */
	/*bool doAcquireNanos(int32_t arg0, int64_t arg1); (private) */
	/*void doAcquireShared(int32_t arg0); (private) */
	/*void doAcquireSharedInterruptibly(int32_t arg0); (private) */
	/*bool doAcquireSharedNanos(int32_t arg0, int64_t arg1); (private) */
	/*void doReleaseShared(); (private) */
	/*AbstractQueuedSynchronizer_Node* enq(AbstractQueuedSynchronizer_Node* arg0); (private) */
	/*bool findNodeFromTail(AbstractQueuedSynchronizer_Node* arg0); (private) */
	/*Thread* fullGetFirstQueuedThread(); (private) */

public: /* package */
	bool fullIsFirst(Thread* arg0);
	int32_t fullyRelease(AbstractQueuedSynchronizer_Node* arg0);

public:
	Collection* getExclusiveQueuedThreads();
	Thread* getFirstQueuedThread();
	int32_t getQueueLength();
	Collection* getQueuedThreads();
	Collection* getSharedQueuedThreads();

public: /* protected */
	int32_t getState();

public:
	int32_t getWaitQueueLength(AbstractQueuedSynchronizer_ConditionObject* arg0);
	Collection* getWaitingThreads(AbstractQueuedSynchronizer_ConditionObject* arg0);
	bool hasContended();
	bool hasQueuedThreads();
	bool hasWaiters(AbstractQueuedSynchronizer_ConditionObject* arg0);

public: /* package */
	bool isFirst(Thread* arg0);

public: /* protected */
	virtual bool isHeldExclusively();

public: /* package */
	bool isOnSyncQueue(AbstractQueuedSynchronizer_Node* arg0);

public:
	bool isQueued(Thread* arg0);
	bool owns(AbstractQueuedSynchronizer_ConditionObject* arg0);
	/*bool parkAndCheckInterrupt(); (private) */
	bool release(int32_t arg0);
	bool releaseShared(int32_t arg0);
	/*static void selfInterrupt(); (private) */
	/*void setHead(AbstractQueuedSynchronizer_Node* arg0); (private) */
	/*void setHeadAndPropagate(AbstractQueuedSynchronizer_Node* arg0, int32_t arg1); (private) */

public: /* protected */
	void setState(int32_t arg0);
	/*static bool shouldParkAfterFailedAcquire(AbstractQueuedSynchronizer_Node* arg0, AbstractQueuedSynchronizer_Node* arg1); (private) */

public:
	String* toString() override;

public: /* package */
	bool transferAfterCancelledWait(AbstractQueuedSynchronizer_Node* arg0);
	bool transferForSignal(AbstractQueuedSynchronizer_Node* arg0);

public: /* protected */
	virtual bool tryAcquire(int32_t arg0);

public:
	bool tryAcquireNanos(int32_t arg0, int64_t arg1);

public: /* protected */
	virtual int32_t tryAcquireShared(int32_t arg0);

public:
	bool tryAcquireSharedNanos(int32_t arg0, int64_t arg1);

public: /* protected */
	virtual bool tryRelease(int32_t arg0);
	virtual bool tryReleaseShared(int32_t arg0);
	/*void unparkSuccessor(AbstractQueuedSynchronizer_Node* arg0); (private) */

	// Generated
	AbstractQueuedSynchronizer();
protected:
	AbstractQueuedSynchronizer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

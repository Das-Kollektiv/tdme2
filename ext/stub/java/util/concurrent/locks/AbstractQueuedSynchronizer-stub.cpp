// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/concurrent/locks/AbstractQueuedSynchronizer.h>

using java::util::concurrent::locks::AbstractQueuedSynchronizer;
extern void unimplemented_(const char16_t* name);
java::util::concurrent::locks::AbstractQueuedSynchronizer::AbstractQueuedSynchronizer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::concurrent::locks::AbstractQueuedSynchronizer::AbstractQueuedSynchronizer()
	: AbstractQueuedSynchronizer(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

int64_t java::util::concurrent::locks::AbstractQueuedSynchronizer::headOffset;
int64_t java::util::concurrent::locks::AbstractQueuedSynchronizer::nextOffset;
constexpr int64_t java::util::concurrent::locks::AbstractQueuedSynchronizer::serialVersionUID;
constexpr int64_t java::util::concurrent::locks::AbstractQueuedSynchronizer::spinForTimeoutThreshold;
int64_t java::util::concurrent::locks::AbstractQueuedSynchronizer::stateOffset;
int64_t java::util::concurrent::locks::AbstractQueuedSynchronizer::tailOffset;
Unsafe* java::util::concurrent::locks::AbstractQueuedSynchronizer::unsafe;
int64_t java::util::concurrent::locks::AbstractQueuedSynchronizer::waitStatusOffset;

void AbstractQueuedSynchronizer::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractQueuedSynchronizer::ctor()");
}

void AbstractQueuedSynchronizer::acquire(int32_t arg0)
{ /* stub */
	unimplemented_(u"void AbstractQueuedSynchronizer::acquire(int32_t arg0)");
}

void AbstractQueuedSynchronizer::acquireInterruptibly(int32_t arg0)
{ /* stub */
	unimplemented_(u"void AbstractQueuedSynchronizer::acquireInterruptibly(int32_t arg0)");
}

bool AbstractQueuedSynchronizer::acquireQueued(AbstractQueuedSynchronizer_Node* arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::acquireQueued(AbstractQueuedSynchronizer_Node* arg0, int32_t arg1)");
	return 0;
}

void AbstractQueuedSynchronizer::acquireShared(int32_t arg0)
{ /* stub */
	unimplemented_(u"void AbstractQueuedSynchronizer::acquireShared(int32_t arg0)");
}

void AbstractQueuedSynchronizer::acquireSharedInterruptibly(int32_t arg0)
{ /* stub */
	unimplemented_(u"void AbstractQueuedSynchronizer::acquireSharedInterruptibly(int32_t arg0)");
}

/* private: AbstractQueuedSynchronizer_Node* AbstractQueuedSynchronizer::addWaiter(AbstractQueuedSynchronizer_Node* arg0) */
bool AbstractQueuedSynchronizer::apparentlyFirstQueuedIsExclusive()
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::apparentlyFirstQueuedIsExclusive()");
	return 0;
}

/* private: void AbstractQueuedSynchronizer::cancelAcquire(AbstractQueuedSynchronizer_Node* arg0) */
/* private: bool AbstractQueuedSynchronizer::compareAndSetHead(AbstractQueuedSynchronizer_Node* arg0) */
/* private: bool AbstractQueuedSynchronizer::compareAndSetNext(AbstractQueuedSynchronizer_Node* arg0, AbstractQueuedSynchronizer_Node* arg1, AbstractQueuedSynchronizer_Node* arg2) */
bool AbstractQueuedSynchronizer::compareAndSetState(int32_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::compareAndSetState(int32_t arg0, int32_t arg1)");
	return 0;
}

/* private: bool AbstractQueuedSynchronizer::compareAndSetTail(AbstractQueuedSynchronizer_Node* arg0, AbstractQueuedSynchronizer_Node* arg1) */
/* private: bool AbstractQueuedSynchronizer::compareAndSetWaitStatus(AbstractQueuedSynchronizer_Node* arg0, int32_t arg1, int32_t arg2) */
/* private: void AbstractQueuedSynchronizer::doAcquireInterruptibly(int32_t arg0) */
/* private: bool AbstractQueuedSynchronizer::doAcquireNanos(int32_t arg0, int64_t arg1) */
/* private: void AbstractQueuedSynchronizer::doAcquireShared(int32_t arg0) */
/* private: void AbstractQueuedSynchronizer::doAcquireSharedInterruptibly(int32_t arg0) */
/* private: bool AbstractQueuedSynchronizer::doAcquireSharedNanos(int32_t arg0, int64_t arg1) */
/* private: void AbstractQueuedSynchronizer::doReleaseShared() */
/* private: AbstractQueuedSynchronizer_Node* AbstractQueuedSynchronizer::enq(AbstractQueuedSynchronizer_Node* arg0) */
/* private: bool AbstractQueuedSynchronizer::findNodeFromTail(AbstractQueuedSynchronizer_Node* arg0) */
/* private: Thread* AbstractQueuedSynchronizer::fullGetFirstQueuedThread() */
bool AbstractQueuedSynchronizer::fullIsFirst(Thread* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::fullIsFirst(Thread* arg0)");
	return 0;
}

int32_t AbstractQueuedSynchronizer::fullyRelease(AbstractQueuedSynchronizer_Node* arg0)
{ /* stub */
	unimplemented_(u"int32_t AbstractQueuedSynchronizer::fullyRelease(AbstractQueuedSynchronizer_Node* arg0)");
	return 0;
}

Collection* AbstractQueuedSynchronizer::getExclusiveQueuedThreads()
{ /* stub */
	unimplemented_(u"Collection* AbstractQueuedSynchronizer::getExclusiveQueuedThreads()");
	return 0;
}

Thread* AbstractQueuedSynchronizer::getFirstQueuedThread()
{ /* stub */
	unimplemented_(u"Thread* AbstractQueuedSynchronizer::getFirstQueuedThread()");
	return 0;
}

int32_t AbstractQueuedSynchronizer::getQueueLength()
{ /* stub */
	unimplemented_(u"int32_t AbstractQueuedSynchronizer::getQueueLength()");
	return 0;
}

Collection* AbstractQueuedSynchronizer::getQueuedThreads()
{ /* stub */
	unimplemented_(u"Collection* AbstractQueuedSynchronizer::getQueuedThreads()");
	return 0;
}

Collection* AbstractQueuedSynchronizer::getSharedQueuedThreads()
{ /* stub */
	unimplemented_(u"Collection* AbstractQueuedSynchronizer::getSharedQueuedThreads()");
	return 0;
}

int32_t AbstractQueuedSynchronizer::getState()
{ /* stub */
return state ; /* getter */
}

int32_t AbstractQueuedSynchronizer::getWaitQueueLength(AbstractQueuedSynchronizer_ConditionObject* arg0)
{ /* stub */
	unimplemented_(u"int32_t AbstractQueuedSynchronizer::getWaitQueueLength(AbstractQueuedSynchronizer_ConditionObject* arg0)");
	return 0;
}

Collection* AbstractQueuedSynchronizer::getWaitingThreads(AbstractQueuedSynchronizer_ConditionObject* arg0)
{ /* stub */
	unimplemented_(u"Collection* AbstractQueuedSynchronizer::getWaitingThreads(AbstractQueuedSynchronizer_ConditionObject* arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::hasContended()
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::hasContended()");
	return 0;
}

bool AbstractQueuedSynchronizer::hasQueuedThreads()
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::hasQueuedThreads()");
	return 0;
}

bool AbstractQueuedSynchronizer::hasWaiters(AbstractQueuedSynchronizer_ConditionObject* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::hasWaiters(AbstractQueuedSynchronizer_ConditionObject* arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::isFirst(Thread* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::isFirst(Thread* arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::isHeldExclusively()
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::isHeldExclusively()");
	return 0;
}

bool AbstractQueuedSynchronizer::isOnSyncQueue(AbstractQueuedSynchronizer_Node* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::isOnSyncQueue(AbstractQueuedSynchronizer_Node* arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::isQueued(Thread* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::isQueued(Thread* arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::owns(AbstractQueuedSynchronizer_ConditionObject* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::owns(AbstractQueuedSynchronizer_ConditionObject* arg0)");
	return 0;
}

/* private: bool AbstractQueuedSynchronizer::parkAndCheckInterrupt() */
bool AbstractQueuedSynchronizer::release(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::release(int32_t arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::releaseShared(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::releaseShared(int32_t arg0)");
	return 0;
}

/* private: void AbstractQueuedSynchronizer::selfInterrupt() */
/* private: void AbstractQueuedSynchronizer::setHead(AbstractQueuedSynchronizer_Node* arg0) */
/* private: void AbstractQueuedSynchronizer::setHeadAndPropagate(AbstractQueuedSynchronizer_Node* arg0, int32_t arg1) */
void AbstractQueuedSynchronizer::setState(int32_t arg0)
{ /* stub */
	this->state = arg0; /* setter */
}

/* private: bool AbstractQueuedSynchronizer::shouldParkAfterFailedAcquire(AbstractQueuedSynchronizer_Node* arg0, AbstractQueuedSynchronizer_Node* arg1) */
String* AbstractQueuedSynchronizer::toString()
{ /* stub */
	unimplemented_(u"String* AbstractQueuedSynchronizer::toString()");
	return 0;
}

bool AbstractQueuedSynchronizer::transferAfterCancelledWait(AbstractQueuedSynchronizer_Node* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::transferAfterCancelledWait(AbstractQueuedSynchronizer_Node* arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::transferForSignal(AbstractQueuedSynchronizer_Node* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::transferForSignal(AbstractQueuedSynchronizer_Node* arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::tryAcquire(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::tryAcquire(int32_t arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::tryAcquireNanos(int32_t arg0, int64_t arg1)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::tryAcquireNanos(int32_t arg0, int64_t arg1)");
	return 0;
}

int32_t AbstractQueuedSynchronizer::tryAcquireShared(int32_t arg0)
{ /* stub */
	unimplemented_(u"int32_t AbstractQueuedSynchronizer::tryAcquireShared(int32_t arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::tryAcquireSharedNanos(int32_t arg0, int64_t arg1)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::tryAcquireSharedNanos(int32_t arg0, int64_t arg1)");
	return 0;
}

bool AbstractQueuedSynchronizer::tryRelease(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::tryRelease(int32_t arg0)");
	return 0;
}

bool AbstractQueuedSynchronizer::tryReleaseShared(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer::tryReleaseShared(int32_t arg0)");
	return 0;
}

/* private: void AbstractQueuedSynchronizer::unparkSuccessor(AbstractQueuedSynchronizer_Node* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractQueuedSynchronizer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.concurrent.locks.AbstractQueuedSynchronizer", 53);
    return c;
}

java::lang::Class* AbstractQueuedSynchronizer::getClass0()
{
	return class_();
}


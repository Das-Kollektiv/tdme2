// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/concurrent/locks/AbstractQueuedSynchronizer_ConditionObject.h>

#include <java/util/concurrent/locks/AbstractQueuedSynchronizer.h>

using java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject;
using java::util::concurrent::locks::AbstractQueuedSynchronizer;

extern void unimplemented_(const char16_t* name);
java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject::AbstractQueuedSynchronizer_ConditionObject(AbstractQueuedSynchronizer *AbstractQueuedSynchronizer_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, AbstractQueuedSynchronizer_this(AbstractQueuedSynchronizer_this)
{
	clinit();
}

java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject::AbstractQueuedSynchronizer_ConditionObject(AbstractQueuedSynchronizer *AbstractQueuedSynchronizer_this)
	: AbstractQueuedSynchronizer_ConditionObject(AbstractQueuedSynchronizer_this, *static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int32_t java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject::REINTERRUPT;
constexpr int32_t java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject::THROW_IE;
constexpr int64_t java::util::concurrent::locks::AbstractQueuedSynchronizer_ConditionObject::serialVersionUID;

void AbstractQueuedSynchronizer_ConditionObject::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractQueuedSynchronizer_ConditionObject::ctor()");
}

/* private: AbstractQueuedSynchronizer_Node* AbstractQueuedSynchronizer_ConditionObject::addConditionWaiter() */
void AbstractQueuedSynchronizer_ConditionObject::await()
{ /* stub */
	unimplemented_(u"void AbstractQueuedSynchronizer_ConditionObject::await()");
}

bool AbstractQueuedSynchronizer_ConditionObject::await(int64_t arg0, TimeUnit* arg1)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer_ConditionObject::await(int64_t arg0, TimeUnit* arg1)");
	return 0;
}

int64_t AbstractQueuedSynchronizer_ConditionObject::awaitNanos(int64_t arg0)
{ /* stub */
	unimplemented_(u"int64_t AbstractQueuedSynchronizer_ConditionObject::awaitNanos(int64_t arg0)");
	return 0;
}

void AbstractQueuedSynchronizer_ConditionObject::awaitUninterruptibly()
{ /* stub */
	unimplemented_(u"void AbstractQueuedSynchronizer_ConditionObject::awaitUninterruptibly()");
}

bool AbstractQueuedSynchronizer_ConditionObject::awaitUntil(Date* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer_ConditionObject::awaitUntil(Date* arg0)");
	return 0;
}

/* private: int32_t AbstractQueuedSynchronizer_ConditionObject::checkInterruptWhileWaiting(AbstractQueuedSynchronizer_Node* arg0) */
/* private: void AbstractQueuedSynchronizer_ConditionObject::doSignal(AbstractQueuedSynchronizer_Node* arg0) */
/* private: void AbstractQueuedSynchronizer_ConditionObject::doSignalAll(AbstractQueuedSynchronizer_Node* arg0) */
int32_t AbstractQueuedSynchronizer_ConditionObject::getWaitQueueLength()
{ /* stub */
	unimplemented_(u"int32_t AbstractQueuedSynchronizer_ConditionObject::getWaitQueueLength()");
	return 0;
}

Collection* AbstractQueuedSynchronizer_ConditionObject::getWaitingThreads()
{ /* stub */
	unimplemented_(u"Collection* AbstractQueuedSynchronizer_ConditionObject::getWaitingThreads()");
	return 0;
}

bool AbstractQueuedSynchronizer_ConditionObject::hasWaiters()
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer_ConditionObject::hasWaiters()");
	return 0;
}

bool AbstractQueuedSynchronizer_ConditionObject::isOwnedBy(AbstractQueuedSynchronizer* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer_ConditionObject::isOwnedBy(AbstractQueuedSynchronizer* arg0)");
	return 0;
}

/* private: void AbstractQueuedSynchronizer_ConditionObject::reportInterruptAfterWait(int32_t arg0) */
void AbstractQueuedSynchronizer_ConditionObject::signal()
{ /* stub */
	unimplemented_(u"void AbstractQueuedSynchronizer_ConditionObject::signal()");
}

void AbstractQueuedSynchronizer_ConditionObject::signalAll()
{ /* stub */
	unimplemented_(u"void AbstractQueuedSynchronizer_ConditionObject::signalAll()");
}

/* private: void AbstractQueuedSynchronizer_ConditionObject::unlinkCancelledWaiters() */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractQueuedSynchronizer_ConditionObject::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.concurrent.locks.AbstractQueuedSynchronizer.ConditionObject", 69);
    return c;
}

java::lang::Class* AbstractQueuedSynchronizer_ConditionObject::getClass0()
{
	return class_();
}


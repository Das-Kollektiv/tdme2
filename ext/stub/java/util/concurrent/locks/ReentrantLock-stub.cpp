// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/concurrent/locks/ReentrantLock.h>

using java::util::concurrent::locks::ReentrantLock;
extern void unimplemented_(const char16_t* name);
java::util::concurrent::locks::ReentrantLock::ReentrantLock(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::concurrent::locks::ReentrantLock::ReentrantLock()
	: ReentrantLock(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::util::concurrent::locks::ReentrantLock::ReentrantLock(bool arg0)
	: ReentrantLock(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int64_t java::util::concurrent::locks::ReentrantLock::serialVersionUID;

void ReentrantLock::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ReentrantLock::ctor()");
}

void ReentrantLock::ctor(bool arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ReentrantLock::ctor(bool arg0)");
}

int32_t ReentrantLock::getHoldCount()
{ /* stub */
	unimplemented_(u"int32_t ReentrantLock::getHoldCount()");
	return 0;
}

Thread* ReentrantLock::getOwner()
{ /* stub */
	unimplemented_(u"Thread* ReentrantLock::getOwner()");
	return 0;
}

int32_t ReentrantLock::getQueueLength()
{ /* stub */
	unimplemented_(u"int32_t ReentrantLock::getQueueLength()");
	return 0;
}

Collection* ReentrantLock::getQueuedThreads()
{ /* stub */
	unimplemented_(u"Collection* ReentrantLock::getQueuedThreads()");
	return 0;
}

int32_t ReentrantLock::getWaitQueueLength(Condition* arg0)
{ /* stub */
	unimplemented_(u"int32_t ReentrantLock::getWaitQueueLength(Condition* arg0)");
	return 0;
}

Collection* ReentrantLock::getWaitingThreads(Condition* arg0)
{ /* stub */
	unimplemented_(u"Collection* ReentrantLock::getWaitingThreads(Condition* arg0)");
	return 0;
}

bool ReentrantLock::hasQueuedThread(Thread* arg0)
{ /* stub */
	unimplemented_(u"bool ReentrantLock::hasQueuedThread(Thread* arg0)");
	return 0;
}

bool ReentrantLock::hasQueuedThreads()
{ /* stub */
	unimplemented_(u"bool ReentrantLock::hasQueuedThreads()");
	return 0;
}

bool ReentrantLock::hasWaiters(Condition* arg0)
{ /* stub */
	unimplemented_(u"bool ReentrantLock::hasWaiters(Condition* arg0)");
	return 0;
}

bool ReentrantLock::isFair()
{ /* stub */
	unimplemented_(u"bool ReentrantLock::isFair()");
	return 0;
}

bool ReentrantLock::isHeldByCurrentThread()
{ /* stub */
	unimplemented_(u"bool ReentrantLock::isHeldByCurrentThread()");
	return 0;
}

bool ReentrantLock::isLocked()
{ /* stub */
	unimplemented_(u"bool ReentrantLock::isLocked()");
	return 0;
}

void ReentrantLock::lock()
{ /* stub */
	unimplemented_(u"void ReentrantLock::lock()");
}

void ReentrantLock::lockInterruptibly()
{ /* stub */
	unimplemented_(u"void ReentrantLock::lockInterruptibly()");
}

Condition* ReentrantLock::newCondition()
{ /* stub */
	unimplemented_(u"Condition* ReentrantLock::newCondition()");
	return 0;
}

String* ReentrantLock::toString()
{ /* stub */
	unimplemented_(u"String* ReentrantLock::toString()");
	return 0;
}

bool ReentrantLock::tryLock()
{ /* stub */
	unimplemented_(u"bool ReentrantLock::tryLock()");
	return 0;
}

bool ReentrantLock::tryLock(int64_t arg0, TimeUnit* arg1)
{ /* stub */
	unimplemented_(u"bool ReentrantLock::tryLock(int64_t arg0, TimeUnit* arg1)");
	return 0;
}

void ReentrantLock::unlock()
{ /* stub */
	unimplemented_(u"void ReentrantLock::unlock()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ReentrantLock::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.concurrent.locks.ReentrantLock", 40);
    return c;
}

java::lang::Class* ReentrantLock::getClass0()
{
	return class_();
}


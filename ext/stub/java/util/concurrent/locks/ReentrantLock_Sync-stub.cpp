// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/concurrent/locks/ReentrantLock_Sync.h>

using java::util::concurrent::locks::ReentrantLock_Sync;
extern void unimplemented_(const char16_t* name);
java::util::concurrent::locks::ReentrantLock_Sync::ReentrantLock_Sync(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::concurrent::locks::ReentrantLock_Sync::ReentrantLock_Sync()
	: ReentrantLock_Sync(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int64_t java::util::concurrent::locks::ReentrantLock_Sync::serialVersionUID;

void ReentrantLock_Sync::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ReentrantLock_Sync::ctor()");
}

int32_t ReentrantLock_Sync::getHoldCount()
{ /* stub */
	unimplemented_(u"int32_t ReentrantLock_Sync::getHoldCount()");
	return 0;
}

Thread* ReentrantLock_Sync::getOwner()
{ /* stub */
	unimplemented_(u"Thread* ReentrantLock_Sync::getOwner()");
	return 0;
}

bool ReentrantLock_Sync::isHeldExclusively()
{ /* stub */
	unimplemented_(u"bool ReentrantLock_Sync::isHeldExclusively()");
	return 0;
}

bool ReentrantLock_Sync::isLocked()
{ /* stub */
	unimplemented_(u"bool ReentrantLock_Sync::isLocked()");
	return 0;
}

AbstractQueuedSynchronizer_ConditionObject* ReentrantLock_Sync::newCondition()
{ /* stub */
	unimplemented_(u"AbstractQueuedSynchronizer_ConditionObject* ReentrantLock_Sync::newCondition()");
	return 0;
}

bool ReentrantLock_Sync::nonfairTryAcquire(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool ReentrantLock_Sync::nonfairTryAcquire(int32_t arg0)");
	return 0;
}

/* private: void ReentrantLock_Sync::readObject(ObjectInputStream* arg0) */
bool ReentrantLock_Sync::tryRelease(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool ReentrantLock_Sync::tryRelease(int32_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ReentrantLock_Sync::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.concurrent.locks.ReentrantLock.Sync", 45);
    return c;
}

java::lang::Class* ReentrantLock_Sync::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/concurrent/locks/ReentrantLock_FairSync.h>

using java::util::concurrent::locks::ReentrantLock_FairSync;
extern void unimplemented_(const char16_t* name);
java::util::concurrent::locks::ReentrantLock_FairSync::ReentrantLock_FairSync(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::concurrent::locks::ReentrantLock_FairSync::ReentrantLock_FairSync()
	: ReentrantLock_FairSync(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int64_t java::util::concurrent::locks::ReentrantLock_FairSync::serialVersionUID;

void ReentrantLock_FairSync::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ReentrantLock_FairSync::ctor()");
}

void ReentrantLock_FairSync::lock()
{ /* stub */
	unimplemented_(u"void ReentrantLock_FairSync::lock()");
}

bool ReentrantLock_FairSync::tryAcquire(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool ReentrantLock_FairSync::tryAcquire(int32_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ReentrantLock_FairSync::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.concurrent.locks.ReentrantLock.FairSync", 49);
    return c;
}

java::lang::Class* ReentrantLock_FairSync::getClass0()
{
	return class_();
}


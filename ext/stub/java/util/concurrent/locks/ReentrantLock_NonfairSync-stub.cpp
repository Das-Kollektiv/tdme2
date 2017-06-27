// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/concurrent/locks/ReentrantLock_NonfairSync.h>

using java::util::concurrent::locks::ReentrantLock_NonfairSync;
extern void unimplemented_(const char16_t* name);
java::util::concurrent::locks::ReentrantLock_NonfairSync::ReentrantLock_NonfairSync(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::concurrent::locks::ReentrantLock_NonfairSync::ReentrantLock_NonfairSync()
	: ReentrantLock_NonfairSync(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int64_t java::util::concurrent::locks::ReentrantLock_NonfairSync::serialVersionUID;

void ReentrantLock_NonfairSync::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ReentrantLock_NonfairSync::ctor()");
}

void ReentrantLock_NonfairSync::lock()
{ /* stub */
	unimplemented_(u"void ReentrantLock_NonfairSync::lock()");
}

bool ReentrantLock_NonfairSync::tryAcquire(int32_t arg0)
{ /* stub */
	unimplemented_(u"bool ReentrantLock_NonfairSync::tryAcquire(int32_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ReentrantLock_NonfairSync::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.concurrent.locks.ReentrantLock.NonfairSync", 52);
    return c;
}

java::lang::Class* ReentrantLock_NonfairSync::getClass0()
{
	return class_();
}


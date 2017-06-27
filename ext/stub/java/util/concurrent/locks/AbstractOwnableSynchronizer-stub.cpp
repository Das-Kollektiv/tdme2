// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/concurrent/locks/AbstractOwnableSynchronizer.h>

using java::util::concurrent::locks::AbstractOwnableSynchronizer;
extern void unimplemented_(const char16_t* name);
java::util::concurrent::locks::AbstractOwnableSynchronizer::AbstractOwnableSynchronizer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::concurrent::locks::AbstractOwnableSynchronizer::AbstractOwnableSynchronizer()
	: AbstractOwnableSynchronizer(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int64_t java::util::concurrent::locks::AbstractOwnableSynchronizer::serialVersionUID;

void AbstractOwnableSynchronizer::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractOwnableSynchronizer::ctor()");
}

Thread* AbstractOwnableSynchronizer::getExclusiveOwnerThread()
{ /* stub */
return exclusiveOwnerThread ; /* getter */
}

void AbstractOwnableSynchronizer::setExclusiveOwnerThread(Thread* arg0)
{ /* stub */
	this->exclusiveOwnerThread = arg0; /* setter */
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractOwnableSynchronizer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.concurrent.locks.AbstractOwnableSynchronizer", 54);
    return c;
}

java::lang::Class* AbstractOwnableSynchronizer::getClass0()
{
	return class_();
}


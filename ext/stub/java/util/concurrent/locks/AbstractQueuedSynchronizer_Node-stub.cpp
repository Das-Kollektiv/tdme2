// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/concurrent/locks/AbstractQueuedSynchronizer_Node.h>

using java::util::concurrent::locks::AbstractQueuedSynchronizer_Node;
extern void unimplemented_(const char16_t* name);
java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::AbstractQueuedSynchronizer_Node(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::AbstractQueuedSynchronizer_Node()
	: AbstractQueuedSynchronizer_Node(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::AbstractQueuedSynchronizer_Node(Thread* arg0, AbstractQueuedSynchronizer_Node* arg1)
	: AbstractQueuedSynchronizer_Node(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::AbstractQueuedSynchronizer_Node(Thread* arg0, int32_t arg1)
	: AbstractQueuedSynchronizer_Node(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int32_t java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::CANCELLED;
constexpr int32_t java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::CONDITION;
AbstractQueuedSynchronizer_Node* java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::EXCLUSIVE;
constexpr int32_t java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::PROPAGATE;
AbstractQueuedSynchronizer_Node* java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::SHARED;
constexpr int32_t java::util::concurrent::locks::AbstractQueuedSynchronizer_Node::SIGNAL;

void AbstractQueuedSynchronizer_Node::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractQueuedSynchronizer_Node::ctor()");
}

void AbstractQueuedSynchronizer_Node::ctor(Thread* arg0, AbstractQueuedSynchronizer_Node* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractQueuedSynchronizer_Node::ctor(Thread* arg0, AbstractQueuedSynchronizer_Node* arg1)");
}

void AbstractQueuedSynchronizer_Node::ctor(Thread* arg0, int32_t arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractQueuedSynchronizer_Node::ctor(Thread* arg0, int32_t arg1)");
}

bool AbstractQueuedSynchronizer_Node::isShared()
{ /* stub */
	unimplemented_(u"bool AbstractQueuedSynchronizer_Node::isShared()");
	return 0;
}

AbstractQueuedSynchronizer_Node* AbstractQueuedSynchronizer_Node::predecessor()
{ /* stub */
	unimplemented_(u"AbstractQueuedSynchronizer_Node* AbstractQueuedSynchronizer_Node::predecessor()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractQueuedSynchronizer_Node::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.concurrent.locks.AbstractQueuedSynchronizer.Node", 58);
    return c;
}

java::lang::Class* AbstractQueuedSynchronizer_Node::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/EventObject.h>

using java::util::EventObject;
extern void unimplemented_(const char16_t* name);
java::util::EventObject::EventObject(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::EventObject::EventObject(Object* arg0)
	: EventObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int64_t java::util::EventObject::serialVersionUID;

void EventObject::ctor(Object* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void EventObject::ctor(Object* arg0)");
}

Object* EventObject::getSource()
{ /* stub */
return source ; /* getter */
}

String* EventObject::toString()
{ /* stub */
	unimplemented_(u"String* EventObject::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* EventObject::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.EventObject", 21);
    return c;
}

java::lang::Class* EventObject::getClass0()
{
	return class_();
}


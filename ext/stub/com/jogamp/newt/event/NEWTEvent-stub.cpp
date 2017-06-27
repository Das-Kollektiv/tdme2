// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/newt/event/NEWTEvent.h>

using com::jogamp::newt::event::NEWTEvent;
extern void unimplemented_(const char16_t* name);
com::jogamp::newt::event::NEWTEvent::NEWTEvent(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

com::jogamp::newt::event::NEWTEvent::NEWTEvent(int16_t arg0, Object* arg1, int64_t arg2)
	: NEWTEvent(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}

constexpr bool com::jogamp::newt::event::NEWTEvent::DEBUG;
Object* com::jogamp::newt::event::NEWTEvent::consumedTag;

void NEWTEvent::ctor(int16_t arg0, Object* arg1, int64_t arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void NEWTEvent::ctor(int16_t arg0, Object* arg1, int64_t arg2)");
}

Object* NEWTEvent::getAttachment()
{ /* stub */
return attachment ; /* getter */
}

int16_t NEWTEvent::getEventType()
{ /* stub */
return eventType ; /* getter */
}

int64_t NEWTEvent::getWhen()
{ /* stub */
return when ; /* getter */
}

bool NEWTEvent::isConsumed()
{ /* stub */
	unimplemented_(u"bool NEWTEvent::isConsumed()");
	return 0;
}

void NEWTEvent::setAttachment(Object* arg0)
{ /* stub */
	this->attachment = arg0; /* setter */
}

void NEWTEvent::setConsumed(bool arg0)
{ /* stub */
	unimplemented_(u"void NEWTEvent::setConsumed(bool arg0)");
}

String* NEWTEvent::toHexString(int16_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* NEWTEvent::toHexString(int16_t arg0)");
	return 0;
}

String* NEWTEvent::toString()
{ /* stub */
	unimplemented_(u"String* NEWTEvent::toString()");
	return 0;
}

StringBuilder* NEWTEvent::toString(StringBuilder* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* NEWTEvent::toString(StringBuilder* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* NEWTEvent::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.newt.event.NEWTEvent", 31);
    return c;
}

java::lang::Class* NEWTEvent::getClass0()
{
	return class_();
}


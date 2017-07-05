// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Object.h>

using java::lang::Object;

extern void unimplemented_(const char16_t* name);
java::lang::Object::Object(const ::default_init_tag&)
{
	clinit();
}

java::lang::Object::Object()
	: Object(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void Object::ctor()
{ /* stub */
	// unimplemented_(u"void Object::ctor()");
}

bool Object::equals(Object* arg0)
{ /* stub */
	return this == arg0;
}

void Object::finalize()
{ /* stub */
	unimplemented_(u"void Object::finalize()");
}

String* Object::toString()
{ /* stub */
	unimplemented_(u"String* Object::toString()");
	return 0;
}

void Object::wait()
{ /* stub */
	unimplemented_(u"void Object::wait()");
}

void Object::wait(int64_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"void Object::wait(int64_t arg0, int32_t arg1)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Object::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Object", 16);
    return c;
}

void Object::clinit()
{
}

java::lang::Object::~Object()
{
}

java::lang::Class* Object::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Enum.h>

using java::lang::Enum;
extern void unimplemented_(const char16_t* name);
java::lang::Enum::Enum(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Enum::Enum(String* arg0, int32_t arg1)
	: Enum(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}


void Enum::ctor(String* arg0, int32_t arg1)
{ /* stub */
	/* super::ctor(); */
	// unimplemented_(u"void Enum::ctor(String* arg0, int32_t arg1)");
}

Object* Enum::clone()
{ /* stub */
	unimplemented_(u"Object* Enum::clone()");
	return 0;
}

int32_t Enum::compareTo(Enum* arg0)
{ /* stub */
	unimplemented_(u"int32_t Enum::compareTo(Enum* arg0)");
	return 0;
}

int32_t Enum::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< Enum* >(o));
}

bool Enum::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Enum::equals(Object* arg0)");
	return 0;
}

void Enum::finalize()
{ /* stub */
	unimplemented_(u"void Enum::finalize()");
}

Class* Enum::getDeclaringClass()
{ /* stub */
	unimplemented_(u"Class* Enum::getDeclaringClass()");
	return 0;
}

int32_t Enum::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Enum::hashCode()");
	return 0;
}

String* Enum::name()
{ /* stub */
	unimplemented_(u"String* Enum::name()");
	return 0;
}

int32_t Enum::ordinal()
{ /* stub */
	unimplemented_(u"int32_t Enum::ordinal()");
	return 0;
}

/* private: void Enum::readObject(ObjectInputStream* arg0) */
/* private: void Enum::readObjectNoData() */
String* Enum::toString()
{ /* stub */
	unimplemented_(u"String* Enum::toString()");
	return 0;
}

Enum* Enum::valueOf(Class* arg0, String* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"Enum* Enum::valueOf(Class* arg0, String* arg1)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Enum::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Enum", 14);
    return c;
}

java::lang::Class* Enum::getClass0()
{
	return class_();
}


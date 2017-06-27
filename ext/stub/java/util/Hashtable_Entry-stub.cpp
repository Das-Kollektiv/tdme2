// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Hashtable_Entry.h>

using java::util::Hashtable_Entry;
extern void unimplemented_(const char16_t* name);
java::util::Hashtable_Entry::Hashtable_Entry(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::Hashtable_Entry::Hashtable_Entry(int32_t arg0, Object* arg1, Object* arg2, Hashtable_Entry* arg3)
	: Hashtable_Entry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}


void Hashtable_Entry::ctor(int32_t arg0, Object* arg1, Object* arg2, Hashtable_Entry* arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Hashtable_Entry::ctor(int32_t arg0, Object* arg1, Object* arg2, Hashtable_Entry* arg3)");
}

Object* Hashtable_Entry::clone()
{ /* stub */
	unimplemented_(u"Object* Hashtable_Entry::clone()");
	return 0;
}

bool Hashtable_Entry::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable_Entry::equals(Object* arg0)");
	return 0;
}

Object* Hashtable_Entry::getKey()
{ /* stub */
return key ; /* getter */
}

Object* Hashtable_Entry::getValue()
{ /* stub */
return value ; /* getter */
}

int32_t Hashtable_Entry::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Hashtable_Entry::hashCode()");
	return 0;
}

Object* Hashtable_Entry::setValue(Object* arg0)
{ /* stub */
}

String* Hashtable_Entry::toString()
{ /* stub */
	unimplemented_(u"String* Hashtable_Entry::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Hashtable_Entry::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Hashtable.Entry", 25);
    return c;
}

java::lang::Class* Hashtable_Entry::getClass0()
{
	return class_();
}


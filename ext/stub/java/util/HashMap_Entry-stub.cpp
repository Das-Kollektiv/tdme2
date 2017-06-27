// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashMap_Entry.h>

using java::util::HashMap_Entry;
extern void unimplemented_(const char16_t* name);
java::util::HashMap_Entry::HashMap_Entry(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::HashMap_Entry::HashMap_Entry(int32_t arg0, Object* arg1, Object* arg2, HashMap_Entry* arg3)
	: HashMap_Entry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}


void HashMap_Entry::ctor(int32_t arg0, Object* arg1, Object* arg2, HashMap_Entry* arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashMap_Entry::ctor(int32_t arg0, Object* arg1, Object* arg2, HashMap_Entry* arg3)");
}

bool HashMap_Entry::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashMap_Entry::equals(Object* arg0)");
	return 0;
}

Object* HashMap_Entry::getKey()
{ /* stub */
return key ; /* getter */
}

Object* HashMap_Entry::getValue()
{ /* stub */
return value ; /* getter */
}

int32_t HashMap_Entry::hashCode()
{ /* stub */
	unimplemented_(u"int32_t HashMap_Entry::hashCode()");
	return 0;
}

void HashMap_Entry::recordAccess(HashMap* arg0)
{ /* stub */
	unimplemented_(u"void HashMap_Entry::recordAccess(HashMap* arg0)");
}

void HashMap_Entry::recordRemoval(HashMap* arg0)
{ /* stub */
	unimplemented_(u"void HashMap_Entry::recordRemoval(HashMap* arg0)");
}

Object* HashMap_Entry::setValue(Object* arg0)
{ /* stub */
}

String* HashMap_Entry::toString()
{ /* stub */
	unimplemented_(u"String* HashMap_Entry::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashMap_Entry::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashMap.Entry", 23);
    return c;
}

java::lang::Class* HashMap_Entry::getClass0()
{
	return class_();
}


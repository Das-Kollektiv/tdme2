// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/AbstractMap_SimpleEntry.h>

using java::util::AbstractMap_SimpleEntry;
extern void unimplemented_(const char16_t* name);
java::util::AbstractMap_SimpleEntry::AbstractMap_SimpleEntry(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::AbstractMap_SimpleEntry::AbstractMap_SimpleEntry(Map_Entry* arg0)
	: AbstractMap_SimpleEntry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::AbstractMap_SimpleEntry::AbstractMap_SimpleEntry(Object* arg0, Object* arg1)
	: AbstractMap_SimpleEntry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::util::AbstractMap_SimpleEntry::serialVersionUID;

void AbstractMap_SimpleEntry::ctor(Map_Entry* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractMap_SimpleEntry::ctor(Map_Entry* arg0)");
}

void AbstractMap_SimpleEntry::ctor(Object* arg0, Object* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractMap_SimpleEntry::ctor(Object* arg0, Object* arg1)");
}

bool AbstractMap_SimpleEntry::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractMap_SimpleEntry::equals(Object* arg0)");
	return 0;
}

Object* AbstractMap_SimpleEntry::getKey()
{ /* stub */
return key ; /* getter */
}

Object* AbstractMap_SimpleEntry::getValue()
{ /* stub */
return value ; /* getter */
}

int32_t AbstractMap_SimpleEntry::hashCode()
{ /* stub */
	unimplemented_(u"int32_t AbstractMap_SimpleEntry::hashCode()");
	return 0;
}

Object* AbstractMap_SimpleEntry::setValue(Object* arg0)
{ /* stub */
}

String* AbstractMap_SimpleEntry::toString()
{ /* stub */
	unimplemented_(u"String* AbstractMap_SimpleEntry::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractMap_SimpleEntry::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.AbstractMap.SimpleEntry", 33);
    return c;
}

java::lang::Class* AbstractMap_SimpleEntry::getClass0()
{
	return class_();
}


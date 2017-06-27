// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/AbstractMap_SimpleImmutableEntry.h>

using java::util::AbstractMap_SimpleImmutableEntry;
extern void unimplemented_(const char16_t* name);
java::util::AbstractMap_SimpleImmutableEntry::AbstractMap_SimpleImmutableEntry(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::AbstractMap_SimpleImmutableEntry::AbstractMap_SimpleImmutableEntry(Map_Entry* arg0)
	: AbstractMap_SimpleImmutableEntry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::AbstractMap_SimpleImmutableEntry::AbstractMap_SimpleImmutableEntry(Object* arg0, Object* arg1)
	: AbstractMap_SimpleImmutableEntry(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::util::AbstractMap_SimpleImmutableEntry::serialVersionUID;

void AbstractMap_SimpleImmutableEntry::ctor(Map_Entry* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractMap_SimpleImmutableEntry::ctor(Map_Entry* arg0)");
}

void AbstractMap_SimpleImmutableEntry::ctor(Object* arg0, Object* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractMap_SimpleImmutableEntry::ctor(Object* arg0, Object* arg1)");
}

bool AbstractMap_SimpleImmutableEntry::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractMap_SimpleImmutableEntry::equals(Object* arg0)");
	return 0;
}

Object* AbstractMap_SimpleImmutableEntry::getKey()
{ /* stub */
return key ; /* getter */
}

Object* AbstractMap_SimpleImmutableEntry::getValue()
{ /* stub */
return value ; /* getter */
}

int32_t AbstractMap_SimpleImmutableEntry::hashCode()
{ /* stub */
	unimplemented_(u"int32_t AbstractMap_SimpleImmutableEntry::hashCode()");
	return 0;
}

Object* AbstractMap_SimpleImmutableEntry::setValue(Object* arg0)
{ /* stub */
}

String* AbstractMap_SimpleImmutableEntry::toString()
{ /* stub */
	unimplemented_(u"String* AbstractMap_SimpleImmutableEntry::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractMap_SimpleImmutableEntry::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.AbstractMap.SimpleImmutableEntry", 42);
    return c;
}

java::lang::Class* AbstractMap_SimpleImmutableEntry::getClass0()
{
	return class_();
}


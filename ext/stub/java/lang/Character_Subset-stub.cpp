// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Character_Subset.h>

using java::lang::Character_Subset;
extern void unimplemented_(const char16_t* name);
java::lang::Character_Subset::Character_Subset(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Character_Subset::Character_Subset(String* name)
	: Character_Subset(*static_cast< ::default_init_tag* >(0))
{
	ctor(name);
}


void Character_Subset::ctor(String* name)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Character_Subset::ctor(String* name)");
}

bool Character_Subset::equals(Object* obj)
{ /* stub */
	unimplemented_(u"bool Character_Subset::equals(Object* obj)");
	return 0;
}

int32_t Character_Subset::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Character_Subset::hashCode()");
	return 0;
}

String* Character_Subset::toString()
{ /* stub */
	unimplemented_(u"String* Character_Subset::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Character_Subset::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Character.Subset", 26);
    return c;
}

java::lang::Class* Character_Subset::getClass0()
{
	return class_();
}


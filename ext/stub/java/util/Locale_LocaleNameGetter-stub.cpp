// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Locale_LocaleNameGetter.h>

#include <java/lang/String.h>
#include <java/util/spi/LocaleNameProvider.h>

using java::util::Locale_LocaleNameGetter;
using java::lang::String;
using java::util::spi::LocaleNameProvider;

extern void unimplemented_(const char16_t* name);
java::util::Locale_LocaleNameGetter::Locale_LocaleNameGetter(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

bool java::util::Locale_LocaleNameGetter::$assertionsDisabled;
Locale_LocaleNameGetter* java::util::Locale_LocaleNameGetter::INSTANCE;

/* private: void Locale_LocaleNameGetter::ctor() */
String* Locale_LocaleNameGetter::getObject(LocaleNameProvider* arg0, Locale* arg1, String* arg2, ObjectArray* arg3)
{ /* stub */
	unimplemented_(u"String* Locale_LocaleNameGetter::getObject(LocaleNameProvider* arg0, Locale* arg1, String* arg2, ObjectArray* arg3)");
	return 0;
}

Object* Locale_LocaleNameGetter::getObject(Object* arg0, Locale* arg1, String* arg2, ObjectArray* arg3)
{ 
	return getObject(dynamic_cast< LocaleNameProvider* >(arg0), arg1, arg2, arg3);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Locale_LocaleNameGetter::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Locale.LocaleNameGetter", 33);
    return c;
}

java::lang::Class* Locale_LocaleNameGetter::getClass0()
{
	return class_();
}


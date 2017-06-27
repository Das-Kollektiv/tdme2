// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/spi/LocaleNameProvider.h>

using java::util::spi::LocaleNameProvider;
extern void unimplemented_(const char16_t* name);
java::util::spi::LocaleNameProvider::LocaleNameProvider(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::spi::LocaleNameProvider::LocaleNameProvider()
	: LocaleNameProvider(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void LocaleNameProvider::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void LocaleNameProvider::ctor()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LocaleNameProvider::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.spi.LocaleNameProvider", 32);
    return c;
}

java::lang::Class* LocaleNameProvider::getClass0()
{
	return class_();
}


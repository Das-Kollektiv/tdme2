// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/spi/LocaleServiceProvider.h>

using java::util::spi::LocaleServiceProvider;
extern void unimplemented_(const char16_t* name);
java::util::spi::LocaleServiceProvider::LocaleServiceProvider(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::spi::LocaleServiceProvider::LocaleServiceProvider()
	: LocaleServiceProvider(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void LocaleServiceProvider::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void LocaleServiceProvider::ctor()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LocaleServiceProvider::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.spi.LocaleServiceProvider", 35);
    return c;
}

java::lang::Class* LocaleServiceProvider::getClass0()
{
	return class_();
}


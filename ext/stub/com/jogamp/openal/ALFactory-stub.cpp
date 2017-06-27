// Generated from /tdme/lib/joal.jar
#include <com/jogamp/openal/ALFactory.h>

using com::jogamp::openal::ALFactory;
extern void unimplemented_(const char16_t* name);
com::jogamp::openal::ALFactory::ALFactory(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

bool com::jogamp::openal::ALFactory::DEBUG;
bool com::jogamp::openal::ALFactory::PREFER_SYSTEM_OPENAL;
AL* com::jogamp::openal::ALFactory::al;
ALC* com::jogamp::openal::ALFactory::alc;
ALExt* com::jogamp::openal::ALFactory::alext;
bool com::jogamp::openal::ALFactory::initialized;

/* private: void ALFactory::ctor() */
AL* ALFactory::getAL()
{ /* stub */
	clinit();
	unimplemented_(u"AL* ALFactory::getAL()");
	return 0;
}

ALC* ALFactory::getALC()
{ /* stub */
	clinit();
	unimplemented_(u"ALC* ALFactory::getALC()");
	return 0;
}

ALExt* ALFactory::getALExt()
{ /* stub */
	clinit();
	unimplemented_(u"ALExt* ALFactory::getALExt()");
	return 0;
}

bool ALFactory::getPreferSystemOpenAL()
{ /* stub */
	clinit();
	unimplemented_(u"bool ALFactory::getPreferSystemOpenAL()");
	return 0;
}

/* private: void ALFactory::initialize() */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ALFactory::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.openal.ALFactory", 27);
    return c;
}

java::lang::Class* ALFactory::getClass0()
{
	return class_();
}


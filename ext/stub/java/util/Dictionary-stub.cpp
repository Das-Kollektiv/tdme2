// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Dictionary.h>

using java::util::Dictionary;
extern void unimplemented_(const char16_t* name);
java::util::Dictionary::Dictionary(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::Dictionary::Dictionary()
	: Dictionary(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void Dictionary::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Dictionary::ctor()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Dictionary::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Dictionary", 20);
    return c;
}

java::lang::Class* Dictionary::getClass0()
{
	return class_();
}


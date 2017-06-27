// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/security/ProtectionDomain_Key.h>

#include <java/security/ProtectionDomain.h>

using java::security::ProtectionDomain_Key;
using java::security::ProtectionDomain;

extern void unimplemented_(const char16_t* name);
java::security::ProtectionDomain_Key::ProtectionDomain_Key(ProtectionDomain *ProtectionDomain_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, ProtectionDomain_this(ProtectionDomain_this)
{
	clinit();
}

java::security::ProtectionDomain_Key::ProtectionDomain_Key(ProtectionDomain *ProtectionDomain_this)
	: ProtectionDomain_Key(ProtectionDomain_this, *static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void ProtectionDomain_Key::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ProtectionDomain_Key::ctor()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ProtectionDomain_Key::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.security.ProtectionDomain.Key", 34);
    return c;
}

java::lang::Class* ProtectionDomain_Key::getClass0()
{
	return class_();
}


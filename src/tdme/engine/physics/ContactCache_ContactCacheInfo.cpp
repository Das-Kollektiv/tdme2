// Generated from /tdme/src/tdme/engine/physics/ContactCache.java
#include <tdme/engine/physics/ContactCache_ContactCacheInfo.h>

using tdme::engine::physics::ContactCache_ContactCacheInfo;
ContactCache_ContactCacheInfo::ContactCache_ContactCacheInfo(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ContactCache_ContactCacheInfo::ContactCache_ContactCacheInfo()
	: ContactCache_ContactCacheInfo(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ContactCache_ContactCacheInfo::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.ContactCache.ContactCacheInfo", 49);
    return c;
}

java::lang::Class* ContactCache_ContactCacheInfo::getClass0()
{
	return class_();
}


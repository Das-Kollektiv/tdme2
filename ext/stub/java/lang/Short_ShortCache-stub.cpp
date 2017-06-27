// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Short_ShortCache.h>

using java::lang::Short_ShortCache;
extern void unimplemented_(const char16_t* name);
java::lang::Short_ShortCache::Short_ShortCache(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ShortArray* java::lang::Short_ShortCache::cache;

/* private: void Short_ShortCache::ctor() */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Short_ShortCache::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Short.ShortCache", 26);
    return c;
}

java::lang::Class* Short_ShortCache::getClass0()
{
	return class_();
}


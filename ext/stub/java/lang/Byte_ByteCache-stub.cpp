// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Byte_ByteCache.h>

using java::lang::Byte_ByteCache;
extern void unimplemented_(const char16_t* name);
java::lang::Byte_ByteCache::Byte_ByteCache(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ByteArray* java::lang::Byte_ByteCache::cache;

/* private: void Byte_ByteCache::ctor() */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Byte_ByteCache::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Byte.ByteCache", 24);
    return c;
}

java::lang::Class* Byte_ByteCache::getClass0()
{
	return class_();
}


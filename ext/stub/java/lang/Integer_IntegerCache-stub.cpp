// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Integer_IntegerCache.h>

using java::lang::Integer_IntegerCache;
extern void unimplemented_(const char16_t* name);
java::lang::Integer_IntegerCache::Integer_IntegerCache(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

IntegerArray* java::lang::Integer_IntegerCache::cache;
int32_t java::lang::Integer_IntegerCache::high;

/* private: void Integer_IntegerCache::ctor() */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Integer_IntegerCache::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Integer.IntegerCache", 30);
    return c;
}

java::lang::Class* Integer_IntegerCache::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Character_CharacterCache.h>

using java::lang::Character_CharacterCache;
extern void unimplemented_(const char16_t* name);
java::lang::Character_CharacterCache::Character_CharacterCache(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

CharacterArray* java::lang::Character_CharacterCache::cache;

/* private: void Character_CharacterCache::ctor() */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Character_CharacterCache::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Character.CharacterCache", 34);
    return c;
}

java::lang::Class* Character_CharacterCache::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashMap_KeyIterator.h>

#include <java/util/HashMap.h>

using java::util::HashMap_KeyIterator;
using java::util::HashMap;

extern void unimplemented_(const char16_t* name);
java::util::HashMap_KeyIterator::HashMap_KeyIterator(HashMap *HashMap_this, const ::default_init_tag&)
	: super(HashMap_this, *static_cast< ::default_init_tag* >(0))
{
	clinit();
}


/* private: void HashMap_KeyIterator::ctor() */
Object* HashMap_KeyIterator::next()
{ /* stub */
	unimplemented_(u"Object* HashMap_KeyIterator::next()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashMap_KeyIterator::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashMap.KeyIterator", 29);
    return c;
}

java::lang::Class* HashMap_KeyIterator::getClass0()
{
	return class_();
}


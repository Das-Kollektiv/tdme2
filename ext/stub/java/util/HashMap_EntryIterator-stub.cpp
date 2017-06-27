// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashMap_EntryIterator.h>

#include <java/util/HashMap.h>

using java::util::HashMap_EntryIterator;
using java::util::HashMap;

extern void unimplemented_(const char16_t* name);
java::util::HashMap_EntryIterator::HashMap_EntryIterator(HashMap *HashMap_this, const ::default_init_tag&)
	: super(HashMap_this, *static_cast< ::default_init_tag* >(0))
{
	clinit();
}


/* private: void HashMap_EntryIterator::ctor() */
Map_Entry* HashMap_EntryIterator::next()
{ /* stub */
	unimplemented_(u"Map_Entry* HashMap_EntryIterator::next()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashMap_EntryIterator::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashMap.EntryIterator", 31);
    return c;
}

java::lang::Class* HashMap_EntryIterator::getClass0()
{
	return class_();
}


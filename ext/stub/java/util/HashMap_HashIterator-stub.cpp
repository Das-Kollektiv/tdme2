// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashMap_HashIterator.h>

#include <java/util/HashMap.h>

using java::util::HashMap_HashIterator;
using java::util::HashMap;

extern void unimplemented_(const char16_t* name);
java::util::HashMap_HashIterator::HashMap_HashIterator(HashMap *HashMap_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, HashMap_this(HashMap_this)
{
	clinit();
}

java::util::HashMap_HashIterator::HashMap_HashIterator(HashMap *HashMap_this)
	: HashMap_HashIterator(HashMap_this, *static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void HashMap_HashIterator::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashMap_HashIterator::ctor()");
}

bool HashMap_HashIterator::hasNext()
{ /* stub */
	unimplemented_(u"bool HashMap_HashIterator::hasNext()");
	return 0;
}

HashMap_Entry* HashMap_HashIterator::nextEntry()
{ /* stub */
	unimplemented_(u"HashMap_Entry* HashMap_HashIterator::nextEntry()");
	return 0;
}

void HashMap_HashIterator::remove()
{ /* stub */
	unimplemented_(u"void HashMap_HashIterator::remove()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashMap_HashIterator::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashMap.HashIterator", 30);
    return c;
}

java::lang::Class* HashMap_HashIterator::getClass0()
{
	return class_();
}


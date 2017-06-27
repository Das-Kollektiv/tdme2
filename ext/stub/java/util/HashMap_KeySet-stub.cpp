// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashMap_KeySet.h>

#include <java/util/HashMap.h>

using java::util::HashMap_KeySet;
using java::util::HashMap;

extern void unimplemented_(const char16_t* name);
java::util::HashMap_KeySet::HashMap_KeySet(HashMap *HashMap_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, HashMap_this(HashMap_this)
{
	clinit();
}


/* private: void HashMap_KeySet::ctor() */
void HashMap_KeySet::clear()
{ /* stub */
	unimplemented_(u"void HashMap_KeySet::clear()");
}

bool HashMap_KeySet::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashMap_KeySet::contains(Object* arg0)");
	return 0;
}

Iterator* HashMap_KeySet::iterator()
{ /* stub */
	unimplemented_(u"Iterator* HashMap_KeySet::iterator()");
	return 0;
}

bool HashMap_KeySet::remove(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashMap_KeySet::remove(Object* arg0)");
	return 0;
}

int32_t HashMap_KeySet::size()
{ /* stub */
	unimplemented_(u"int32_t HashMap_KeySet::size()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashMap_KeySet::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashMap.KeySet", 24);
    return c;
}

java::lang::Class* HashMap_KeySet::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashMap_EntrySet.h>

#include <java/util/HashMap.h>

using java::util::HashMap_EntrySet;
using java::util::HashMap;

extern void unimplemented_(const char16_t* name);
java::util::HashMap_EntrySet::HashMap_EntrySet(HashMap *HashMap_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, HashMap_this(HashMap_this)
{
	clinit();
}


/* private: void HashMap_EntrySet::ctor() */
void HashMap_EntrySet::clear()
{ /* stub */
	unimplemented_(u"void HashMap_EntrySet::clear()");
}

bool HashMap_EntrySet::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashMap_EntrySet::contains(Object* arg0)");
	return 0;
}

Iterator* HashMap_EntrySet::iterator()
{ /* stub */
	unimplemented_(u"Iterator* HashMap_EntrySet::iterator()");
	return 0;
}

bool HashMap_EntrySet::remove(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashMap_EntrySet::remove(Object* arg0)");
	return 0;
}

int32_t HashMap_EntrySet::size()
{ /* stub */
	unimplemented_(u"int32_t HashMap_EntrySet::size()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashMap_EntrySet::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashMap.EntrySet", 26);
    return c;
}

java::lang::Class* HashMap_EntrySet::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashMap_Values.h>

#include <java/util/HashMap.h>

using java::util::HashMap_Values;
using java::util::HashMap;

extern void unimplemented_(const char16_t* name);
java::util::HashMap_Values::HashMap_Values(HashMap *HashMap_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, HashMap_this(HashMap_this)
{
	clinit();
}


/* private: void HashMap_Values::ctor() */
void HashMap_Values::clear()
{ /* stub */
	unimplemented_(u"void HashMap_Values::clear()");
}

bool HashMap_Values::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashMap_Values::contains(Object* arg0)");
	return 0;
}

Iterator* HashMap_Values::iterator()
{ /* stub */
	unimplemented_(u"Iterator* HashMap_Values::iterator()");
	return 0;
}

int32_t HashMap_Values::size()
{ /* stub */
	unimplemented_(u"int32_t HashMap_Values::size()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashMap_Values::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashMap.Values", 24);
    return c;
}

java::lang::Class* HashMap_Values::getClass0()
{
	return class_();
}


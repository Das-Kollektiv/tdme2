// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Hashtable_ValueCollection.h>

#include <java/util/Hashtable.h>

using java::util::Hashtable_ValueCollection;
using java::util::Hashtable;

extern void unimplemented_(const char16_t* name);
java::util::Hashtable_ValueCollection::Hashtable_ValueCollection(Hashtable *Hashtable_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, Hashtable_this(Hashtable_this)
{
	clinit();
}


/* private: void Hashtable_ValueCollection::ctor() */
void Hashtable_ValueCollection::clear()
{ /* stub */
	unimplemented_(u"void Hashtable_ValueCollection::clear()");
}

bool Hashtable_ValueCollection::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable_ValueCollection::contains(Object* arg0)");
	return 0;
}

Iterator* Hashtable_ValueCollection::iterator()
{ /* stub */
	unimplemented_(u"Iterator* Hashtable_ValueCollection::iterator()");
	return 0;
}

int32_t Hashtable_ValueCollection::size()
{ /* stub */
	unimplemented_(u"int32_t Hashtable_ValueCollection::size()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Hashtable_ValueCollection::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Hashtable.ValueCollection", 35);
    return c;
}

java::lang::Class* Hashtable_ValueCollection::getClass0()
{
	return class_();
}


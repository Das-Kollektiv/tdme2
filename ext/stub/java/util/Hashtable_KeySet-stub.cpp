// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Hashtable_KeySet.h>

#include <java/util/Hashtable.h>

using java::util::Hashtable_KeySet;
using java::util::Hashtable;

extern void unimplemented_(const char16_t* name);
java::util::Hashtable_KeySet::Hashtable_KeySet(Hashtable *Hashtable_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, Hashtable_this(Hashtable_this)
{
	clinit();
}


/* private: void Hashtable_KeySet::ctor() */
void Hashtable_KeySet::clear()
{ /* stub */
	unimplemented_(u"void Hashtable_KeySet::clear()");
}

bool Hashtable_KeySet::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable_KeySet::contains(Object* arg0)");
	return 0;
}

Iterator* Hashtable_KeySet::iterator()
{ /* stub */
	unimplemented_(u"Iterator* Hashtable_KeySet::iterator()");
	return 0;
}

bool Hashtable_KeySet::remove(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable_KeySet::remove(Object* arg0)");
	return 0;
}

int32_t Hashtable_KeySet::size()
{ /* stub */
	unimplemented_(u"int32_t Hashtable_KeySet::size()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Hashtable_KeySet::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Hashtable.KeySet", 26);
    return c;
}

java::lang::Class* Hashtable_KeySet::getClass0()
{
	return class_();
}


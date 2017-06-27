// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Hashtable_EntrySet.h>

#include <java/util/Hashtable.h>
#include <java/util/Map_Entry.h>

using java::util::Hashtable_EntrySet;
using java::util::Hashtable;
using java::util::Map_Entry;

extern void unimplemented_(const char16_t* name);
java::util::Hashtable_EntrySet::Hashtable_EntrySet(Hashtable *Hashtable_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, Hashtable_this(Hashtable_this)
{
	clinit();
}


/* private: void Hashtable_EntrySet::ctor() */
bool Hashtable_EntrySet::add(Map_Entry* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable_EntrySet::add(Map_Entry* arg0)");
	return 0;
}

bool Hashtable_EntrySet::add(Object* arg0)
{ 
	return add(dynamic_cast< Map_Entry* >(arg0));
}

void Hashtable_EntrySet::clear()
{ /* stub */
	unimplemented_(u"void Hashtable_EntrySet::clear()");
}

bool Hashtable_EntrySet::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable_EntrySet::contains(Object* arg0)");
	return 0;
}

Iterator* Hashtable_EntrySet::iterator()
{ /* stub */
	unimplemented_(u"Iterator* Hashtable_EntrySet::iterator()");
	return 0;
}

bool Hashtable_EntrySet::remove(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable_EntrySet::remove(Object* arg0)");
	return 0;
}

int32_t Hashtable_EntrySet::size()
{ /* stub */
	unimplemented_(u"int32_t Hashtable_EntrySet::size()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Hashtable_EntrySet::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Hashtable.EntrySet", 28);
    return c;
}

java::lang::Class* Hashtable_EntrySet::getClass0()
{
	return class_();
}


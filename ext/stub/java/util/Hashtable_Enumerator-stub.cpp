// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Hashtable_Enumerator.h>

#include <java/util/Hashtable.h>

using java::util::Hashtable_Enumerator;
using java::util::Hashtable;

extern void unimplemented_(const char16_t* name);
java::util::Hashtable_Enumerator::Hashtable_Enumerator(Hashtable *Hashtable_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, Hashtable_this(Hashtable_this)
{
	clinit();
}

java::util::Hashtable_Enumerator::Hashtable_Enumerator(Hashtable *Hashtable_this, int32_t arg0, bool arg1)
	: Hashtable_Enumerator(Hashtable_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}


void Hashtable_Enumerator::ctor(int32_t arg0, bool arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Hashtable_Enumerator::ctor(int32_t arg0, bool arg1)");
}

bool Hashtable_Enumerator::hasMoreElements()
{ /* stub */
	unimplemented_(u"bool Hashtable_Enumerator::hasMoreElements()");
	return 0;
}

bool Hashtable_Enumerator::hasNext()
{ /* stub */
	unimplemented_(u"bool Hashtable_Enumerator::hasNext()");
	return 0;
}

Object* Hashtable_Enumerator::next()
{ /* stub */
	unimplemented_(u"Object* Hashtable_Enumerator::next()");
	return 0;
}

Object* Hashtable_Enumerator::nextElement()
{ /* stub */
	unimplemented_(u"Object* Hashtable_Enumerator::nextElement()");
	return 0;
}

void Hashtable_Enumerator::remove()
{ /* stub */
	unimplemented_(u"void Hashtable_Enumerator::remove()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Hashtable_Enumerator::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Hashtable.Enumerator", 30);
    return c;
}

java::lang::Class* Hashtable_Enumerator::getClass0()
{
	return class_();
}


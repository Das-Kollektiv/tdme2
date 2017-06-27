// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Hashtable_EmptyEnumerator.h>

using java::util::Hashtable_EmptyEnumerator;
extern void unimplemented_(const char16_t* name);
java::util::Hashtable_EmptyEnumerator::Hashtable_EmptyEnumerator(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::Hashtable_EmptyEnumerator::Hashtable_EmptyEnumerator()
	: Hashtable_EmptyEnumerator(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void Hashtable_EmptyEnumerator::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Hashtable_EmptyEnumerator::ctor()");
}

bool Hashtable_EmptyEnumerator::hasMoreElements()
{ /* stub */
	unimplemented_(u"bool Hashtable_EmptyEnumerator::hasMoreElements()");
	return 0;
}

Object* Hashtable_EmptyEnumerator::nextElement()
{ /* stub */
	unimplemented_(u"Object* Hashtable_EmptyEnumerator::nextElement()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Hashtable_EmptyEnumerator::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Hashtable.EmptyEnumerator", 35);
    return c;
}

java::lang::Class* Hashtable_EmptyEnumerator::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/AbstractList_Itr.h>

#include <java/util/AbstractList.h>

using java::util::AbstractList_Itr;
using java::util::AbstractList;

extern void unimplemented_(const char16_t* name);
java::util::AbstractList_Itr::AbstractList_Itr(AbstractList *AbstractList_this, const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
	, AbstractList_this(AbstractList_this)
{
	clinit();
}


/* private: void AbstractList_Itr::ctor() */
void AbstractList_Itr::checkForComodification()
{ /* stub */
	unimplemented_(u"void AbstractList_Itr::checkForComodification()");
}

bool AbstractList_Itr::hasNext()
{ /* stub */
	unimplemented_(u"bool AbstractList_Itr::hasNext()");
	return 0;
}

Object* AbstractList_Itr::next()
{ /* stub */
	unimplemented_(u"Object* AbstractList_Itr::next()");
	return 0;
}

void AbstractList_Itr::remove()
{ /* stub */
	unimplemented_(u"void AbstractList_Itr::remove()");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractList_Itr::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.AbstractList.Itr", 26);
    return c;
}

java::lang::Class* AbstractList_Itr::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/AbstractList_ListItr.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/util/AbstractList.h>

using java::util::AbstractList_ListItr;
using java::lang::ClassCastException;
using java::lang::Object;
using java::util::AbstractList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

extern void unimplemented_(const char16_t* name);
java::util::AbstractList_ListItr::AbstractList_ListItr(AbstractList *AbstractList_this, const ::default_init_tag&)
	: super(AbstractList_this, *static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::AbstractList_ListItr::AbstractList_ListItr(AbstractList *AbstractList_this, int32_t arg0)
	: AbstractList_ListItr(AbstractList_this, *static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void AbstractList_ListItr::ctor(int32_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractList_ListItr::ctor(int32_t arg0)");
}

void AbstractList_ListItr::add(Object* arg0)
{ /* stub */
	unimplemented_(u"void AbstractList_ListItr::add(Object* arg0)");
}

bool AbstractList_ListItr::hasPrevious()
{ /* stub */
	unimplemented_(u"bool AbstractList_ListItr::hasPrevious()");
	return 0;
}

int32_t AbstractList_ListItr::nextIndex()
{ /* stub */
	unimplemented_(u"int32_t AbstractList_ListItr::nextIndex()");
	return 0;
}

Object* AbstractList_ListItr::previous()
{ /* stub */
	unimplemented_(u"Object* AbstractList_ListItr::previous()");
	return 0;
}

int32_t AbstractList_ListItr::previousIndex()
{ /* stub */
	unimplemented_(u"int32_t AbstractList_ListItr::previousIndex()");
	return 0;
}

void AbstractList_ListItr::set(Object* arg0)
{ /* stub */
	unimplemented_(u"void AbstractList_ListItr::set(Object* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractList_ListItr::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.AbstractList.ListItr", 30);
    return c;
}

bool AbstractList_ListItr::hasNext()
{
	return AbstractList_Itr::hasNext();
}

Object* AbstractList_ListItr::next()
{
	return java_cast< Object* >(AbstractList_Itr::next());
}

void AbstractList_ListItr::remove()
{
	AbstractList_Itr::remove();
}

java::lang::Class* AbstractList_ListItr::getClass0()
{
	return class_();
}


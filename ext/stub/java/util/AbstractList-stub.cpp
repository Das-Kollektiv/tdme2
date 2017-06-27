// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/AbstractList.h>

#include <java/lang/ClassCastException.h>
#include <ObjectArray.h>

using java::util::AbstractList;
using java::lang::ClassCastException;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

extern void unimplemented_(const char16_t* name);
java::util::AbstractList::AbstractList(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::AbstractList::AbstractList()
	: AbstractList(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void AbstractList::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractList::ctor()");
}

bool AbstractList::add(Object* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractList::add(Object* arg0)");
	return 0;
}

void AbstractList::add(int32_t arg0, Object* arg1)
{ /* stub */
	unimplemented_(u"void AbstractList::add(int32_t arg0, Object* arg1)");
}

bool AbstractList::addAll(int32_t arg0, Collection* arg1)
{ /* stub */
	unimplemented_(u"bool AbstractList::addAll(int32_t arg0, Collection* arg1)");
	return 0;
}

void AbstractList::clear()
{ /* stub */
	unimplemented_(u"void AbstractList::clear()");
}

bool AbstractList::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractList::equals(Object* arg0)");
	return 0;
}

int32_t AbstractList::hashCode()
{ /* stub */
	unimplemented_(u"int32_t AbstractList::hashCode()");
	return 0;
}

int32_t AbstractList::indexOf(Object* arg0)
{ /* stub */
	unimplemented_(u"int32_t AbstractList::indexOf(Object* arg0)");
	return 0;
}

Iterator* AbstractList::iterator()
{ /* stub */
	unimplemented_(u"Iterator* AbstractList::iterator()");
	return 0;
}

int32_t AbstractList::lastIndexOf(Object* arg0)
{ /* stub */
	unimplemented_(u"int32_t AbstractList::lastIndexOf(Object* arg0)");
	return 0;
}

ListIterator* AbstractList::listIterator()
{ /* stub */
	unimplemented_(u"ListIterator* AbstractList::listIterator()");
	return 0;
}

ListIterator* AbstractList::listIterator(int32_t arg0)
{ /* stub */
	unimplemented_(u"ListIterator* AbstractList::listIterator(int32_t arg0)");
	return 0;
}

Object* AbstractList::remove(int32_t arg0)
{ /* stub */
	unimplemented_(u"Object* AbstractList::remove(int32_t arg0)");
	return 0;
}

void AbstractList::removeRange(int32_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"void AbstractList::removeRange(int32_t arg0, int32_t arg1)");
}

Object* AbstractList::set(int32_t arg0, Object* arg1)
{ /* stub */
	unimplemented_(u"Object* AbstractList::set(int32_t arg0, Object* arg1)");
	return 0;
}

List* AbstractList::subList(int32_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"List* AbstractList::subList(int32_t arg0, int32_t arg1)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractList::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.AbstractList", 22);
    return c;
}

bool AbstractList::addAll(Collection* arg0)
{
	return AbstractCollection::addAll(arg0);
}

bool AbstractList::contains(Object* arg0)
{
	return AbstractCollection::contains(arg0);
}

bool AbstractList::containsAll(Collection* arg0)
{
	return AbstractCollection::containsAll(arg0);
}

bool AbstractList::isEmpty()
{
	return AbstractCollection::isEmpty();
}

bool AbstractList::remove(Object* arg0)
{
	return AbstractCollection::remove(arg0);
}

bool AbstractList::removeAll(Collection* arg0)
{
	return AbstractCollection::removeAll(arg0);
}

bool AbstractList::retainAll(Collection* arg0)
{
	return AbstractCollection::retainAll(arg0);
}

ObjectArray* AbstractList::toArray()
{
	return AbstractCollection::toArray();
}

ObjectArray* AbstractList::toArray(ObjectArray* arg0)
{
	return java_cast< ObjectArray* >(AbstractCollection::toArray(arg0));
}

java::lang::Class* AbstractList::getClass0()
{
	return class_();
}


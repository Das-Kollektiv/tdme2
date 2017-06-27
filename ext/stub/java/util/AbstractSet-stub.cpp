// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/AbstractSet.h>

#include <java/lang/ClassCastException.h>
#include <ObjectArray.h>

using java::util::AbstractSet;
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
java::util::AbstractSet::AbstractSet(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::AbstractSet::AbstractSet()
	: AbstractSet(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void AbstractSet::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractSet::ctor()");
}

bool AbstractSet::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractSet::equals(Object* arg0)");
	return 0;
}

int32_t AbstractSet::hashCode()
{ /* stub */
	unimplemented_(u"int32_t AbstractSet::hashCode()");
	return 0;
}

bool AbstractSet::removeAll(Collection* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractSet::removeAll(Collection* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractSet::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.AbstractSet", 21);
    return c;
}

bool AbstractSet::add(Object* e)
{
	return AbstractCollection::add(e);
}

bool AbstractSet::addAll(Collection* c)
{
	return AbstractCollection::addAll(c);
}

void AbstractSet::clear()
{
	AbstractCollection::clear();
}

bool AbstractSet::contains(Object* o)
{
	return AbstractCollection::contains(o);
}

bool AbstractSet::containsAll(Collection* c)
{
	return AbstractCollection::containsAll(c);
}

bool AbstractSet::isEmpty()
{
	return AbstractCollection::isEmpty();
}

bool AbstractSet::remove(Object* o)
{
	return AbstractCollection::remove(o);
}

bool AbstractSet::retainAll(Collection* c)
{
	return AbstractCollection::retainAll(c);
}

ObjectArray* AbstractSet::toArray()
{
	return AbstractCollection::toArray();
}

ObjectArray* AbstractSet::toArray(ObjectArray* a)
{
	return java_cast< ObjectArray* >(AbstractCollection::toArray(a));
}

java::lang::Class* AbstractSet::getClass0()
{
	return class_();
}


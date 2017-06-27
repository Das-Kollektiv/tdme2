// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/AbstractCollection.h>

using java::util::AbstractCollection;
extern void unimplemented_(const char16_t* name);
java::util::AbstractCollection::AbstractCollection(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::AbstractCollection::AbstractCollection()
	: AbstractCollection(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void AbstractCollection::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void AbstractCollection::ctor()");
}

bool AbstractCollection::add(Object* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractCollection::add(Object* arg0)");
	return 0;
}

bool AbstractCollection::addAll(Collection* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractCollection::addAll(Collection* arg0)");
	return 0;
}

void AbstractCollection::clear()
{ /* stub */
	unimplemented_(u"void AbstractCollection::clear()");
}

bool AbstractCollection::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractCollection::contains(Object* arg0)");
	return 0;
}

bool AbstractCollection::containsAll(Collection* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractCollection::containsAll(Collection* arg0)");
	return 0;
}

/* private: ObjectArray* AbstractCollection::finishToArray(ObjectArray* arg0, Iterator* arg1) */
bool AbstractCollection::isEmpty()
{ /* stub */
	unimplemented_(u"bool AbstractCollection::isEmpty()");
	return 0;
}

bool AbstractCollection::remove(Object* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractCollection::remove(Object* arg0)");
	return 0;
}

bool AbstractCollection::removeAll(Collection* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractCollection::removeAll(Collection* arg0)");
	return 0;
}

bool AbstractCollection::retainAll(Collection* arg0)
{ /* stub */
	unimplemented_(u"bool AbstractCollection::retainAll(Collection* arg0)");
	return 0;
}

ObjectArray* AbstractCollection::toArray()
{ /* stub */
	unimplemented_(u"ObjectArray* AbstractCollection::toArray()");
	return 0;
}

ObjectArray* AbstractCollection::toArray(ObjectArray* arg0)
{ /* stub */
	unimplemented_(u"ObjectArray* AbstractCollection::toArray(ObjectArray* arg0)");
	return 0;
}

String* AbstractCollection::toString()
{ /* stub */
	unimplemented_(u"String* AbstractCollection::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* AbstractCollection::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.AbstractCollection", 28);
    return c;
}

bool AbstractCollection::equals(Object* o)
{
	return Object::equals(o);
}

int32_t AbstractCollection::hashCode()
{
	return Object::hashCode();
}

java::lang::Class* AbstractCollection::getClass0()
{
	return class_();
}


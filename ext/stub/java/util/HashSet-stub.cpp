// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashSet.h>

#include <java/lang/ClassCastException.h>
#include <ObjectArray.h>

using java::util::HashSet;
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
java::util::HashSet::HashSet(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::HashSet::HashSet()
	: HashSet(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::util::HashSet::HashSet(Collection* arg0)
	: HashSet(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::HashSet::HashSet(int32_t arg0)
	: HashSet(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::HashSet::HashSet(int32_t arg0, float arg1)
	: HashSet(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::util::HashSet::HashSet(int32_t arg0, float arg1, bool arg2)
	: HashSet(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}

Object* java::util::HashSet::PRESENT;
constexpr int64_t java::util::HashSet::serialVersionUID;

void HashSet::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashSet::ctor()");
}

void HashSet::ctor(Collection* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashSet::ctor(Collection* arg0)");
}

void HashSet::ctor(int32_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashSet::ctor(int32_t arg0)");
}

void HashSet::ctor(int32_t arg0, float arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashSet::ctor(int32_t arg0, float arg1)");
}

void HashSet::ctor(int32_t arg0, float arg1, bool arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashSet::ctor(int32_t arg0, float arg1, bool arg2)");
}

bool HashSet::add(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashSet::add(Object* arg0)");
	return 0;
}

void HashSet::clear()
{ /* stub */
	unimplemented_(u"void HashSet::clear()");
}

Object* HashSet::clone()
{ /* stub */
	unimplemented_(u"Object* HashSet::clone()");
	return 0;
}

bool HashSet::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashSet::contains(Object* arg0)");
	return 0;
}

bool HashSet::isEmpty()
{ /* stub */
	unimplemented_(u"bool HashSet::isEmpty()");
	return 0;
}

Iterator* HashSet::iterator()
{ /* stub */
	unimplemented_(u"Iterator* HashSet::iterator()");
	return 0;
}

/* private: void HashSet::readObject(ObjectInputStream* arg0) */
bool HashSet::remove(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashSet::remove(Object* arg0)");
	return 0;
}

int32_t HashSet::size()
{ /* stub */
	unimplemented_(u"int32_t HashSet::size()");
	return 0;
}

/* private: void HashSet::writeObject(ObjectOutputStream* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashSet::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashSet", 17);
    return c;
}

bool HashSet::addAll(Collection* arg0)
{
	return AbstractCollection::addAll(arg0);
}

bool HashSet::containsAll(Collection* arg0)
{
	return AbstractCollection::containsAll(arg0);
}

bool HashSet::equals(Object* arg0)
{
	return AbstractSet::equals(arg0);
}

int32_t HashSet::hashCode()
{
	return AbstractSet::hashCode();
}

bool HashSet::removeAll(Collection* arg0)
{
	return AbstractSet::removeAll(arg0);
}

bool HashSet::retainAll(Collection* arg0)
{
	return AbstractCollection::retainAll(arg0);
}

ObjectArray* HashSet::toArray()
{
	return AbstractCollection::toArray();
}

ObjectArray* HashSet::toArray(ObjectArray* arg0)
{
	return java_cast< ObjectArray* >(AbstractCollection::toArray(arg0));
}

java::lang::Class* HashSet::getClass0()
{
	return class_();
}


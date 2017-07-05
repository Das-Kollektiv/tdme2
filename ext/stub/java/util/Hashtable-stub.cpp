// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Hashtable.h>

using java::util::Hashtable;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace util {
typedef ::SubArray< ::java::util::Map_Entry, ::java::lang::ObjectArray > Map_EntryArray;
typedef ::SubArray< ::java::util::Hashtable_Entry, ::java::lang::ObjectArray, Map_EntryArray > Hashtable_EntryArray;
}  // namespace util
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::util::Hashtable::Hashtable(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::Hashtable::Hashtable()
	: Hashtable(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::util::Hashtable::Hashtable(int32_t arg0)
	: Hashtable(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::Hashtable::Hashtable(Map* arg0)
	: Hashtable(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::Hashtable::Hashtable(int32_t arg0, float arg1)
	: Hashtable(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int32_t java::util::Hashtable::ENTRIES;
constexpr int32_t java::util::Hashtable::KEYS;
constexpr int32_t java::util::Hashtable::VALUES;
Enumeration* java::util::Hashtable::emptyEnumerator;
Iterator* java::util::Hashtable::emptyIterator;
constexpr int64_t java::util::Hashtable::serialVersionUID;

void Hashtable::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Hashtable::ctor()");
}

void Hashtable::ctor(int32_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Hashtable::ctor(int32_t arg0)");
}

void Hashtable::ctor(Map* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Hashtable::ctor(Map* arg0)");
}

void Hashtable::ctor(int32_t arg0, float arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Hashtable::ctor(int32_t arg0, float arg1)");
}

void Hashtable::clear()
{ /* stub */
	unimplemented_(u"void Hashtable::clear()");
}

Object* Hashtable::clone()
{ /* stub */
	unimplemented_(u"Object* Hashtable::clone()");
	return 0;
}

bool Hashtable::contains(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable::contains(Object* arg0)");
	return 0;
}

bool Hashtable::containsKey(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable::containsKey(Object* arg0)");
	return 0;
}

bool Hashtable::containsValue(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable::containsValue(Object* arg0)");
	return 0;
}

Enumeration* Hashtable::elements()
{ /* stub */
	unimplemented_(u"Enumeration* Hashtable::elements()");
	return 0;
}

Set* Hashtable::entrySet()
{ /* stub */
	unimplemented_(u"Set* Hashtable::entrySet()");
	return 0;
}

bool Hashtable::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Hashtable::equals(Object* arg0)");
	return 0;
}

Object* Hashtable::get(Object* arg0)
{ /* stub */
	unimplemented_(u"Object* Hashtable::get(Object* arg0)");
	return 0;
}

/* private: Enumeration* Hashtable::getEnumeration(int32_t arg0) */
/* private: Iterator* Hashtable::getIterator(int32_t arg0) */
int32_t Hashtable::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Hashtable::hashCode()");
	return 0;
}

bool Hashtable::isEmpty()
{ /* stub */
	unimplemented_(u"bool Hashtable::isEmpty()");
	return 0;
}

Set* Hashtable::keySet()
{ /* stub */
	unimplemented_(u"Set* Hashtable::keySet()");
	return 0;
}

Enumeration* Hashtable::keys()
{ /* stub */
	unimplemented_(u"Enumeration* Hashtable::keys()");
	return 0;
}

Object* Hashtable::put(Object* arg0, Object* arg1)
{ /* stub */
	unimplemented_(u"Object* Hashtable::put(Object* arg0, Object* arg1)");
	return 0;
}

void Hashtable::putAll(Map* arg0)
{ /* stub */
	unimplemented_(u"void Hashtable::putAll(Map* arg0)");
}

/* private: void Hashtable::readObject(ObjectInputStream* arg0) */
/* private: void Hashtable::reconstitutionPut(Hashtable_EntryArray* arg0, Object* arg1, Object* arg2) */
void Hashtable::rehash()
{ /* stub */
	unimplemented_(u"void Hashtable::rehash()");
}

Object* Hashtable::remove(Object* arg0)
{ /* stub */
	unimplemented_(u"Object* Hashtable::remove(Object* arg0)");
	return 0;
}

int32_t Hashtable::size()
{ /* stub */
	unimplemented_(u"int32_t Hashtable::size()");
	return 0;
}

String* Hashtable::toString()
{ /* stub */
	unimplemented_(u"String* Hashtable::toString()");
	return 0;
}

Collection* Hashtable::values()
{ /* stub */
	unimplemented_(u"Collection* Hashtable::values()");
	return 0;
}

/* private: void Hashtable::writeObject(ObjectOutputStream* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Hashtable::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Hashtable", 19);
    return c;
}

java::lang::Class* Hashtable::getClass0()
{
	return class_();
}


// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/HashMap.h>

using java::util::HashMap;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace util {
typedef ::SubArray< ::java::util::Map_Entry, ::java::lang::ObjectArray > Map_EntryArray;
typedef ::SubArray< ::java::util::HashMap_Entry, ::java::lang::ObjectArray, Map_EntryArray > HashMap_EntryArray;
}  // namespace util
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::util::HashMap::HashMap(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::HashMap::HashMap()
	: HashMap(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::util::HashMap::HashMap(int32_t arg0)
	: HashMap(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::HashMap::HashMap(Map* arg0)
	: HashMap(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::HashMap::HashMap(int32_t arg0, float arg1)
	: HashMap(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int32_t java::util::HashMap::DEFAULT_INITIAL_CAPACITY;
constexpr float java::util::HashMap::DEFAULT_LOAD_FACTOR;
constexpr int32_t java::util::HashMap::MAXIMUM_CAPACITY;
constexpr int64_t java::util::HashMap::serialVersionUID;

void HashMap::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashMap::ctor()");
}

void HashMap::ctor(int32_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashMap::ctor(int32_t arg0)");
}

void HashMap::ctor(Map* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashMap::ctor(Map* arg0)");
}

void HashMap::ctor(int32_t arg0, float arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void HashMap::ctor(int32_t arg0, float arg1)");
}

void HashMap::addEntry(int32_t arg0, Object* arg1, Object* arg2, int32_t arg3)
{ /* stub */
	unimplemented_(u"void HashMap::addEntry(int32_t arg0, Object* arg1, Object* arg2, int32_t arg3)");
}

int32_t HashMap::capacity()
{ /* stub */
	unimplemented_(u"int32_t HashMap::capacity()");
	return 0;
}

void HashMap::clear()
{ /* stub */
	unimplemented_(u"void HashMap::clear()");
}

Object* HashMap::clone()
{ /* stub */
	unimplemented_(u"Object* HashMap::clone()");
	return 0;
}

bool HashMap::containsKey(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashMap::containsKey(Object* arg0)");
	return 0;
}

/* private: bool HashMap::containsNullValue() */
bool HashMap::containsValue(Object* arg0)
{ /* stub */
	unimplemented_(u"bool HashMap::containsValue(Object* arg0)");
	return 0;
}

void HashMap::createEntry(int32_t arg0, Object* arg1, Object* arg2, int32_t arg3)
{ /* stub */
	unimplemented_(u"void HashMap::createEntry(int32_t arg0, Object* arg1, Object* arg2, int32_t arg3)");
}

Set* HashMap::entrySet()
{ /* stub */
	unimplemented_(u"Set* HashMap::entrySet()");
	return 0;
}

/* private: Set* HashMap::entrySet0() */
Object* HashMap::get(Object* arg0)
{ /* stub */
	unimplemented_(u"Object* HashMap::get(Object* arg0)");
	return 0;
}

HashMap_Entry* HashMap::getEntry(Object* arg0)
{ /* stub */
	unimplemented_(u"HashMap_Entry* HashMap::getEntry(Object* arg0)");
	return 0;
}

/* private: Object* HashMap::getForNullKey() */
int32_t HashMap::hash(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t HashMap::hash(int32_t arg0)");
	return 0;
}

int32_t HashMap::indexFor(int32_t arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t HashMap::indexFor(int32_t arg0, int32_t arg1)");
	return 0;
}

void HashMap::init_()
{ /* stub */
	unimplemented_(u"void HashMap::init_()");
}

bool HashMap::isEmpty()
{ /* stub */
	unimplemented_(u"bool HashMap::isEmpty()");
	return 0;
}

Set* HashMap::keySet()
{ /* stub */
	unimplemented_(u"Set* HashMap::keySet()");
	return 0;
}

float HashMap::loadFactor()
{ /* stub */
	unimplemented_(u"float HashMap::loadFactor()");
	return 0;
}

Iterator* HashMap::newEntryIterator()
{ /* stub */
	unimplemented_(u"Iterator* HashMap::newEntryIterator()");
	return 0;
}

Iterator* HashMap::newKeyIterator()
{ /* stub */
	unimplemented_(u"Iterator* HashMap::newKeyIterator()");
	return 0;
}

Iterator* HashMap::newValueIterator()
{ /* stub */
	unimplemented_(u"Iterator* HashMap::newValueIterator()");
	return 0;
}

Object* HashMap::put(Object* arg0, Object* arg1)
{ /* stub */
	unimplemented_(u"Object* HashMap::put(Object* arg0, Object* arg1)");
	return 0;
}

void HashMap::putAll(Map* arg0)
{ /* stub */
	unimplemented_(u"void HashMap::putAll(Map* arg0)");
}

/* private: void HashMap::putAllForCreate(Map* arg0) */
/* private: void HashMap::putForCreate(Object* arg0, Object* arg1) */
/* private: Object* HashMap::putForNullKey(Object* arg0) */
/* private: void HashMap::readObject(ObjectInputStream* arg0) */
Object* HashMap::remove(Object* arg0)
{ /* stub */
	unimplemented_(u"Object* HashMap::remove(Object* arg0)");
	return 0;
}

HashMap_Entry* HashMap::removeEntryForKey(Object* arg0)
{ /* stub */
	unimplemented_(u"HashMap_Entry* HashMap::removeEntryForKey(Object* arg0)");
	return 0;
}

HashMap_Entry* HashMap::removeMapping(Object* arg0)
{ /* stub */
	unimplemented_(u"HashMap_Entry* HashMap::removeMapping(Object* arg0)");
	return 0;
}

void HashMap::resize(int32_t arg0)
{ /* stub */
	unimplemented_(u"void HashMap::resize(int32_t arg0)");
}

int32_t HashMap::size()
{ /* stub */
	unimplemented_(u"int32_t HashMap::size()");
	return 0;
}

void HashMap::transfer(HashMap_EntryArray* arg0)
{ /* stub */
	unimplemented_(u"void HashMap::transfer(HashMap_EntryArray* arg0)");
}

Collection* HashMap::values()
{ /* stub */
	unimplemented_(u"Collection* HashMap::values()");
	return 0;
}

/* private: void HashMap::writeObject(ObjectOutputStream* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* HashMap::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.HashMap", 17);
    return c;
}

bool HashMap::equals(Object* arg0)
{
	return AbstractMap::equals(arg0);
}

int32_t HashMap::hashCode()
{
	return AbstractMap::hashCode();
}

java::lang::Class* HashMap::getClass0()
{
	return class_();
}


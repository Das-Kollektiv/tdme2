// Generated from /tdme/src/tdme/utils/_HashMap.java
#include <tdme/utils/_HashMap_ValuesIterator.h>

#include <java/lang/Object.h>
#include <java/util/Iterator.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap_Pair.h>
#include <tdme/utils/_HashMap.h>

using tdme::utils::_HashMap_ValuesIterator;
using java::lang::Object;
using java::util::Iterator;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap_Pair;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

_HashMap_ValuesIterator::_HashMap_ValuesIterator(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_HashMap_ValuesIterator::_HashMap_ValuesIterator(_HashMap* hashmap) 
	: _HashMap_ValuesIterator(*static_cast< ::default_init_tag* >(0))
{
	ctor(hashmap);
}

void _HashMap_ValuesIterator::ctor(_HashMap* hashmap)
{
	super::ctor();
	this->hashMap = hashmap;
	reset();
}

Iterator* _HashMap_ValuesIterator::reset()
{
	this->bucketIdx = 0;
	this->keyValuePairIdx = 0;
	this->elementIdx = 0;
	return this;
}

Iterator* _HashMap_ValuesIterator::iterator()
{
	return reset();
}

bool _HashMap_ValuesIterator::hasNext()
{
	return elementIdx < hashMap->elements;
}

Object* _HashMap_ValuesIterator::next()
{
	while (bucketIdx < hashMap->buckets->size()) {
		auto bucket = java_cast< _ArrayList* >(hashMap->buckets->get(bucketIdx));
		if (keyValuePairIdx == bucket->size()) {
			keyValuePairIdx = 0;
			bucketIdx++;
		} else {
			auto keyValuePair = java_cast< _HashMap_Pair* >(bucket->get(keyValuePairIdx++));
			elementIdx++;
			return java_cast< Object* >(keyValuePair->value);
		}
	}
	return nullptr;
}

void _HashMap_ValuesIterator::remove()
{
	// TODO: throw a exception maybe
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _HashMap_ValuesIterator::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils._HashMap.ValuesIterator", 34);
    return c;
}

java::lang::Class* _HashMap_ValuesIterator::getClass0()
{
	return class_();
}


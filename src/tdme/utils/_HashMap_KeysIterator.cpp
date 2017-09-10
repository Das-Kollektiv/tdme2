#include <tdme/utils/_HashMap_KeysIterator.h>

#include <java/lang/Object.h>
#include <java/util/Iterator.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap_Pair.h>
#include <tdme/utils/_HashMap.h>

using tdme::utils::_HashMap_KeysIterator;
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

_HashMap_KeysIterator::_HashMap_KeysIterator(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_HashMap_KeysIterator::_HashMap_KeysIterator(_HashMap* hashmap) 
	: _HashMap_KeysIterator(*static_cast< ::default_init_tag* >(0))
{
	ctor(hashmap);
}

void _HashMap_KeysIterator::ctor(_HashMap* hashmap)
{
	super::ctor();
	this->hashMap = hashmap;
	reset();
}

Iterator* _HashMap_KeysIterator::reset()
{
	this->bucketIdx = 0;
	this->keyValuePairIdx = 0;
	this->elementIdx = 0;
	return this;
}

Iterator* _HashMap_KeysIterator::iterator()
{
	return reset();
}

bool _HashMap_KeysIterator::hasNext()
{
	return elementIdx < hashMap->elements;
}

Object* _HashMap_KeysIterator::next()
{
	while (bucketIdx < hashMap->buckets->size()) {
		auto bucket = java_cast< _ArrayList* >(hashMap->buckets->get(bucketIdx));
		if (keyValuePairIdx == bucket->size()) {
			keyValuePairIdx = 0;
			bucketIdx++;
		} else {
			auto keyValuePair = java_cast< _HashMap_Pair* >(bucket->get(keyValuePairIdx++));
			elementIdx++;
			return java_cast< Object* >(keyValuePair->key);
		}
	}
	return nullptr;
}

void _HashMap_KeysIterator::remove()
{
	// TODO: throw a exception maybe
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _HashMap_KeysIterator::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils._HashMap.KeysIterator", 32);
    return c;
}

java::lang::Class* _HashMap_KeysIterator::getClass0()
{
	return class_();
}


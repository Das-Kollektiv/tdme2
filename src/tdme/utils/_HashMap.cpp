// Generated from /tdme/src/tdme/utils/_HashMap.java
#include <tdme/utils/_HashMap.h>

#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap_1.h>
#include <tdme/utils/_HashMap_KeysIterator.h>
#include <tdme/utils/_HashMap_Pair.h>
#include <tdme/utils/_HashMap_ValuesIterator.h>

using tdme::utils::_HashMap;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::utils::Pool;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap_1;
using tdme::utils::_HashMap_KeysIterator;
using tdme::utils::_HashMap_Pair;
using tdme::utils::_HashMap_ValuesIterator;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

_HashMap::_HashMap(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_HashMap::_HashMap() 
	: _HashMap(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void _HashMap::init()
{
	capacity = 256;
	elements = 0;
	buckets = new _ArrayList();
	valuesIterator = new _HashMap_ValuesIterator(this);
	keysIterator = new _HashMap_KeysIterator(this);
	pairPool = new _HashMap_1(this);
}

void _HashMap::ctor()
{
	super::ctor();
	init();
	for (auto i = 0; i < capacity; i++) {
		buckets->add(new _ArrayList());
	}
}

void _HashMap::clear()
{
	pairPool->reset();
	elements = 0;
	for (auto i = 0; i < capacity; i++) {
		java_cast< _ArrayList* >(buckets->get(i))->clear();
	}
}

void _HashMap::grow()
{
	auto oldBuckets = buckets;
	buckets = new _ArrayList();
	capacity *= 2;
	elements = 0;
	for (auto i = 0; i < capacity; i++) {
		buckets->add(new _ArrayList());
	}
	for (auto i = 0; i < oldBuckets->size(); i++) {
		auto bucket = java_cast< _ArrayList* >(oldBuckets->get(i));
		for (auto j = 0; j < bucket->size(); j++) {
			auto keyValuePair = java_cast< _HashMap_Pair* >(bucket->get(j));
			put(java_cast< Object* >(keyValuePair->key), java_cast< Object* >(keyValuePair->value));
		}
	}
}

Object* _HashMap::get(Object* key)
{
	auto bucket = java_cast< _ArrayList* >(buckets->get(Math::abs(key->hashCode()) % capacity));
	for (auto i = 0; i < bucket->size(); i++) {
		auto keyValuePair = java_cast< _HashMap_Pair* >(bucket->get(i));
		if (java_cast< Object* >(keyValuePair->key)->equals(key))
			return java_cast< Object* >(keyValuePair->value);

	}
	return nullptr;
}

Object* _HashMap::remove(Object* key)
{
	auto bucket = java_cast< _ArrayList* >(buckets->get(Math::abs(key->hashCode()) % capacity));
	for (auto i = 0; i < bucket->size(); i++) {
		auto keyValuePair = java_cast< _HashMap_Pair* >(bucket->get(i));
		if (java_cast< Object* >(keyValuePair->key)->equals(key)) {
			pairPool->release(keyValuePair);
			bucket->remove(i);
			elements--;
			return java_cast< Object* >(keyValuePair->value);
		}
	}
	return nullptr;
}

Object* _HashMap::getKey(Object* key)
{
	auto bucket = java_cast< _ArrayList* >(buckets->get(Math::abs(key->hashCode()) % capacity));
	for (auto i = 0; i < bucket->size(); i++) {
		auto keyValuePair = java_cast< _HashMap_Pair* >(bucket->get(i));
		if (java_cast< Object* >(keyValuePair->key)->equals(key))
			return java_cast< Object* >(keyValuePair->key);

	}
	return nullptr;
}

Object* _HashMap::put(Object* key, Object* value)
{
	if (elements + 1 >= buckets->size())
		grow();

	auto oldValue = java_cast< Object* >(remove(key));
	auto bucket = java_cast< _ArrayList* >(buckets->get(Math::abs(key->hashCode()) % capacity));
	auto keyValuePair = java_cast< _HashMap_Pair* >(pairPool->allocate());
	keyValuePair->key = key;
	keyValuePair->value = value;
	bucket->add(keyValuePair);
	elements++;
	return oldValue;
}

int32_t _HashMap::size()
{
	return elements;
}

_HashMap_ValuesIterator* _HashMap::getValuesIterator()
{
	valuesIterator->reset();
	return valuesIterator;
}

_HashMap_KeysIterator* _HashMap::getKeysIterator()
{
	keysIterator->reset();
	return keysIterator;
}

String* _HashMap::toString()
{
	auto string = new String();
	for (auto i = 0; i < buckets->size(); i++) {
		auto bucket = java_cast< _ArrayList* >(buckets->get(i));
		for (auto j = 0; j < bucket->size(); j++) {
			auto keyValuePair = java_cast< _HashMap_Pair* >(bucket->get(j));
			if (string->length() > 0)
				string = ::java::lang::StringBuilder(string).append(u", "_j)->toString();

			string = ::java::lang::StringBuilder(string).append(::java::lang::StringBuilder().append(static_cast< Object* >(java_cast< Object* >(keyValuePair->key)))->append(u"="_j)
				->append(static_cast< Object* >(java_cast< Object* >(keyValuePair->value)))->toString())->toString();
		}
	}
	string = ::java::lang::StringBuilder().append(u"HashMap["_j)->append(string)
		->append(u"]"_j)->toString();
	return string;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _HashMap::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils._HashMap", 19);
    return c;
}

java::lang::Class* _HashMap::getClass0()
{
	return class_();
}


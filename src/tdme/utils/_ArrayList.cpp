// Generated from /tdme/src/tdme/utils/_ArrayList.java
#include <tdme/utils/_ArrayList.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <java/lang/UnsupportedOperationException.h>
#include <ObjectArray.h>

using tdme::utils::_ArrayList;
using java::lang::ClassCastException;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using java::lang::UnsupportedOperationException;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

_ArrayList::_ArrayList(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_ArrayList::_ArrayList() 
	: _ArrayList(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

_ArrayList::_ArrayList(ObjectArray* values) 
	: _ArrayList(*static_cast< ::default_init_tag* >(0))
{
	ctor(values);
}

void _ArrayList::ctor()
{
	super::ctor();
	capacity_ = 32;
	size_ = 0;
	elements = java_cast< ObjectArray* >(new ObjectArray(capacity_));
	iteratorIdx = 0;
}

void _ArrayList::ctor(ObjectArray* values)
{
	super::ctor();
	capacity_ = 32;
	size_ = 0;
	elements = java_cast< ObjectArray* >(new ObjectArray(capacity_));
	iteratorIdx = 0;
	for (auto i = 0; i < values->length; i++) {
		add((*values)[i]);
	}
}

void _ArrayList::grow()
{
	auto elementsOld = elements;
	capacity_ *= 2;
	elements = java_cast< ObjectArray* >(new ObjectArray(capacity_));
	for (auto i = 0; i < size_; i++) {
		elements->set(i, (*elementsOld)[i]);
	}
}

bool _ArrayList::isEmpty()
{
	return size_ == 0;
}

int32_t _ArrayList::size()
{
	return size_;
}

int32_t _ArrayList::capacity()
{
	return capacity_;
}

void _ArrayList::clear()
{
	size_ = 0;
}

void _ArrayList::add(Object* value)
{
	if (size_ == capacity_) {
		grow();
	}
	elements->set(size_++, value);
}

void _ArrayList::addAll(_ArrayList* values)
{
	for (auto i = 0; i < values->size_; i++) {
		add((*values->elements)[i]);
	}
}

Object* _ArrayList::set(int32_t idx, Object* value)
{
	auto oldValue = (*elements)[idx];
	elements->set(idx, value);
	return oldValue;
}

Object* _ArrayList::remove(int32_t idx)
{
	auto value = (*elements)[idx];
	System::arraycopy(elements, idx + 1, elements, idx, size_ - idx - 1);
	elements->set(size_ - 1, nullptr);
	size_--;
	return value;
}

bool _ArrayList::remove(Object* value)
{
	if (value == nullptr) {
		for (auto i = 0; i < size_; i++) {
			if ((*elements)[i] == nullptr) {
				remove(i);
				return true;
			}
		}
	} else {
		for (auto i = 0; i < size_; i++) {
			if ((*elements)[i] != nullptr && (*elements)[i]->equals(value)) {
				remove(i);
				return true;
			}
		}
	}
	return false;
}

Object* _ArrayList::get(int32_t idx)
{
	return (*elements)[idx];
}

bool _ArrayList::contains(Object* value)
{
	if (value == nullptr) {
		for (auto i = 0; i < size_; i++) {
			if ((*elements)[i] == nullptr)
				return true;

		}
	} else {
		for (auto i = 0; i < size_; i++) {
			if ((*elements)[i] != nullptr && elements->equals(value) == true)
				return true;

		}
	}
	return false;
}

ObjectArray* _ArrayList::toArray(ObjectArray* array)
{
	for (auto i = 0; i < size_; i++) {
		array->set(i, (*elements)[i]);
	}
	return array;
}

Iterator* _ArrayList::iterator()
{
	iteratorIdx = 0;
	return this;
}

bool _ArrayList::hasNext()
{
	return iteratorIdx < size_;
}

Object* _ArrayList::next()
{
	return (*elements)[iteratorIdx++];
}

void _ArrayList::remove()
{
	throw new UnsupportedOperationException();
}

_ArrayList* _ArrayList::clone()
{
	auto clone = new _ArrayList();
	clone->capacity_ = capacity_;
	clone->size_ = size_;
	clone->elements = java_cast< ObjectArray* >(new ObjectArray(clone->capacity_));
	clone->iteratorIdx = 0;
	for (auto i = 0; i < size_; i++) {
		clone->elements->set(i, (*elements)[i]);
	}
	return clone;
}

String* _ArrayList::toString()
{
	auto result = u"["_j;
	for (auto i = 0; i < size_; i++) {
		result = ::java::lang::StringBuilder(result).append(static_cast< Object* >((*elements)[i]))->toString();
		if (i < size_ - 1)
			result = ::java::lang::StringBuilder(result).append(u", "_j)->toString();

	}
	result = ::java::lang::StringBuilder(result).append(u"]"_j)->toString();
	return result;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _ArrayList::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils._ArrayList", 21);
    return c;
}

java::lang::Class* _ArrayList::getClass0()
{
	return class_();
}


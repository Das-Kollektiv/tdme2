// Generated from /tdme/src/tdme/utils/ArrayListIteratorMultiple.java
#include <tdme/utils/ArrayListIteratorMultiple.h>

#include <java/lang/Object.h>
#include <tdme/utils/_ArrayList.h>

using tdme::utils::ArrayListIteratorMultiple;
using java::lang::Object;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

ArrayListIteratorMultiple::ArrayListIteratorMultiple(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ArrayListIteratorMultiple::ArrayListIteratorMultiple() 
	: ArrayListIteratorMultiple(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

ArrayListIteratorMultiple::ArrayListIteratorMultiple(_ArrayList* arrayLists) 
	: ArrayListIteratorMultiple(*static_cast< ::default_init_tag* >(0))
{
	ctor(arrayLists);
}

void ArrayListIteratorMultiple::ctor()
{
	super::ctor();
	this->arrayLists = new _ArrayList();
	reset();
}

void ArrayListIteratorMultiple::ctor(_ArrayList* arrayLists)
{
	super::ctor();
	this->arrayLists = arrayLists;
	reset();
}

void ArrayListIteratorMultiple::clear()
{
	arrayLists->clear();
}

void ArrayListIteratorMultiple::addArrayList(_ArrayList* _arrayLists)
{
	if (_arrayLists == nullptr)
		return;

	if (_arrayLists->size() == 0)
		return;

	for (auto i = 0; i < arrayLists->size(); i++) {
		if (java_cast< _ArrayList* >(arrayLists->get(i)) == _arrayLists)
			return;

	}
	arrayLists->add(_arrayLists);
}

ArrayListIteratorMultiple* ArrayListIteratorMultiple::reset()
{
	this->vectorIdx = 0;
	this->elementIdx = 0;
	this->length = 0;
	for (auto i = 0; i < arrayLists->size(); i++) {
		this->length += java_cast< _ArrayList* >(arrayLists->get(i))->size();
	}
	return this;
}

bool ArrayListIteratorMultiple::hasNext()
{
	auto hasNext = (vectorIdx < arrayLists->size() - 1) || (vectorIdx == arrayLists->size() - 1 && elementIdx < java_cast< _ArrayList* >(arrayLists->get(vectorIdx))->size());
	return hasNext;
}

Object* ArrayListIteratorMultiple::next()
{
	auto element = java_cast< Object* >(java_cast< _ArrayList* >(arrayLists->get(vectorIdx))->get(elementIdx++));
	if (elementIdx == java_cast< _ArrayList* >(arrayLists->get(vectorIdx))->size()) {
		elementIdx = 0;
		vectorIdx++;
	}
	return element;
}

void ArrayListIteratorMultiple::remove()
{
	// TODO: Throw a exception maybe
}

Iterator* ArrayListIteratorMultiple::iterator()
{
	reset();
	return this;
}

ArrayListIteratorMultiple* ArrayListIteratorMultiple::clone()
{
	return new ArrayListIteratorMultiple(java_cast< _ArrayList* >(arrayLists->clone()));
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ArrayListIteratorMultiple::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils.ArrayListIteratorMultiple", 36);
    return c;
}

java::lang::Class* ArrayListIteratorMultiple::getClass0()
{
	return class_();
}


// Generated from /tdme/src/tdme/utils/Key.java
#include <tdme/utils/Key.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/Float.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

using tdme::utils::Key;
using java::lang::ClassCastException;
using java::lang::Float;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

Key::Key(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Key::Key() 
	: Key(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int32_t Key::LENGTH_MAX;

void Key::ctor()
{
	super::ctor();
	length = 0;
	hash = 0;
	data = new char16_tArray(LENGTH_MAX);
}

void Key::reset()
{
	length = 0;
	hash = 0;
}

void Key::append(String* string)
{
	if (length + string->length() > LENGTH_MAX) {
		_Console::println(static_cast< Object* >(u"Key.append: key too long"_j));
	}
	string->getChars(0, string->length(), data, length);
	length += string->length();
	hash = 0;
}

void Key::append(float value)
{
	if (length + 4 > LENGTH_MAX) {
		_Console::println(static_cast< Object* >(u"Key.append: key too long"_j));
	}
	auto intValue = Float::floatToIntBits(value);
	(*data)[length++] = static_cast< char16_t >(((intValue) & 255));
	(*data)[length++] = static_cast< char16_t >(((intValue >> 8) & 255));
	(*data)[length++] = static_cast< char16_t >(((intValue >> 16) & 255));
	(*data)[length++] = static_cast< char16_t >(((intValue >> 24) & 255));
	hash = 0;
}

void Key::append(int32_t value)
{
	if (length + 4 > LENGTH_MAX) {
		_Console::println(static_cast< Object* >(u"Key.append: key too long"_j));
	}
	(*data)[length++] = static_cast< char16_t >(((value) & 255));
	(*data)[length++] = static_cast< char16_t >(((value >> 8) & 255));
	(*data)[length++] = static_cast< char16_t >(((value >> 16) & 255));
	(*data)[length++] = static_cast< char16_t >(((value >> 24) & 255));
	hash = 0;
}

int32_t Key::hashCode()
{
	auto h = hash;
	if (h == 0 && length > 0) {
		for (auto i = 0; i < length; i++) {
			h = 31 * h + (*data)[i];
		}
		hash = h;
	}
	return h;
}

bool Key::equals(Object* object)
{
	if (static_cast< Object* >(this) == object)
		return true;

	if (dynamic_cast< Key* >(object) != nullptr == false)
		return false;

	auto key2 = java_cast< Key* >(object);
	if (length != key2->length)
		return false;

	for (auto i = 0; i < length; i++) 
				if ((*data)[i] != (*key2->data)[i]) {
			return false;
		}

	return true;
}

void Key::cloneInto(Key* key2)
{
	key2->length = length;
	key2->hash = hash;
	System::arraycopy(data, 0, key2->data, 0, length);
}

char16_tArray* Key::getData()
{
	return data;
}

int32_t Key::getLength()
{
	return length;
}

String* Key::toString()
{
	auto tmp = u"\""_j;
	for (auto i = 0; i < length; i++) {
		tmp = ::java::lang::StringBuilder(tmp).append((*data)[i])->toString();
	}
	tmp = ::java::lang::StringBuilder(tmp).append(u"\""_j)->toString();
	return tmp;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Key::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils.Key", 14);
    return c;
}

java::lang::Class* Key::getClass0()
{
	return class_();
}


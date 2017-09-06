// Generated from /tdme/src/tdme/utils/MutableString.java
#include <tdme/utils/MutableString.h>

#include <string>

#include <java/lang/Math.h>
#include <java/lang/String.h>
#include <java/lang/System.h>
#include <java/util/Arrays.h>
#include <Array.h>

using std::wstring;

using tdme::utils::MutableString;
using java::lang::Math;
using java::lang::String;
using java::lang::System;
using java::util::Arrays;

MutableString::MutableString(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

MutableString::MutableString() 
	: MutableString(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

MutableString::MutableString(String* s) 
	: MutableString(*static_cast< ::default_init_tag* >(0))
{
	ctor(s);
}

MutableString::MutableString(const wstring& s)
	: MutableString(*static_cast< ::default_init_tag* >(0))
{
	ctor(s);
}

void MutableString::ctor()
{
	super::ctor();
	this->data = new char16_tArray(64);
	this->length_ = 0;
	this->hash = 0;
}

void MutableString::ctor(String* s)
{
	super::ctor();
	this->data = new char16_tArray(64);
	this->length_ = 0;
	this->hash = 0;
	append(s);
}

void MutableString::ctor(const wstring& s)
{
	super::ctor();
	this->data = new char16_tArray(64);
	this->length_ = 0;
	this->hash = 0;
	append(s);
}

void MutableString::grow()
{
	auto dataNew = new char16_tArray(data->length + 64);
	System::arraycopy(data, 0, dataNew, 0, length_);
	data = dataNew;
}

int32_t MutableString::length()
{
	return length_;
}

char16_t MutableString::charAt(int32_t idx)
{
	return (*data)[idx];
}

MutableString* MutableString::reset()
{
	Arrays::fill(data, char16_t(0x0000));
	length_ = 0;
	hash = 0;
	return this;
}

MutableString* MutableString::set(char16_t c)
{
	reset();
	append(c);
	return this;
}

MutableString* MutableString::append(char16_t c)
{
	if (length_ + 1 >= data->length) {
		grow();
	}
	(*data)[length_++] = c;
	hash = 0;
	return this;
}

MutableString* MutableString::insert(int32_t idx, char16_t c)
{
	if (length_ + 1 >= data->length) {
		grow();
	}
	System::arraycopy(data, idx, data, idx + 1, length_ - idx);
	(*data)[idx] = c;
	length_++;
	hash = 0;
	return this;
}

MutableString* MutableString::set(String* s)
{
	reset();
	append(s);
	return this;
}

MutableString* MutableString::set(const wstring& s)
{
	reset();
	append(s);
	return this;
}

MutableString* MutableString::append(String* s)
{
	for (auto i = 0; i < s->length(); i++) {
		append(s->charAt(i));
	}
	return this;
}

MutableString* MutableString::append(const wstring& s)
{
	for (auto i = 0; i < s.length(); i++) {
		append((char16_t)s[i]);
	}
	return this;
}


MutableString* MutableString::insert(int32_t idx, String* s)
{
	for (auto i = 0; i < s->length(); i++) {
		insert(idx + i, s->charAt(i));
	}
	return this;
}

MutableString* MutableString::set(MutableString* s)
{
	reset();
	append(s);
	return this;
}

MutableString* MutableString::append(MutableString* s)
{
	for (auto i = 0; i < s->length(); i++) {
		append(s->charAt(i));
	}
	return this;
}

MutableString* MutableString::insert(int32_t idx, MutableString* s)
{
	for (auto i = 0; i < s->length(); i++) {
		insert(idx + i, s->charAt(i));
	}
	return this;
}

MutableString* MutableString::set(int32_t i)
{
	reset();
	append(i);
	return this;
}

MutableString* MutableString::append(int32_t i)
{
	insert(length_, i);
	return this;
}

MutableString* MutableString::insert(int32_t idx, int32_t i)
{
	auto negative = false;
	if (i < 0) {
		negative = true;
		i = -i;
	}
	while (true == true) {
		auto remainder = i % 10;
		i = i / 10;
		insert(idx, static_cast< char16_t >((u'0' + remainder)));
		if (i == 0) {
			break;
		}
	}
	if (negative == true) {
		insert(idx, u'-');
	}
	return this;
}

MutableString* MutableString::set(float f, int32_t decimals)
{
	reset();
	append(f, decimals);
	return this;
}

MutableString* MutableString::append(float f, int32_t decimals)
{
	insert(length_, f, decimals);
	return this;
}

MutableString* MutableString::insert(int32_t idx, float f, int32_t decimals)
{
	auto integer = static_cast< int32_t >(f);
	auto integerDecimals = static_cast< int32_t >(((f - integer) * Math::pow(10.0f, decimals)));
	if (integerDecimals < 0.0f)
		integerDecimals = -integerDecimals;

	for (auto i = 0; i < decimals; i++) {
		auto integerDecimal = static_cast< int32_t >(((f - integer) * Math::pow(10.0f, i + 1))) - (10 * static_cast< int32_t >(((f - integer) * Math::pow(10.0f, i))));
		insert(idx + i, integerDecimal);
	}
	insert(idx, u'.');
	insert(idx, integer);
	return this;
}

MutableString* MutableString::delete_(int32_t idx, int32_t count)
{
	if (count + idx > length_)
		return this;

	System::arraycopy(data, idx + count, data, idx, length_ - count - idx);
	length_ -= count;
	hash = 0;
	return this;
}

int32_t MutableString::indexOf(MutableString* s, int32_t idx)
{
	for (auto i = idx; i < length_; i++) {
		auto found = true;
		for (auto j = 0; j < s->length_; j++) {
			if (i + j >= length_) {
				found = false;
				break;
			}
			;
			if ((*data)[i + j] != (*s->data)[j]) {
				found = false;
				break;
			}
		}
		if (found == true) {
			return i;
		}
	}
	return -1;
}

int32_t MutableString::indexOf(MutableString* s)
{
	return indexOf(s, 0);
}

int32_t MutableString::hashCode()
{
	auto h = hash;
	if (h == 0 && length_ > 0) {
		for (auto i = 0; i < length_; i++) {
			h = 31 * h + (*data)[i];
		}
		hash = h;
	}
	return h;
}

bool MutableString::equals(const wstring& s2)
{
	if (length_ != s2.length())
		return false;

	for (auto i = 0; i < length_; i++) {
		if ((*data)[i] != s2[i])
			return false;

	}
	return true;
}

bool MutableString::equals(String* s2)
{
	if (length_ != s2->length())
		return false;

	for (auto i = 0; i < length_; i++) {
		if ((*data)[i] != s2->charAt(i))
			return false;

	}
	return true;
}

bool MutableString::equals(MutableString* s2)
{
	if (this == s2)
		return true;

	if (length_ != s2->length_)
		return false;

	for (auto i = 0; i < length_; i++) {
		if ((*data)[i] != (*s2->data)[i])
			return false;

	}
	return true;
}

String* MutableString::toString()
{
	return new String(data, 0, length_);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* MutableString::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.utils.MutableString", 24);
    return c;
}

bool MutableString::equals(Object* obj)
{
	return super::equals(obj);
}

java::lang::Class* MutableString::getClass0()
{
	return class_();
}


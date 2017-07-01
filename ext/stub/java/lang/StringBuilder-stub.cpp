// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/StringBuilder.h>

#include <java/lang/String.h>

using std::to_wstring;

using java::lang::String;
using java::lang::StringBuilder;

extern void unimplemented_(const char16_t* name);

java::lang::StringBuilder::StringBuilder(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::StringBuilder::StringBuilder()
	: StringBuilder(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::StringBuilder::StringBuilder(int32_t arg0)
	: StringBuilder(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::StringBuilder::StringBuilder(String* arg0)
	: StringBuilder(*static_cast< ::default_init_tag* >(0))
{
	cppwstring = arg0->getCPPWString();
}

java::lang::StringBuilder::StringBuilder(CharSequence* arg0)
	: StringBuilder(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int64_t java::lang::StringBuilder::serialVersionUID;

void StringBuilder::ctor()
{ /* stub */
	/* super::ctor(); */
	// unimplemented_(u"void StringBuilder::ctor()");
}

void StringBuilder::ctor(int32_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void StringBuilder::ctor(int32_t arg0)");
}

void StringBuilder::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void StringBuilder::ctor(String* arg0)");
}

void StringBuilder::ctor(CharSequence* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void StringBuilder::ctor(CharSequence* arg0)");
}

StringBuilder* StringBuilder::append(Object* arg0)
{ /* stub */
	cppwstring+= arg0->toString()->getCPPWString();
	return this;
}

StringBuilder* StringBuilder::append(String* arg0)
{ /* stub */
	cppwstring+= arg0->getCPPWString();
	return this;
}

/* private: StringBuilder* StringBuilder::append(StringBuilder* arg0) */
StringBuilder* StringBuilder::append(StringBuffer* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::append(StringBuffer* arg0)");
	return 0;
}

StringBuilder* StringBuilder::append(CharSequence* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::append(CharSequence* arg0)");
	return 0;
}

StringBuilder* StringBuilder::append(char16_tArray* arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::append(char16_tArray* arg0)");
	return 0;
}

StringBuilder* StringBuilder::append(bool arg0)
{ /* stub */
	cppwstring+= to_wstring(arg0);
	return this;
}

StringBuilder* StringBuilder::append(char16_t arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::append(char16_t arg0)");
	return 0;
}

StringBuilder* StringBuilder::append(int32_t arg0)
{ /* stub */
	cppwstring+= to_wstring(arg0);
	return this;
}

StringBuilder* StringBuilder::append(int64_t arg0)
{ /* stub */
	cppwstring+= to_wstring(arg0);
	return this;
}

StringBuilder* StringBuilder::append(float arg0)
{ /* stub */
	cppwstring+= to_wstring(arg0);
	return this;
}

StringBuilder* StringBuilder::append(double arg0)
{ /* stub */
	cppwstring+= to_wstring(arg0);
	return this;
}

StringBuilder* StringBuilder::append(CharSequence* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::append(CharSequence* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

StringBuilder* StringBuilder::append(char16_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::append(char16_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

StringBuilder* StringBuilder::appendCodePoint(int32_t arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::appendCodePoint(int32_t arg0)");
	return 0;
}

StringBuilder* StringBuilder::delete_(int32_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::delete_(int32_t arg0, int32_t arg1)");
	return 0;
}

StringBuilder* StringBuilder::deleteCharAt(int32_t arg0)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::deleteCharAt(int32_t arg0)");
	return 0;
}

int32_t StringBuilder::indexOf(String* arg0)
{ /* stub */
	unimplemented_(u"int32_t StringBuilder::indexOf(String* arg0)");
	return 0;
}

int32_t StringBuilder::indexOf(String* arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"int32_t StringBuilder::indexOf(String* arg0, int32_t arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, Object* arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, Object* arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, String* arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, String* arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, char16_tArray* arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, char16_tArray* arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, CharSequence* arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, CharSequence* arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, bool arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, bool arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, char16_t arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, char16_t arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, int32_t arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, int64_t arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, int64_t arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, float arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, float arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, double arg1)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, double arg1)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, char16_tArray* arg1, int32_t arg2, int32_t arg3)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, char16_tArray* arg1, int32_t arg2, int32_t arg3)");
	return 0;
}

StringBuilder* StringBuilder::insert(int32_t arg0, CharSequence* arg1, int32_t arg2, int32_t arg3)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::insert(int32_t arg0, CharSequence* arg1, int32_t arg2, int32_t arg3)");
	return 0;
}

int32_t StringBuilder::lastIndexOf(String* arg0)
{ /* stub */
	unimplemented_(u"int32_t StringBuilder::lastIndexOf(String* arg0)");
	return 0;
}

int32_t StringBuilder::lastIndexOf(String* arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"int32_t StringBuilder::lastIndexOf(String* arg0, int32_t arg1)");
	return 0;
}

/* private: void StringBuilder::readObject(ObjectInputStream* arg0) */
StringBuilder* StringBuilder::replace(int32_t arg0, int32_t arg1, String* arg2)
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::replace(int32_t arg0, int32_t arg1, String* arg2)");
	return 0;
}

StringBuilder* StringBuilder::reverse()
{ /* stub */
	unimplemented_(u"StringBuilder* StringBuilder::reverse()");
	return 0;
}

String* StringBuilder::toString()
{ /* stub */
	return new String(cppwstring);
}

/* private: void StringBuilder::writeObject(ObjectOutputStream* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* StringBuilder::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.StringBuilder", 23);
    return c;
}

char16_t StringBuilder::charAt(int32_t index)
{
	return AbstractStringBuilder::charAt(index);
}

int32_t StringBuilder::length()
{
	return AbstractStringBuilder::length();
}

CharSequence* StringBuilder::subSequence(int32_t start, int32_t end)
{
	return AbstractStringBuilder::subSequence(start, end);
}

java::lang::Class* StringBuilder::getClass0()
{
	return class_();
}


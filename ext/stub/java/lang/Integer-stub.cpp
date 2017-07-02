// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#include <string>

#include <java/lang/Integer.h>
#include <java/lang/String.h>

#include <tdme/utils/_Console.h>

using std::stoi;

using java::lang::Integer;

using tdme::utils::_Console;


extern void unimplemented_(const char16_t* name);
java::lang::Integer::Integer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Integer::Integer(int32_t arg0)
	: Integer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Integer::Integer(String* arg0)
	: Integer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

char16_tArray* java::lang::Integer::DigitOnes;
char16_tArray* java::lang::Integer::DigitTens;
constexpr int32_t java::lang::Integer::MAX_VALUE;
constexpr int32_t java::lang::Integer::MIN_VALUE;
constexpr int32_t java::lang::Integer::SIZE;
Class* java::lang::Integer::TYPE;
char16_tArray* java::lang::Integer::digits;
String* java::lang::Integer::integerCacheHighPropValue;
constexpr int64_t java::lang::Integer::serialVersionUID;
int32_tArray* java::lang::Integer::sizeTable;

void Integer::ctor(int32_t arg0)
{ /* stub */
	value = arg0;
}

void Integer::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Integer::ctor(String* arg0)");
}

int32_t Integer::bitCount(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::bitCount(int32_t arg0)");
	return 0;
}

int8_t Integer::byteValue()
{ /* stub */
	unimplemented_(u"int8_t Integer::byteValue()");
	return 0;
}

int32_t Integer::compareTo(Integer* arg0)
{ /* stub */
	unimplemented_(u"int32_t Integer::compareTo(Integer* arg0)");
	return 0;
}

int32_t Integer::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< Integer* >(o));
}

Integer* Integer::decode(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Integer* Integer::decode(String* arg0)");
	return 0;
}

double Integer::doubleValue()
{ /* stub */
	unimplemented_(u"double Integer::doubleValue()");
	return 0;
}

bool Integer::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Integer::equals(Object* arg0)");
	return 0;
}

float Integer::floatValue()
{ /* stub */
	unimplemented_(u"float Integer::floatValue()");
	return 0;
}

void Integer::getAndRemoveCacheProperties()
{ /* stub */
	clinit();
	unimplemented_(u"void Integer::getAndRemoveCacheProperties()");
}

void Integer::getChars(int32_t arg0, int32_t arg1, char16_tArray* arg2)
{ /* stub */
	clinit();
	unimplemented_(u"void Integer::getChars(int32_t arg0, int32_t arg1, char16_tArray* arg2)");
}

Integer* Integer::getInteger(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Integer* Integer::getInteger(String* arg0)");
	return 0;
}

Integer* Integer::getInteger(String* arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"Integer* Integer::getInteger(String* arg0, int32_t arg1)");
	return 0;
}

Integer* Integer::getInteger(String* arg0, Integer* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"Integer* Integer::getInteger(String* arg0, Integer* arg1)");
	return 0;
}

int32_t Integer::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Integer::hashCode()");
	return 0;
}

int32_t Integer::highestOneBit(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::highestOneBit(int32_t arg0)");
	return 0;
}

int32_t Integer::intValue()
{
	return value;
}

int64_t Integer::longValue()
{ /* stub */
	unimplemented_(u"int64_t Integer::longValue()");
	return 0;
}

int32_t Integer::lowestOneBit(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::lowestOneBit(int32_t arg0)");
	return 0;
}

int32_t Integer::numberOfLeadingZeros(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::numberOfLeadingZeros(int32_t arg0)");
	return 0;
}

int32_t Integer::numberOfTrailingZeros(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::numberOfTrailingZeros(int32_t arg0)");
	return 0;
}

int32_t Integer::parseInt(String* arg0)
{ /* stub */
	clinit();
	return std::stoi(arg0->getCPPWString());
}

int32_t Integer::parseInt(String* arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::parseInt(String* arg0, int32_t arg1)");
	return 0;
}

int32_t Integer::reverse(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::reverse(int32_t arg0)");
	return 0;
}

int32_t Integer::reverseBytes(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::reverseBytes(int32_t arg0)");
	return 0;
}

int32_t Integer::rotateLeft(int32_t arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::rotateLeft(int32_t arg0, int32_t arg1)");
	return 0;
}

int32_t Integer::rotateRight(int32_t arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::rotateRight(int32_t arg0, int32_t arg1)");
	return 0;
}

int16_t Integer::shortValue()
{ /* stub */
	unimplemented_(u"int16_t Integer::shortValue()");
	return 0;
}

int32_t Integer::signum(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::signum(int32_t arg0)");
	return 0;
}

int32_t Integer::stringSize(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Integer::stringSize(int32_t arg0)");
	return 0;
}

String* Integer::toBinaryString(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* Integer::toBinaryString(int32_t arg0)");
	return 0;
}

String* Integer::toHexString(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* Integer::toHexString(int32_t arg0)");
	return 0;
}

String* Integer::toOctalString(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* Integer::toOctalString(int32_t arg0)");
	return 0;
}

String* Integer::toString()
{ /* stub */
	unimplemented_(u"String* Integer::toString()");
	return 0;
}

String* Integer::toString(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* Integer::toString(int32_t arg0)");
	return 0;
}

String* Integer::toString(int32_t arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"String* Integer::toString(int32_t arg0, int32_t arg1)");
	return 0;
}

/* private: String* Integer::toUnsignedString(int32_t arg0, int32_t arg1) */
Integer* Integer::valueOf(String* arg0)
{ /* stub */
	clinit();
	return new Integer(std::stoi(arg0->getCPPWString()));
}

Integer* Integer::valueOf(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Integer* Integer::valueOf(int32_t arg0)");
	return 0;
}

Integer* Integer::valueOf(String* arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"Integer* Integer::valueOf(String* arg0, int32_t arg1)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Integer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Integer", 17);
    return c;
}

java::lang::Class* Integer::getClass0()
{
	return class_();
}


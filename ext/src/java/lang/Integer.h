// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Number.h>
#include <java/lang/Comparable.h>

using java::lang::Number;
using java::lang::Comparable;
using java::lang::Class;
using java::lang::Object;
using java::lang::String;


struct default_init_tag;
class java::lang::Integer final
	: public Number
	, public Comparable
{

public:
	typedef Number super;

public: /* package */
	static char16_tArray* DigitOnes;
	static char16_tArray* DigitTens;

public:
	static constexpr int32_t MAX_VALUE { 2147483647 };
	static constexpr int32_t MIN_VALUE { -0x7fffffff-1 };
	static constexpr int32_t SIZE { 32 };
	static Class* TYPE;

public: /* package */
	static char16_tArray* digits;

private:
	static String* integerCacheHighPropValue;
	static constexpr int64_t serialVersionUID { 1360826667806852920LL };

public: /* package */
	static int32_tArray* sizeTable;

private:
	int32_t value {  };

protected:
	void ctor(int32_t arg0);
	void ctor(String* arg0);

public:
	static int32_t bitCount(int32_t arg0);
	int8_t byteValue() override;
	int32_t compareTo(Integer* arg0);
	static Integer* decode(String* arg0);
	double doubleValue() override;
	bool equals(Object* arg0) override;
	float floatValue() override;

public: /* package */
	static void getAndRemoveCacheProperties();
	static void getChars(int32_t arg0, int32_t arg1, char16_tArray* arg2);

public:
	static Integer* getInteger(String* arg0);
	static Integer* getInteger(String* arg0, int32_t arg1);
	static Integer* getInteger(String* arg0, Integer* arg1);
	int32_t hashCode() override;
	static int32_t highestOneBit(int32_t arg0);
	int32_t intValue() override;
	int64_t longValue() override;
	static int32_t lowestOneBit(int32_t arg0);
	static int32_t numberOfLeadingZeros(int32_t arg0);
	static int32_t numberOfTrailingZeros(int32_t arg0);
	static int32_t parseInt(String* arg0);
	static int32_t parseInt(String* arg0, int32_t arg1);
	static int32_t reverse(int32_t arg0);
	static int32_t reverseBytes(int32_t arg0);
	static int32_t rotateLeft(int32_t arg0, int32_t arg1);
	static int32_t rotateRight(int32_t arg0, int32_t arg1);
	int16_t shortValue() override;
	static int32_t signum(int32_t arg0);

public: /* package */
	static int32_t stringSize(int32_t arg0);

public:
	static String* toBinaryString(int32_t arg0);
	static String* toHexString(int32_t arg0);
	static String* toOctalString(int32_t arg0);
	String* toString() override;
	static String* toString(int32_t arg0);
	static String* toString(int32_t arg0, int32_t arg1);
	/*static String* toUnsignedString(int32_t arg0, int32_t arg1); (private) */
	static Integer* valueOf(String* arg0);
	static Integer* valueOf(int32_t arg0);
	static Integer* valueOf(String* arg0, int32_t arg1);

	// Generated
	Integer(int32_t arg0);
	Integer(String* arg0);
protected:
	Integer(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};

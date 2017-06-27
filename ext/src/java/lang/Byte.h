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
class java::lang::Byte final
	: public Number
	, public Comparable
{

public:
	typedef Number super;
	static constexpr int8_t MAX_VALUE { int8_t(127) };
	static constexpr int8_t MIN_VALUE { int8_t(-128) };
	static constexpr int32_t SIZE { 8 };
	static Class* TYPE;

private:
	static constexpr int64_t serialVersionUID { -7183698231559129828LL };
	int8_t value {  };

protected:
	void ctor(int8_t arg0);
	void ctor(String* arg0);

public:
	int8_t byteValue() override;
	int32_t compareTo(Byte* arg0);
	static Byte* decode(String* arg0);
	double doubleValue() override;
	bool equals(Object* arg0) override;
	float floatValue() override;
	int32_t hashCode() override;
	int32_t intValue() override;
	int64_t longValue() override;
	static int8_t parseByte(String* arg0);
	static int8_t parseByte(String* arg0, int32_t arg1);
	int16_t shortValue() override;
	String* toString() override;
	static String* toString(int8_t arg0);
	static Byte* valueOf(int8_t arg0);
	static Byte* valueOf(String* arg0);
	static Byte* valueOf(String* arg0, int32_t arg1);

	// Generated
	Byte(int8_t arg0);
	Byte(String* arg0);
protected:
	Byte(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};

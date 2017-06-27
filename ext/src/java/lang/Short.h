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
class java::lang::Short final
	: public Number
	, public Comparable
{

public:
	typedef Number super;
	static constexpr int16_t MAX_VALUE { 32767 };
	static constexpr int16_t MIN_VALUE { -32768 };
	static constexpr int32_t SIZE { 16 };
	static Class* TYPE;

private:
	static constexpr int64_t serialVersionUID { 7515723908773894738LL };
	int16_t value {  };

protected:
	void ctor(int16_t arg0);
	void ctor(String* arg0);

public:
	int8_t byteValue() override;
	int32_t compareTo(Short* arg0);
	static Short* decode(String* arg0);
	double doubleValue() override;
	bool equals(Object* arg0) override;
	float floatValue() override;
	int32_t hashCode() override;
	int32_t intValue() override;
	int64_t longValue() override;
	static int16_t parseShort(String* arg0);
	static int16_t parseShort(String* arg0, int32_t arg1);
	static int16_t reverseBytes(int16_t arg0);
	int16_t shortValue() override;
	String* toString() override;
	static String* toString(int16_t arg0);
	static Short* valueOf(String* arg0);
	static Short* valueOf(int16_t arg0);
	static Short* valueOf(String* arg0, int32_t arg1);

	// Generated
	Short(int16_t arg0);
	Short(String* arg0);
protected:
	Short(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};

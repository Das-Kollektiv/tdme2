// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::io::Serializable;


struct default_init_tag;
class java::lang::Number
	: public virtual Object
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	static constexpr int64_t serialVersionUID { -8742448824652078965LL };

protected:
	void ctor();

public:
	virtual int8_t byteValue();
	virtual double doubleValue() = 0;
	virtual float floatValue() = 0;
	virtual int32_t intValue() = 0;
	virtual int64_t longValue() = 0;
	virtual int16_t shortValue();

	// Generated
	Number();
protected:
	Number(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

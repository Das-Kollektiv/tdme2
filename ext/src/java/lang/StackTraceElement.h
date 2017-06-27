// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::String;


struct default_init_tag;
class java::lang::StackTraceElement final
	: public virtual Object
	, public Serializable
{

public:
	typedef Object super;

private:
	String* declaringClass {  };
	String* fileName {  };
	int32_t lineNumber {  };
	String* methodName {  };
	static constexpr int64_t serialVersionUID { 6992337162326171013LL };

protected:
	void ctor(String* arg0, String* arg1, String* arg2, int32_t arg3);
	/*static bool eq(Object* arg0, Object* arg1); (private) */

public:
	bool equals(Object* arg0) override;
	String* getClassName();
	String* getFileName();
	int32_t getLineNumber();
	String* getMethodName();
	int32_t hashCode() override;
	bool isNativeMethod();
	String* toString() override;

	// Generated
	StackTraceElement(String* arg0, String* arg1, String* arg2, int32_t arg3);
protected:
	StackTraceElement(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

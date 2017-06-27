// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/RuntimeException.h>

using java::lang::RuntimeException;
using java::lang::String;
using java::lang::Throwable;


struct default_init_tag;
class java::lang::UnsupportedOperationException
	: public RuntimeException
{

public:
	typedef RuntimeException super;

public: /* package */
	static constexpr int64_t serialVersionUID { -1242599979055084673LL };

protected:
	void ctor();
	void ctor(String* arg0);
	void ctor(Throwable* arg0);
	void ctor(String* arg0, Throwable* arg1);

	// Generated

public:
	UnsupportedOperationException();
	UnsupportedOperationException(String* arg0);
	UnsupportedOperationException(Throwable* arg0);
	UnsupportedOperationException(String* arg0, Throwable* arg1);
protected:
	UnsupportedOperationException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

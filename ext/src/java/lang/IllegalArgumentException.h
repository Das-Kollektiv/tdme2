// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/RuntimeException.h>

using java::lang::RuntimeException;
using java::lang::String;
using java::lang::Throwable;


struct default_init_tag;
class java::lang::IllegalArgumentException
	: public RuntimeException
{

public:
	typedef RuntimeException super;

private:
	static constexpr int64_t serialVersionUID { -5365630128856068164LL };

protected:
	void ctor();
	void ctor(String* arg0);
	void ctor(Throwable* arg0);
	void ctor(String* arg0, Throwable* arg1);

	// Generated

public:
	IllegalArgumentException();
	IllegalArgumentException(String* arg0);
	IllegalArgumentException(Throwable* arg0);
	IllegalArgumentException(String* arg0, Throwable* arg1);
protected:
	IllegalArgumentException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

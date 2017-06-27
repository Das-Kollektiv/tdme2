// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/lang/RuntimeException.h>

using java::lang::RuntimeException;
using java::lang::String;


struct default_init_tag;
class java::lang::NullPointerException
	: public RuntimeException
{

public:
	typedef RuntimeException super;

protected:
	void ctor();
	void ctor(String* arg0);

	// Generated

public:
	NullPointerException();
	NullPointerException(String* arg0);
protected:
	NullPointerException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Exception.h>

using java::lang::Exception;
using java::lang::String;
using java::lang::Throwable;


struct default_init_tag;
class java::lang::RuntimeException
	: public Exception
{

public:
	typedef Exception super;

public: /* package */
	static constexpr int64_t serialVersionUID { -7034897190745766939LL };

protected:
	void ctor();
	void ctor(String* arg0);
	void ctor(Throwable* arg0);
	void ctor(String* arg0, Throwable* arg1);

	// Generated

public:
	RuntimeException();
	RuntimeException(String* arg0);
	RuntimeException(Throwable* arg0);
	RuntimeException(String* arg0, Throwable* arg1);
protected:
	RuntimeException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

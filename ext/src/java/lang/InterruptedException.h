// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/lang/Exception.h>

using java::lang::Exception;
using java::lang::String;


struct default_init_tag;
class java::lang::InterruptedException
	: public Exception
{

public:
	typedef Exception super;

protected:
	void ctor();
	void ctor(String* arg0);

	// Generated

public:
	InterruptedException();
	InterruptedException(String* arg0);
protected:
	InterruptedException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

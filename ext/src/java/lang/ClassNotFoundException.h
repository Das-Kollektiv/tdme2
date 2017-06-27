// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Exception.h>

using java::lang::Exception;
using java::lang::String;
using java::lang::Throwable;


struct default_init_tag;
class java::lang::ClassNotFoundException
	: public Exception
{

public:
	typedef Exception super;

private:
	Throwable* ex {  };
	static constexpr int64_t serialVersionUID { 9176873029745254542LL };

protected:
	void ctor();
	void ctor(String* arg0);
	void ctor(String* arg0, Throwable* arg1);

public:
	Throwable* getCause() override;
	virtual Throwable* getException();

	// Generated
	ClassNotFoundException();
	ClassNotFoundException(String* arg0);
	ClassNotFoundException(String* arg0, Throwable* arg1);
protected:
	ClassNotFoundException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

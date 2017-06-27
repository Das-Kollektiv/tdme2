// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Exception.h>

using java::lang::Exception;
using java::lang::String;
using java::lang::Throwable;


struct default_init_tag;
class java::io::IOException
	: public Exception
{

public:
	typedef Exception super;

public: /* package */
	static constexpr int64_t serialVersionUID { 7818375828146090155LL };

protected:
	void ctor();
	void ctor(String* arg0);
	void ctor(Throwable* arg0);
	void ctor(String* arg0, Throwable* arg1);

	// Generated

public:
	IOException();
	IOException(String* arg0);
	IOException(Throwable* arg0);
	IOException(String* arg0, Throwable* arg1);
protected:
	IOException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

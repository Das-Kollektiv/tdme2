// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Throwable.h>

using java::lang::Throwable;
using java::lang::String;


struct default_init_tag;
class java::lang::Exception
	: public Throwable
{

public:
	typedef Throwable super;

public: /* package */
	static constexpr int64_t serialVersionUID { -3387516993124229948LL };

protected:
	void ctor();
	void ctor(String* arg0);
	void ctor(Throwable* arg0);
	void ctor(String* arg0, Throwable* arg1);

	// Generated

public:
	Exception();
	Exception(String* arg0);
	Exception(Throwable* arg0);
	Exception(String* arg0, Throwable* arg1);
protected:
	Exception(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

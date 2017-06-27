// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/IllegalArgumentException.h>

using java::lang::IllegalArgumentException;
using java::lang::String;


struct default_init_tag;
class java::lang::NumberFormatException
	: public IllegalArgumentException
{

public:
	typedef IllegalArgumentException super;

public: /* package */
	static constexpr int64_t serialVersionUID { -2848938806368998894LL };

protected:
	void ctor();
	void ctor(String* arg0);

public: /* package */
	static NumberFormatException* forInputString(String* arg0);

	// Generated

public:
	NumberFormatException();
	NumberFormatException(String* arg0);
protected:
	NumberFormatException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

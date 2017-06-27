// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/io/IOException.h>

using java::io::IOException;
using java::lang::String;


struct default_init_tag;
class java::io::FileNotFoundException
	: public IOException
{

public:
	typedef IOException super;

protected:
	void ctor();
	void ctor(String* arg0);
	/*void ctor(String* arg0, String* arg1); (private) */

	// Generated

public:
	FileNotFoundException();
	FileNotFoundException(String* arg0);
protected:
	FileNotFoundException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

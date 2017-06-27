// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/security/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;
using java::security::SecureRandom;


struct default_init_tag;
class java::io::File_LazyInitialization
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	static SecureRandom* random;
	static String* temporaryDirectory_;

	/*void ctor(); (private) */
	static String* temporaryDirectory();

	// Generated

public:
	File_LazyInitialization();
protected:
	File_LazyInitialization(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

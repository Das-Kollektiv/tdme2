// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;
class java::nio::ByteOrder final
	: public Object
{

public:
	typedef Object super;
	static ByteOrder* BIG_ENDIAN_;
	static ByteOrder* LITTLE_ENDIAN_;

private:
	String* name {  };

	/*void ctor(String* arg0); (private) */

public:
	static ByteOrder* nativeOrder();
	String* toString() override;

	// Generated
	ByteOrder();
protected:
	ByteOrder(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

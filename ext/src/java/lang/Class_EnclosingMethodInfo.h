// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::Class;
using java::lang::String;

using java::lang::ObjectArray;

struct default_init_tag;
class java::lang::Class_EnclosingMethodInfo final
	: public Object
{

public:
	typedef Object super;

public: /* package */
	static bool $assertionsDisabled;

private:
	String* descriptor {  };
	Class* enclosingClass {  };
	String* name {  };

	/*void ctor(ObjectArray* arg0); (private) */

public: /* package */
	String* getDescriptor();
	Class* getEnclosingClass();
	String* getName();
	bool isConstructor();
	bool isMethod();
	bool isPartial();

	// Generated

public:
	Class_EnclosingMethodInfo();
protected:
	Class_EnclosingMethodInfo(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

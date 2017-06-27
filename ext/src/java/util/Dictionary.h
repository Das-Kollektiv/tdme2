// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::util::Enumeration;


struct default_init_tag;
class java::util::Dictionary
	: public virtual Object
{

public:
	typedef Object super;

protected:
	void ctor();

public:
	virtual Enumeration* elements() = 0;
	virtual Object* get(Object* arg0) = 0;
	virtual bool isEmpty() = 0;
	virtual Enumeration* keys() = 0;
	virtual Object* put(Object* arg0, Object* arg1) = 0;
	virtual Object* remove(Object* arg0) = 0;
	virtual int32_t size() = 0;

	// Generated
	Dictionary();
protected:
	Dictionary(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

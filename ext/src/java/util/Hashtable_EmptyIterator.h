// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Iterator.h>

using java::lang::Object;
using java::util::Iterator;


struct default_init_tag;
class java::util::Hashtable_EmptyIterator
	: public virtual Object
	, public virtual Iterator
{

public:
	typedef Object super;

protected:
	void ctor();

public:
	bool hasNext() override;
	Object* next() override;
	void remove() override;

	// Generated

public: /* package */
	Hashtable_EmptyIterator();
protected:
	Hashtable_EmptyIterator(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/Iterator.h>

using java::util::Iterator;
using java::lang::Object;


struct java::util::ListIterator
	: public virtual Iterator
{

	virtual void add(Object* arg0) = 0;
	/*bool hasNext(); (already declared) */
	virtual bool hasPrevious() = 0;
	/*Object* next(); (already declared) */
	virtual int32_t nextIndex() = 0;
	virtual Object* previous() = 0;
	virtual int32_t previousIndex() = 0;
	/*void remove(); (already declared) */
	virtual void set(Object* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

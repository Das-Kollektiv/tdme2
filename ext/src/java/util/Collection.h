// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Iterable.h>

using java::lang::Iterable;
using java::lang::Object;
using java::util::Iterator;

using java::lang::ObjectArray;

struct java::util::Collection
	: public virtual Iterable
{

	virtual bool add(Object* arg0) = 0;
	virtual bool addAll(Collection* arg0) = 0;
	virtual void clear() = 0;
	virtual bool contains(Object* arg0) = 0;
	virtual bool containsAll(Collection* arg0) = 0;
	/*virtual bool equals(Object* arg0); (already declared) */
	/*virtual int32_t hashCode(); (already declared) */
	virtual bool isEmpty() = 0;
	/*Iterator* iterator(); (already declared) */
	virtual bool remove(Object* arg0) = 0;
	virtual bool removeAll(Collection* arg0) = 0;
	virtual bool retainAll(Collection* arg0) = 0;
	virtual int32_t size() = 0;
	virtual ObjectArray* toArray() = 0;
	virtual ObjectArray* toArray(ObjectArray* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};

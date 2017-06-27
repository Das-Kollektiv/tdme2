// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/Collection.h>

using java::util::Collection;
using java::lang::Object;
using java::util::Iterator;
using java::util::ListIterator;

using java::lang::ObjectArray;

struct java::util::List
	: public virtual Collection
{

	/*bool add(Object* arg0); (already declared) */
	virtual void add(int32_t arg0, Object* arg1) = 0;
	/*bool addAll(Collection* arg0); (already declared) */
	virtual bool addAll(int32_t arg0, Collection* arg1) = 0;
	/*void clear(); (already declared) */
	/*bool contains(Object* arg0); (already declared) */
	/*bool containsAll(Collection* arg0); (already declared) */
	/*bool equals(Object* arg0); (already declared) */
	virtual Object* get(int32_t arg0) = 0;
	/*int32_t hashCode(); (already declared) */
	virtual int32_t indexOf(Object* arg0) = 0;
	/*bool isEmpty(); (already declared) */
	/*Iterator* iterator(); (already declared) */
	virtual int32_t lastIndexOf(Object* arg0) = 0;
	virtual ListIterator* listIterator() = 0;
	virtual ListIterator* listIterator(int32_t arg0) = 0;
	/*bool remove(Object* arg0); (already declared) */
	virtual Object* remove(int32_t arg0) = 0;
	/*bool removeAll(Collection* arg0); (already declared) */
	/*bool retainAll(Collection* arg0); (already declared) */
	virtual Object* set(int32_t arg0, Object* arg1) = 0;
	/*int32_t size(); (already declared) */
	virtual List* subList(int32_t arg0, int32_t arg1) = 0;
	/*ObjectArray* toArray(); (already declared) */
	/*ObjectArray* toArray(ObjectArray* arg0); (already declared) */

	// Generated
	static ::java::lang::Class *class_();
	virtual bool add(Object* arg0) = 0;
	virtual bool addAll(Collection* arg0) = 0;
	virtual bool remove(Object* arg0) = 0;
};

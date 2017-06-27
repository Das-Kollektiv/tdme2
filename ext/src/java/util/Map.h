// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::util::Collection;
using java::util::Set;


struct java::util::Map
	: public virtual Object
{

	virtual void clear() = 0;
	virtual bool containsKey(Object* arg0) = 0;
	virtual bool containsValue(Object* arg0) = 0;
	virtual Set* entrySet() = 0;
	/*virtual bool equals(Object* arg0); (already declared) */
	virtual Object* get(Object* arg0) = 0;
	/*virtual int32_t hashCode(); (already declared) */
	virtual bool isEmpty() = 0;
	virtual Set* keySet() = 0;
	virtual Object* put(Object* arg0, Object* arg1) = 0;
	virtual void putAll(Map* arg0) = 0;
	virtual Object* remove(Object* arg0) = 0;
	virtual int32_t size() = 0;
	virtual Collection* values() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Collection.h>

using java::lang::Object;
using java::util::Collection;
using java::lang::String;
using java::util::Iterator;

using java::lang::ObjectArray;

struct default_init_tag;
class java::util::AbstractCollection
	: public virtual Object
	, public virtual Collection
{

public:
	typedef Object super;

protected:
	void ctor();

public:
	bool add(Object* arg0) override;
	bool addAll(Collection* arg0) override;
	void clear() override;
	bool contains(Object* arg0) override;
	bool containsAll(Collection* arg0) override;
	/*static ObjectArray* finishToArray(ObjectArray* arg0, Iterator* arg1); (private) */
	bool isEmpty() override;
	/*Iterator* iterator(); (already declared) */
	bool remove(Object* arg0) override;
	bool removeAll(Collection* arg0) override;
	bool retainAll(Collection* arg0) override;
	/*int32_t size(); (already declared) */
	ObjectArray* toArray() override;
	ObjectArray* toArray(ObjectArray* arg0) override;
	String* toString() override;

	// Generated

public: /* protected */
	AbstractCollection();
protected:
	AbstractCollection(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual bool equals(Object* o);
	virtual int32_t hashCode();

private:
	virtual ::java::lang::Class* getClass0();
};

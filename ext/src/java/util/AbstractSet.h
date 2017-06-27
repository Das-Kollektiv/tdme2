// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractCollection.h>
#include <java/util/Set.h>

using java::util::AbstractCollection;
using java::util::Set;
using java::lang::Object;
using java::util::Collection;

using java::lang::ObjectArray;

struct default_init_tag;
class java::util::AbstractSet
	: public AbstractCollection
	, public virtual Set
{

public:
	typedef AbstractCollection super;

protected:
	void ctor();

public:
	bool equals(Object* arg0) override;
	int32_t hashCode() override;
	bool removeAll(Collection* arg0) override;

	// Generated

public: /* protected */
	AbstractSet();
protected:
	AbstractSet(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	bool add(Object* e);
	bool addAll(Collection* c);
	void clear();
	bool contains(Object* o);
	bool containsAll(Collection* c);
	bool isEmpty();
	bool remove(Object* o);
	bool retainAll(Collection* c);
	ObjectArray* toArray();
	ObjectArray* toArray(ObjectArray* a);

private:
	virtual ::java::lang::Class* getClass0();
};

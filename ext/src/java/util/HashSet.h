// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractSet.h>
#include <java/util/Set.h>
#include <java/lang/Cloneable.h>
#include <java/io/Serializable.h>

using java::util::AbstractSet;
using java::util::Set;
using java::lang::Cloneable;
using java::io::Serializable;
using java::io::ObjectInputStream;
using java::io::ObjectOutputStream;
using java::lang::Object;
using java::util::Collection;
using java::util::HashMap;
using java::util::Iterator;

using java::lang::ObjectArray;

struct default_init_tag;
class java::util::HashSet
	: public AbstractSet
	, public virtual Set
	, public virtual Cloneable
	, public virtual Serializable
{

public:
	typedef AbstractSet super;

private:
	static Object* PRESENT;
	HashMap* map {  };

public: /* package */
	static constexpr int64_t serialVersionUID { -5024744406713321676LL };

protected:
	void ctor();
	void ctor(Collection* arg0);
	void ctor(int32_t arg0);
	void ctor(int32_t arg0, float arg1);
	void ctor(int32_t arg0, float arg1, bool arg2);

public:
	bool add(Object* arg0) override;
	void clear() override;
	Object* clone() override;
	bool contains(Object* arg0) override;
	bool isEmpty() override;
	Iterator* iterator() override;
	/*void readObject(ObjectInputStream* arg0); (private) */
	bool remove(Object* arg0) override;
	int32_t size() override;
	/*void writeObject(ObjectOutputStream* arg0); (private) */

	// Generated
	HashSet();
	HashSet(Collection* arg0);
	HashSet(int32_t arg0);
	HashSet(int32_t arg0, float arg1);

public: /* package */
	HashSet(int32_t arg0, float arg1, bool arg2);
protected:
	HashSet(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	bool addAll(Collection* arg0);
	bool containsAll(Collection* arg0);
	bool equals(Object* arg0);
	int32_t hashCode();
	bool removeAll(Collection* arg0);
	bool retainAll(Collection* arg0);
	ObjectArray* toArray();
	ObjectArray* toArray(ObjectArray* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};

// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractCollection.h>
#include <java/util/List.h>

using java::util::AbstractCollection;
using java::util::List;
using java::lang::Object;
using java::util::Collection;
using java::util::Iterator;
using java::util::ListIterator;

using java::lang::ObjectArray;

struct default_init_tag;
class java::util::AbstractList
	: public AbstractCollection
	, public virtual List
{

public:
	typedef AbstractCollection super;

public: /* protected */
	int32_t modCount {  };

protected:
	void ctor();

public:
	bool add(Object* arg0) override;
	void add(int32_t arg0, Object* arg1) override;
	bool addAll(int32_t arg0, Collection* arg1) override;
	void clear() override;
	bool equals(Object* arg0) override;
	/*Object* get(int32_t arg0); (already declared) */
	int32_t hashCode() override;
	int32_t indexOf(Object* arg0) override;
	Iterator* iterator() override;
	int32_t lastIndexOf(Object* arg0) override;
	ListIterator* listIterator() override;
	ListIterator* listIterator(int32_t arg0) override;
	Object* remove(int32_t arg0) override;

public: /* protected */
	virtual void removeRange(int32_t arg0, int32_t arg1);

public:
	Object* set(int32_t arg0, Object* arg1) override;
	List* subList(int32_t arg0, int32_t arg1) override;

	// Generated

public: /* protected */
	AbstractList();
protected:
	AbstractList(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	bool addAll(Collection* arg0);
	bool contains(Object* arg0);
	bool containsAll(Collection* arg0);
	bool isEmpty();
	bool remove(Object* arg0);
	bool removeAll(Collection* arg0);
	bool retainAll(Collection* arg0);
	ObjectArray* toArray();
	ObjectArray* toArray(ObjectArray* arg0);

private:
	virtual ::java::lang::Class* getClass0();
};

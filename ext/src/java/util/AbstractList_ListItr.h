// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractList_Itr.h>
#include <java/util/ListIterator.h>

using java::util::AbstractList_Itr;
using java::util::ListIterator;
using java::lang::Object;
using java::util::AbstractList;


struct default_init_tag;
class java::util::AbstractList_ListItr
	: public AbstractList_Itr
	, public virtual ListIterator
{

public:
	typedef AbstractList_Itr super;

public: /* package */
	AbstractList* this$0 {  };

protected:
	void ctor(int32_t arg0);

public:
	void add(Object* arg0) override;
	bool hasPrevious() override;
	int32_t nextIndex() override;
	Object* previous() override;
	int32_t previousIndex() override;
	void set(Object* arg0) override;

	// Generated

public: /* package */
	AbstractList_ListItr(AbstractList *AbstractList_this, int32_t arg0);
protected:
	AbstractList_ListItr(AbstractList *AbstractList_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	bool hasNext();
	Object* next();
	void remove();

private:
	virtual ::java::lang::Class* getClass0();
};

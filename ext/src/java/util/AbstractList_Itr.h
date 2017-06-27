// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Iterator.h>

using java::lang::Object;
using java::util::Iterator;
using java::util::AbstractList;


struct default_init_tag;
class java::util::AbstractList_Itr
	: public virtual Object
	, public virtual Iterator
{

public:
	typedef Object super;

public: /* package */
	int32_t cursor {  };
	int32_t expectedModCount {  };
	int32_t lastRet {  };
	AbstractList* this$0 {  };

	/*void ctor(); (private) */
	void checkForComodification();

public:
	bool hasNext() override;
	Object* next() override;
	void remove() override;

	// Generated
	AbstractList_Itr(AbstractList *AbstractList_this);
protected:
	AbstractList_Itr(AbstractList *AbstractList_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	AbstractList *AbstractList_this;

private:
	virtual ::java::lang::Class* getClass0();
};

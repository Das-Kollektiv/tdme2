// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Iterator.h>

using java::lang::Object;
using java::util::Iterator;
using java::util::HashMap_Entry;
using java::util::HashMap;


struct default_init_tag;
class java::util::HashMap_HashIterator
	: public virtual Object
	, public virtual Iterator
{

public:
	typedef Object super;

public: /* package */
	HashMap_Entry* current {  };
	int32_t expectedModCount {  };
	int32_t index {  };
	HashMap_Entry* next {  };
	HashMap* this$0 {  };

protected:
	void ctor();

public:
	bool hasNext() override;

public: /* package */
	HashMap_Entry* nextEntry();

public:
	void remove() override;

	// Generated

public: /* package */
	HashMap_HashIterator(HashMap *HashMap_this);
protected:
	HashMap_HashIterator(HashMap *HashMap_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	HashMap *HashMap_this;

private:
	virtual ::java::lang::Class* getClass0();
};

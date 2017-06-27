// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/HashMap_HashIterator.h>

using java::util::HashMap_HashIterator;
using java::lang::Object;
using java::util::HashMap;


struct default_init_tag;
class java::util::HashMap_ValueIterator final
	: public HashMap_HashIterator
{

public:
	typedef HashMap_HashIterator super;

public: /* package */
	HashMap* this$0 {  };

	/*void ctor(); (private) */

public:
	Object* next() override;

	// Generated
	HashMap_ValueIterator(HashMap *HashMap_this);
protected:
	HashMap_ValueIterator(HashMap *HashMap_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

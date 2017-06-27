// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/util/fwd-tdme.h>
#include <java/util/HashMap_HashIterator.h>
#include <java/util/Map_Entry.h>

using java::util::HashMap_HashIterator;
using java::util::HashMap;
using java::util::Map_Entry;


struct default_init_tag;
class java::util::HashMap_EntryIterator final
	: public HashMap_HashIterator
{

public:
	typedef HashMap_HashIterator super;

public: /* package */
	HashMap* this$0 {  };

	/*void ctor(); (private) */

public:
	Map_Entry* next() override;

	// Generated
	HashMap_EntryIterator(HashMap *HashMap_this);
protected:
	HashMap_EntryIterator(HashMap *HashMap_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractSet.h>

using java::util::AbstractSet;
using java::lang::Object;
using java::util::HashMap;
using java::util::Iterator;


struct default_init_tag;
class java::util::HashMap_EntrySet final
	: public AbstractSet
{

public:
	typedef AbstractSet super;

public: /* package */
	HashMap* this$0 {  };

	/*void ctor(); (private) */

public:
	void clear() override;
	bool contains(Object* arg0) override;
	Iterator* iterator() override;
	bool remove(Object* arg0) override;
	int32_t size() override;

	// Generated
	HashMap_EntrySet(HashMap *HashMap_this);
protected:
	HashMap_EntrySet(HashMap *HashMap_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	HashMap *HashMap_this;

private:
	virtual ::java::lang::Class* getClass0();
};

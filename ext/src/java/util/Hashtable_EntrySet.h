// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractSet.h>

using java::util::AbstractSet;
using java::lang::Object;
using java::util::Hashtable;
using java::util::Iterator;
using java::util::Map_Entry;


struct default_init_tag;
class java::util::Hashtable_EntrySet
	: public AbstractSet
{

public:
	typedef AbstractSet super;

public: /* package */
	Hashtable* this$0 {  };

	/*void ctor(); (private) */

public:
	virtual bool add(Map_Entry* arg0);
	void clear() override;
	bool contains(Object* arg0) override;
	Iterator* iterator() override;
	bool remove(Object* arg0) override;
	int32_t size() override;

	// Generated
	Hashtable_EntrySet(Hashtable *Hashtable_this);
protected:
	Hashtable_EntrySet(Hashtable *Hashtable_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	bool add(Object* arg0) override;
	Hashtable *Hashtable_this;

private:
	virtual ::java::lang::Class* getClass0();
};

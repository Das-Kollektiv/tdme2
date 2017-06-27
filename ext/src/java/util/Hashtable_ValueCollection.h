// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/AbstractCollection.h>

using java::util::AbstractCollection;
using java::lang::Object;
using java::util::Hashtable;
using java::util::Iterator;


struct default_init_tag;
class java::util::Hashtable_ValueCollection
	: public AbstractCollection
{

public:
	typedef AbstractCollection super;

public: /* package */
	Hashtable* this$0 {  };

	/*void ctor(); (private) */

public:
	void clear() override;
	bool contains(Object* arg0) override;
	Iterator* iterator() override;
	int32_t size() override;

	// Generated
	Hashtable_ValueCollection(Hashtable *Hashtable_this);
protected:
	Hashtable_ValueCollection(Hashtable *Hashtable_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	Hashtable *Hashtable_this;

private:
	virtual ::java::lang::Class* getClass0();
};

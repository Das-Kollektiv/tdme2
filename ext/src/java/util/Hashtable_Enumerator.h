// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Enumeration.h>
#include <java/util/Iterator.h>

using java::lang::Object;
using java::util::Enumeration;
using java::util::Iterator;
using java::util::Hashtable_Entry;
using java::util::Hashtable;
using java::util::Map_Entry;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace util {
typedef ::SubArray< ::java::util::Map_Entry, ::java::lang::ObjectArray > Map_EntryArray;
typedef ::SubArray< ::java::util::Hashtable_Entry, ::java::lang::ObjectArray, Map_EntryArray > Hashtable_EntryArray;
}  // namespace util
}  // namespace java

using java::lang::ObjectArray;
using java::util::Hashtable_EntryArray;
using java::util::Map_EntryArray;

struct default_init_tag;
class java::util::Hashtable_Enumerator
	: public virtual Object
	, public virtual Enumeration
	, public virtual Iterator
{

public:
	typedef Object super;

public: /* package */
	Hashtable_Entry* entry {  };

public: /* protected */
	int32_t expectedModCount {  };

public: /* package */
	int32_t index {  };
	bool iterator {  };
	Hashtable_Entry* lastReturned {  };
	Hashtable_EntryArray* table {  };
	Hashtable* this$0 {  };
	int32_t type {  };

protected:
	void ctor(int32_t arg0, bool arg1);

public:
	bool hasMoreElements() override;
	bool hasNext() override;
	Object* next() override;
	Object* nextElement() override;
	void remove() override;

	// Generated

public: /* package */
	Hashtable_Enumerator(Hashtable *Hashtable_this, int32_t arg0, bool arg1);
protected:
	Hashtable_Enumerator(Hashtable *Hashtable_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	Hashtable *Hashtable_this;

private:
	virtual ::java::lang::Class* getClass0();
};

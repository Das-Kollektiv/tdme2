// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Map_Entry.h>

using java::lang::Object;
using java::util::Map_Entry;
using java::lang::String;
using java::util::HashMap;


struct default_init_tag;
class java::util::HashMap_Entry
	: public virtual Object
	, public virtual Map_Entry
{

public:
	typedef Object super;

public: /* package */
	int32_t hash {  };
	Object* key {  };
	HashMap_Entry* next {  };
	Object* value {  };

protected:
	void ctor(int32_t arg0, Object* arg1, Object* arg2, HashMap_Entry* arg3);

public:
	bool equals(Object* arg0) override;
	Object* getKey() override;
	Object* getValue() override;
	int32_t hashCode() override;

public: /* package */
	virtual void recordAccess(HashMap* arg0);
	virtual void recordRemoval(HashMap* arg0);

public:
	Object* setValue(Object* arg0) override;
	String* toString() override;

	// Generated

public: /* package */
	HashMap_Entry(int32_t arg0, Object* arg1, Object* arg2, HashMap_Entry* arg3);
protected:
	HashMap_Entry(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

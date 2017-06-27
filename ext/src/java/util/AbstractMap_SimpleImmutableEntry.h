// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Map_Entry.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::util::Map_Entry;
using java::io::Serializable;
using java::lang::String;


struct default_init_tag;
class java::util::AbstractMap_SimpleImmutableEntry
	: public virtual Object
	, public virtual Map_Entry
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	Object* key {  };
	static constexpr int64_t serialVersionUID { 7138329143949025153LL };
	Object* value {  };

protected:
	void ctor(Map_Entry* arg0);
	void ctor(Object* arg0, Object* arg1);

public:
	bool equals(Object* arg0) override;
	Object* getKey() override;
	Object* getValue() override;
	int32_t hashCode() override;
	Object* setValue(Object* arg0) override;
	String* toString() override;

	// Generated
	AbstractMap_SimpleImmutableEntry(Map_Entry* arg0);
	AbstractMap_SimpleImmutableEntry(Object* arg0, Object* arg1);
protected:
	AbstractMap_SimpleImmutableEntry(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

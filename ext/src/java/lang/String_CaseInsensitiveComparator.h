// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/util/Comparator.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::util::Comparator;
using java::io::Serializable;
using java::lang::String;


struct default_init_tag;
class java::lang::String_CaseInsensitiveComparator
	: public virtual Object
	, public virtual Comparator
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	static constexpr int64_t serialVersionUID { 8575799808933029326LL };

	/*void ctor(); (private) */

public:
	virtual int32_t compare(String* arg0, String* arg1);

	// Generated
	String_CaseInsensitiveComparator();
protected:
	String_CaseInsensitiveComparator(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual bool equals(Object* obj);
	virtual int32_t compare(Object* o1, Object* o2) override;

private:
	virtual ::java::lang::Class* getClass0();
};

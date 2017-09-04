// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/lang/Comparable.h>
#include <java/io/Serializable.h>

using std::wstring;

using java::lang::Object;
using java::lang::Comparable;
using java::io::Serializable;
using java::io::ObjectInputStream;
using java::lang::Class;
using java::lang::String;


struct default_init_tag;
class java::lang::Enum
	: public virtual Object
	, public virtual Comparable
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	wstring name_ {  };
	int32_t ordinal_ {  };

protected:
	void ctor(const wstring& arg0, int32_t arg1);

public: /* protected */
	Object* clone() override;

public:
	int32_t compareTo(Enum* arg0);
	bool equals(Object* arg0) override;

public: /* protected */
	void finalize() override;

public:
	Class* getDeclaringClass();
	int32_t hashCode() override;
	const wstring& name();
	int32_t ordinal();
	/*void readObject(ObjectInputStream* arg0); (private) */
	/*void readObjectNoData(); (private) */
	String* toString() override;
	const wstring& toWString();
	static Enum* valueOf(Class* arg0, String* arg1);

	// Generated

public: /* protected */
	Enum(const wstring& arg0, int32_t arg1);
protected:
	Enum(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};

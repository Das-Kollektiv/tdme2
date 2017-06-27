// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::String;


struct default_init_tag;
class java::util::EventObject
	: public virtual Object
	, public virtual Serializable
{

public:
	typedef Object super;

private:
	static constexpr int64_t serialVersionUID { 5516075349620653480LL };

public: /* protected */
	Object* source {  };

protected:
	void ctor(Object* arg0);

public:
	virtual Object* getSource();
	String* toString() override;

	// Generated
	EventObject(Object* arg0);
protected:
	EventObject(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

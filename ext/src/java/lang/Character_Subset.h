// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;
class java::lang::Character_Subset
	: public virtual Object
{

public:
	typedef Object super;

private:
	String* name {  };

protected:
	void ctor(String* name);

public:
	bool equals(Object* obj) override;
	int32_t hashCode() override;
	String* toString() override;

	// Generated

public: /* protected */
	Character_Subset(String* name);
protected:
	Character_Subset(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

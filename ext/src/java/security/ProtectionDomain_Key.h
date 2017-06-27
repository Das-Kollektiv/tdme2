// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/security/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::security::ProtectionDomain;


struct default_init_tag;
class java::security::ProtectionDomain_Key final
	: public Object
{

public:
	typedef Object super;

public: /* package */
	ProtectionDomain* this$0 {  };

protected:
	void ctor();

	// Generated

public: /* package */
	ProtectionDomain_Key(ProtectionDomain *ProtectionDomain_this);
protected:
	ProtectionDomain_Key(ProtectionDomain *ProtectionDomain_this, const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	ProtectionDomain *ProtectionDomain_this;

private:
	virtual ::java::lang::Class* getClass0();
};

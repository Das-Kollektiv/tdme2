// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/security/fwd-tdme.h>
#include <sun/security/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::ClassLoader;
using java::lang::String;
using java::security::CodeSource;
using java::security::Permission;
using java::security::PermissionCollection;
using java::security::Principal;
using java::security::ProtectionDomain_Key;
using sun::security::util::Debug;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace security {
typedef ::SubArray< ::java::security::Principal, ::java::lang::ObjectArray > PrincipalArray;
}  // namespace security
}  // namespace java

using java::lang::ObjectArray;
using java::security::PrincipalArray;

struct default_init_tag;
class java::security::ProtectionDomain
	: public virtual Object
{

public:
	typedef Object super;

private:
	ClassLoader* classloader {  };
	CodeSource* codesource {  };
	static Debug* debug;
	bool hasAllPerm {  };

public: /* package */
	ProtectionDomain_Key* key {  };

private:
	PermissionCollection* permissions {  };
	PrincipalArray* principals {  };
	bool staticPermissions {  };

protected:
	void ctor(CodeSource* arg0, PermissionCollection* arg1);
	void ctor(CodeSource* arg0, PermissionCollection* arg1, ClassLoader* arg2, PrincipalArray* arg3);

public:
	ClassLoader* getClassLoader();
	CodeSource* getCodeSource();
	PermissionCollection* getPermissions();
	PrincipalArray* getPrincipals();
	virtual bool implies(Permission* arg0);

public: /* package */
	virtual bool impliesCreateAccessControlContext();
	/*PermissionCollection* mergePermissions(); (private) */
	/*static bool seeAllp(); (private) */

public:
	String* toString() override;

	// Generated
	ProtectionDomain(CodeSource* arg0, PermissionCollection* arg1);
	ProtectionDomain(CodeSource* arg0, PermissionCollection* arg1, ClassLoader* arg2, PrincipalArray* arg3);
protected:
	ProtectionDomain(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

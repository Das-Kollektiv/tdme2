// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/security/ProtectionDomain.h>

using java::security::ProtectionDomain;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace security {
typedef ::SubArray< ::java::security::Principal, ::java::lang::ObjectArray > PrincipalArray;
}  // namespace security
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::security::ProtectionDomain::ProtectionDomain(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::security::ProtectionDomain::ProtectionDomain(CodeSource* arg0, PermissionCollection* arg1)
	: ProtectionDomain(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::security::ProtectionDomain::ProtectionDomain(CodeSource* arg0, PermissionCollection* arg1, ClassLoader* arg2, PrincipalArray* arg3)
	: ProtectionDomain(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

Debug* java::security::ProtectionDomain::debug;

void ProtectionDomain::ctor(CodeSource* arg0, PermissionCollection* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ProtectionDomain::ctor(CodeSource* arg0, PermissionCollection* arg1)");
}

void ProtectionDomain::ctor(CodeSource* arg0, PermissionCollection* arg1, ClassLoader* arg2, PrincipalArray* arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ProtectionDomain::ctor(CodeSource* arg0, PermissionCollection* arg1, ClassLoader* arg2, PrincipalArray* arg3)");
}

ClassLoader* ProtectionDomain::getClassLoader()
{ /* stub */
	unimplemented_(u"ClassLoader* ProtectionDomain::getClassLoader()");
	return 0;
}

CodeSource* ProtectionDomain::getCodeSource()
{ /* stub */
	unimplemented_(u"CodeSource* ProtectionDomain::getCodeSource()");
	return 0;
}

PermissionCollection* ProtectionDomain::getPermissions()
{ /* stub */
return permissions ; /* getter */
}

PrincipalArray* ProtectionDomain::getPrincipals()
{ /* stub */
return principals ; /* getter */
}

bool ProtectionDomain::implies(Permission* arg0)
{ /* stub */
	unimplemented_(u"bool ProtectionDomain::implies(Permission* arg0)");
	return 0;
}

bool ProtectionDomain::impliesCreateAccessControlContext()
{ /* stub */
	unimplemented_(u"bool ProtectionDomain::impliesCreateAccessControlContext()");
	return 0;
}

/* private: PermissionCollection* ProtectionDomain::mergePermissions() */
/* private: bool ProtectionDomain::seeAllp() */
String* ProtectionDomain::toString()
{ /* stub */
	unimplemented_(u"String* ProtectionDomain::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ProtectionDomain::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.security.ProtectionDomain", 30);
    return c;
}

java::lang::Class* ProtectionDomain::getClass0()
{
	return class_();
}


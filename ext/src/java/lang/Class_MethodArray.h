// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/reflect/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::reflect::AccessibleObject;
using java::lang::reflect::AnnotatedElement;
using java::lang::reflect::GenericDeclaration;
using java::lang::reflect::Member;
using java::lang::reflect::Method;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace lang {
namespace reflect {
typedef ::SubArray< ::java::lang::reflect::AnnotatedElement, ::java::lang::ObjectArray > AnnotatedElementArray;
typedef ::SubArray< ::java::lang::reflect::AccessibleObject, ::java::lang::ObjectArray, AnnotatedElementArray > AccessibleObjectArray;
typedef ::SubArray< ::java::lang::reflect::GenericDeclaration, ::java::lang::ObjectArray > GenericDeclarationArray;
typedef ::SubArray< ::java::lang::reflect::Member, ::java::lang::ObjectArray > MemberArray;
typedef ::SubArray< ::java::lang::reflect::Method, AccessibleObjectArray, GenericDeclarationArray, MemberArray > MethodArray;
}  // namespace reflect
}  // namespace lang
}  // namespace java

using java::lang::ObjectArray;
using java::lang::reflect::AccessibleObjectArray;
using java::lang::reflect::AnnotatedElementArray;
using java::lang::reflect::GenericDeclarationArray;
using java::lang::reflect::MemberArray;
using java::lang::reflect::MethodArray;

struct default_init_tag;
class java::lang::Class_MethodArray
	: public virtual Object
{

public:
	typedef Object super;

private:
	int32_t length_ {  };
	MethodArray* methods {  };

protected:
	void ctor();

public: /* package */
	virtual void add(Method* arg0);
	virtual void addAll(MethodArray* arg0);
	virtual void addAll(Class_MethodArray* arg0);
	virtual void addAllIfNotPresent(Class_MethodArray* arg0);
	virtual void addIfNotPresent(Method* arg0);
	virtual void compactAndTrim();
	virtual Method* get(int32_t arg0);
	virtual MethodArray* getArray();
	virtual int32_t length();
	virtual void removeByNameAndSignature(Method* arg0);

	// Generated
	Class_MethodArray();
protected:
	Class_MethodArray(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

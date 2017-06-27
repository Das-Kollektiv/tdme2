// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/lang/fwd-tdme.h>
#include <java/lang/reflect/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::reflect::Type;
using java::lang::reflect::TypeVariable;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace lang {
namespace reflect {
typedef ::SubArray< ::java::lang::reflect::Type, ::java::lang::ObjectArray > TypeArray;
typedef ::SubArray< ::java::lang::reflect::TypeVariable, ::java::lang::ObjectArray, TypeArray > TypeVariableArray;
}  // namespace reflect
}  // namespace lang
}  // namespace java

using java::lang::ObjectArray;
using java::lang::reflect::TypeArray;
using java::lang::reflect::TypeVariableArray;

struct java::lang::reflect::GenericDeclaration
	: public virtual Object
{

	virtual TypeVariableArray* getTypeParameters() = 0;

	// Generated
	static ::java::lang::Class *class_();
};

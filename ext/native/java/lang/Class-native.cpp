// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Class.h>

using java::lang::Class;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
namespace reflect {
typedef ::SubArray< ::java::lang::reflect::GenericDeclaration, ::java::lang::ObjectArray > GenericDeclarationArray;
typedef ::SubArray< ::java::lang::reflect::Type, ::java::lang::ObjectArray > TypeArray;
typedef ::SubArray< ::java::lang::reflect::AnnotatedElement, ::java::lang::ObjectArray > AnnotatedElementArray;
}  // namespace reflect
typedef ::SubArray< ::java::lang::Class, ObjectArray, ::java::io::SerializableArray, ::java::lang::reflect::GenericDeclarationArray, ::java::lang::reflect::TypeArray, ::java::lang::reflect::AnnotatedElementArray > ClassArray;

namespace reflect {
typedef ::SubArray< ::java::lang::reflect::AccessibleObject, ::java::lang::ObjectArray, AnnotatedElementArray > AccessibleObjectArray;
typedef ::SubArray< ::java::lang::reflect::Member, ::java::lang::ObjectArray > MemberArray;
typedef ::SubArray< ::java::lang::reflect::Constructor, AccessibleObjectArray, GenericDeclarationArray, MemberArray > ConstructorArray;
typedef ::SubArray< ::java::lang::reflect::Field, AccessibleObjectArray, MemberArray > FieldArray;
typedef ::SubArray< ::java::lang::reflect::Method, AccessibleObjectArray, GenericDeclarationArray, MemberArray > MethodArray;
}  // namespace reflect
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);

/* private: bool Class::desiredAssertionStatus0(Class* arg0) */
/* private: Class* Class::forName0(String* arg0, bool arg1, ClassLoader* arg2) */
ClassLoader* Class::getClassLoader0()
{ /* native */
	unimplemented_(u"ClassLoader* Class::getClassLoader0()");
	return 0;
}

Class* Class::getComponentType()
{ /* native */
	unimplemented_(u"Class* Class::getComponentType()");
	return 0;
}

ConstantPool* Class::getConstantPool()
{ /* native */
	unimplemented_(u"ConstantPool* Class::getConstantPool()");
	return 0;
}

/* private: ClassArray* Class::getDeclaredClasses0() */
/* private: ConstructorArray* Class::getDeclaredConstructors0(bool arg0) */
/* private: FieldArray* Class::getDeclaredFields0(bool arg0) */
/* private: MethodArray* Class::getDeclaredMethods0(bool arg0) */
/* private: Class* Class::getDeclaringClass0() */
/* private: ObjectArray* Class::getEnclosingMethod0() */
/* private: String* Class::getGenericSignature() */
ClassArray* Class::getInterfaces()
{ /* native */
	unimplemented_(u"ClassArray* Class::getInterfaces()");
	return 0;
}

int32_t Class::getModifiers()
{ /* native */
	unimplemented_(u"int32_t Class::getModifiers()");
	return 0;
}

/* private: String* Class::getName0() */
Class* Class::getPrimitiveClass(String* arg0)
{ /* native */
	clinit();
	unimplemented_(u"Class* Class::getPrimitiveClass(String* arg0)");
	return 0;
}

/* private: ProtectionDomain* Class::getProtectionDomain0() */
/* private: int8_tArray* Class::getRawAnnotations() */
ObjectArray* Class::getSigners()
{ /* native */
	unimplemented_(u"ObjectArray* Class::getSigners()");
	return 0;
}

Class* Class::getSuperclass()
{ /* native */
	unimplemented_(u"Class* Class::getSuperclass()");
	return 0;
}

bool Class::isArray()
{ /* native */
	unimplemented_(u"bool Class::isArray()");
	return 0;
}

bool Class::isAssignableFrom(Class* arg0)
{ /* native */
	unimplemented_(u"bool Class::isAssignableFrom(Class* arg0)");
	return 0;
}

bool Class::isInstance(Object* arg0)
{ /* native */
	unimplemented_(u"bool Class::isInstance(Object* arg0)");
	return 0;
}

bool Class::isInterface()
{ /* native */
	unimplemented_(u"bool Class::isInterface()");
	return 0;
}

bool Class::isPrimitive()
{ /* native */
	unimplemented_(u"bool Class::isPrimitive()");
	return 0;
}

/* private: void Class::registerNatives() */
void Class::setProtectionDomain0(ProtectionDomain* arg0)
{ /* native */
	unimplemented_(u"void Class::setProtectionDomain0(ProtectionDomain* arg0)");
}

void Class::setSigners(ObjectArray* arg0)
{ /* native */
	unimplemented_(u"void Class::setSigners(ObjectArray* arg0)");
}


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

namespace annotation {
typedef ::SubArray< ::java::lang::annotation::Annotation, ::java::lang::ObjectArray > AnnotationArray;
}  // namespace annotation

namespace reflect {
typedef ::SubArray< ::java::lang::reflect::AccessibleObject, ::java::lang::ObjectArray, AnnotatedElementArray > AccessibleObjectArray;
typedef ::SubArray< ::java::lang::reflect::Member, ::java::lang::ObjectArray > MemberArray;
typedef ::SubArray< ::java::lang::reflect::Constructor, AccessibleObjectArray, GenericDeclarationArray, MemberArray > ConstructorArray;
typedef ::SubArray< ::java::lang::reflect::Field, AccessibleObjectArray, MemberArray > FieldArray;
typedef ::SubArray< ::java::lang::reflect::Method, AccessibleObjectArray, GenericDeclarationArray, MemberArray > MethodArray;
typedef ::SubArray< ::java::lang::reflect::TypeVariable, ::java::lang::ObjectArray, TypeArray > TypeVariableArray;
}  // namespace reflect
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::lang::Class::Class(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

constexpr int32_t java::lang::Class::ANNOTATION;
constexpr int32_t java::lang::Class::ENUM;
constexpr int32_t java::lang::Class::SYNTHETIC;
ProtectionDomain* java::lang::Class::allPermDomain;
bool java::lang::Class::initted;
ReflectionFactory* java::lang::Class::reflectionFactory;
ObjectStreamFieldArray* java::lang::Class::serialPersistentFields;
constexpr int64_t java::lang::Class::serialVersionUID;
bool java::lang::Class::useCaches;

/* private: void Class::ctor() */
/* private: void Class::addAll(Collection* arg0, FieldArray* arg1) */
/* private: String* Class::argumentTypesToString(ClassArray* arg0) */
/* private: bool Class::arrayContentsEq(ObjectArray* arg0, ObjectArray* arg1) */
Class* Class::asSubclass(Class* arg0)
{ /* stub */
	unimplemented_(u"Class* Class::asSubclass(Class* arg0)");
	return 0;
}

Object* Class::cast(Object* arg0)
{ /* stub */
	unimplemented_(u"Object* Class::cast(Object* arg0)");
	return 0;
}

/* private: void Class::checkInitted() */
/* private: void Class::checkMemberAccess(int32_t arg0, ClassLoader* arg1, bool arg2) */
/* private: void Class::checkPackageAccess(ClassLoader* arg0, bool arg1) */
/* private: void Class::clearCachesOnClassRedefinition() */
/* private: ConstructorArray* Class::copyConstructors(ConstructorArray* arg0) */
/* private: FieldArray* Class::copyFields(FieldArray* arg0) */
/* private: MethodArray* Class::copyMethods(MethodArray* arg0) */
bool Class::desiredAssertionStatus()
{ /* stub */
	unimplemented_(u"bool Class::desiredAssertionStatus()");
	return 0;
}

Map* Class::enumConstantDirectory()
{ /* stub */
	unimplemented_(u"Map* Class::enumConstantDirectory()");
	return 0;
}

Class* Class::forName(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Class* Class::forName(String* arg0)");
	return 0;
}

Class* Class::forName(String* arg0, bool arg1, ClassLoader* arg2)
{ /* stub */
	clinit();
	unimplemented_(u"Class* Class::forName(String* arg0, bool arg1, ClassLoader* arg2)");
	return 0;
}

Annotation* Class::getAnnotation(Class* arg0)
{ /* stub */
	unimplemented_(u"Annotation* Class::getAnnotation(Class* arg0)");
	return 0;
}

AnnotationType* Class::getAnnotationType()
{ /* stub */
return annotationType ; /* getter */
}

AnnotationArray* Class::getAnnotations()
{ /* stub */
}

String* Class::getCanonicalName()
{ /* stub */
	unimplemented_(u"String* Class::getCanonicalName()");
	return 0;
}

ClassLoader* Class::getClassLoader()
{ /* stub */
	unimplemented_(u"ClassLoader* Class::getClassLoader()");
	return 0;
}

ClassArray* Class::getClasses()
{ /* stub */
	unimplemented_(u"ClassArray* Class::getClasses()");
	return 0;
}

Constructor* Class::getConstructor(ClassArray* arg0)
{ /* stub */
	unimplemented_(u"Constructor* Class::getConstructor(ClassArray* arg0)");
	return 0;
}

/* private: Constructor* Class::getConstructor0(ClassArray* arg0, int32_t arg1) */
ConstructorArray* Class::getConstructors()
{ /* stub */
	unimplemented_(u"ConstructorArray* Class::getConstructors()");
	return 0;
}

AnnotationArray* Class::getDeclaredAnnotations()
{ /* stub */
}

ClassArray* Class::getDeclaredClasses()
{ /* stub */
	unimplemented_(u"ClassArray* Class::getDeclaredClasses()");
	return 0;
}

Constructor* Class::getDeclaredConstructor(ClassArray* arg0)
{ /* stub */
	unimplemented_(u"Constructor* Class::getDeclaredConstructor(ClassArray* arg0)");
	return 0;
}

ConstructorArray* Class::getDeclaredConstructors()
{ /* stub */
}

Field* Class::getDeclaredField(String* arg0)
{ /* stub */
	unimplemented_(u"Field* Class::getDeclaredField(String* arg0)");
	return 0;
}

FieldArray* Class::getDeclaredFields()
{ /* stub */
}

Method* Class::getDeclaredMethod(String* arg0, ClassArray* arg1)
{ /* stub */
	unimplemented_(u"Method* Class::getDeclaredMethod(String* arg0, ClassArray* arg1)");
	return 0;
}

MethodArray* Class::getDeclaredMethods()
{ /* stub */
}

Class* Class::getDeclaringClass()
{ /* stub */
	unimplemented_(u"Class* Class::getDeclaringClass()");
	return 0;
}

Class* Class::getEnclosingClass()
{ /* stub */
	unimplemented_(u"Class* Class::getEnclosingClass()");
	return 0;
}

Constructor* Class::getEnclosingConstructor()
{ /* stub */
	unimplemented_(u"Constructor* Class::getEnclosingConstructor()");
	return 0;
}

Method* Class::getEnclosingMethod()
{ /* stub */
	unimplemented_(u"Method* Class::getEnclosingMethod()");
	return 0;
}

/* private: Class_EnclosingMethodInfo* Class::getEnclosingMethodInfo() */
ObjectArray* Class::getEnumConstants()
{ /* stub */
return enumConstants ; /* getter */
}

ObjectArray* Class::getEnumConstantsShared()
{ /* stub */
	unimplemented_(u"ObjectArray* Class::getEnumConstantsShared()");
	return 0;
}

/* private: GenericsFactory* Class::getFactory() */
Field* Class::getField(String* arg0)
{ /* stub */
	unimplemented_(u"Field* Class::getField(String* arg0)");
	return 0;
}

/* private: Field* Class::getField0(String* arg0) */
FieldArray* Class::getFields()
{ /* stub */
	unimplemented_(u"FieldArray* Class::getFields()");
	return 0;
}

/* private: ClassRepository* Class::getGenericInfo() */
TypeArray* Class::getGenericInterfaces()
{ /* stub */
	unimplemented_(u"TypeArray* Class::getGenericInterfaces()");
	return 0;
}

Type* Class::getGenericSuperclass()
{ /* stub */
	unimplemented_(u"Type* Class::getGenericSuperclass()");
	return 0;
}

Method* Class::getMethod(String* arg0, ClassArray* arg1)
{ /* stub */
	unimplemented_(u"Method* Class::getMethod(String* arg0, ClassArray* arg1)");
	return 0;
}

/* private: Method* Class::getMethod0(String* arg0, ClassArray* arg1) */
MethodArray* Class::getMethods()
{ /* stub */
	unimplemented_(u"MethodArray* Class::getMethods()");
	return 0;
}

String* Class::getName()
{ /* stub */
return name ; /* getter */
}

Package* Class::getPackage()
{ /* stub */
	unimplemented_(u"Package* Class::getPackage()");
	return 0;
}

ProtectionDomain* Class::getProtectionDomain()
{ /* stub */
	unimplemented_(u"ProtectionDomain* Class::getProtectionDomain()");
	return 0;
}

/* private: ReflectionFactory* Class::getReflectionFactory() */
URL* Class::getResource(String* arg0)
{ /* stub */
	unimplemented_(u"URL* Class::getResource(String* arg0)");
	return 0;
}

InputStream* Class::getResourceAsStream(String* arg0)
{ /* stub */
	unimplemented_(u"InputStream* Class::getResourceAsStream(String* arg0)");
	return 0;
}

/* private: String* Class::getSimpleBinaryName() */
String* Class::getSimpleName()
{ /* stub */
	unimplemented_(u"String* Class::getSimpleName()");
	return 0;
}

TypeVariableArray* Class::getTypeParameters()
{ /* stub */
	unimplemented_(u"TypeVariableArray* Class::getTypeParameters()");
	return 0;
}

/* private: void Class::initAnnotationsIfNecessary() */
bool Class::isAnnotation()
{ /* stub */
	unimplemented_(u"bool Class::isAnnotation()");
	return 0;
}

bool Class::isAnnotationPresent(Class* arg0)
{ /* stub */
	unimplemented_(u"bool Class::isAnnotationPresent(Class* arg0)");
	return 0;
}

bool Class::isAnonymousClass()
{ /* stub */
	unimplemented_(u"bool Class::isAnonymousClass()");
	return 0;
}

/* private: bool Class::isAsciiDigit(char16_t arg0) */
bool Class::isEnum()
{ /* stub */
	unimplemented_(u"bool Class::isEnum()");
	return 0;
}

bool Class::isLocalClass()
{ /* stub */
	unimplemented_(u"bool Class::isLocalClass()");
	return 0;
}

/* private: bool Class::isLocalOrAnonymousClass() */
bool Class::isMemberClass()
{ /* stub */
	unimplemented_(u"bool Class::isMemberClass()");
	return 0;
}

bool Class::isSynthetic()
{ /* stub */
	unimplemented_(u"bool Class::isSynthetic()");
	return 0;
}

Object* Class::newInstance()
{ /* stub */
	unimplemented_(u"Object* Class::newInstance()");
	return 0;
}

/* private: Object* Class::newInstance0() */
/* private: ConstructorArray* Class::privateGetDeclaredConstructors(bool arg0) */
/* private: FieldArray* Class::privateGetDeclaredFields(bool arg0) */
/* private: MethodArray* Class::privateGetDeclaredMethods(bool arg0) */
/* private: FieldArray* Class::privateGetPublicFields(Set* arg0) */
/* private: MethodArray* Class::privateGetPublicMethods() */
/* private: String* Class::resolveName(String* arg0) */
/* private: Field* Class::searchFields(FieldArray* arg0, String* arg1) */
/* private: Method* Class::searchMethods(MethodArray* arg0, String* arg1, ClassArray* arg2) */
void Class::setAnnotationType(AnnotationType* arg0)
{ /* stub */
	this->annotationType = arg0; /* setter */
}

/* private: Class* Class::toClass(Type* arg0) */
String* Class::toString()
{ /* stub */
	unimplemented_(u"String* Class::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Class::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Class", 15);
    return c;
}

java::lang::Class* Class::getClass0()
{
	return class_();
}


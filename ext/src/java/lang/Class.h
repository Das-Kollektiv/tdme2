// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/annotation/fwd-tdme.h>
#include <java/lang/ref/fwd-tdme.h>
#include <java/lang/reflect/fwd-tdme.h>
#include <java/net/fwd-tdme.h>
#include <java/security/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <sun/reflect/fwd-tdme.h>
#include <sun/reflect/annotation/fwd-tdme.h>
#include <sun/reflect/generics/factory/fwd-tdme.h>
#include <sun/reflect/generics/repository/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>
#include <java/lang/reflect/GenericDeclaration.h>
#include <java/lang/reflect/Type.h>
#include <java/lang/reflect/AnnotatedElement.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::reflect::GenericDeclaration;
using java::lang::reflect::Type;
using java::lang::reflect::AnnotatedElement;
using java::io::InputStream;
using java::io::ObjectStreamField;
using java::lang::Class_EnclosingMethodInfo;
using java::lang::ClassLoader;
using java::lang::Comparable;
using java::lang::Package;
using java::lang::String;
using java::lang::annotation::Annotation;
using java::lang::ref::SoftReference;
using java::lang::reflect::AccessibleObject;
using java::lang::reflect::Constructor;
using java::lang::reflect::Field;
using java::lang::reflect::Member;
using java::lang::reflect::Method;
using java::lang::reflect::TypeVariable;
using java::net::URL;
using java::security::ProtectionDomain;
using java::util::Collection;
using java::util::Map;
using java::util::Set;
using sun::reflect::ConstantPool;
using sun::reflect::ReflectionFactory;
using sun::reflect::annotation::AnnotationType;
using sun::reflect::generics::factory::GenericsFactory;
using sun::reflect::generics::repository::ClassRepository;
using java::lang::Class;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
}  // namespace lang

namespace io {
typedef ::SubArray< ::java::io::ObjectStreamField, ::java::lang::ObjectArray, ::java::lang::ComparableArray > ObjectStreamFieldArray;
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

using java::io::ObjectStreamFieldArray;
using java::io::SerializableArray;
using java::lang::ClassArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::annotation::AnnotationArray;
using java::lang::reflect::AccessibleObjectArray;
using java::lang::reflect::AnnotatedElementArray;
using java::lang::reflect::ConstructorArray;
using java::lang::reflect::FieldArray;
using java::lang::reflect::GenericDeclarationArray;
using java::lang::reflect::MemberArray;
using java::lang::reflect::MethodArray;
using java::lang::reflect::TypeArray;
using java::lang::reflect::TypeVariableArray;

struct default_init_tag;
class java::lang::Class final
	: public virtual Object
	, public Serializable
	, public GenericDeclaration
	, public Type
	, public AnnotatedElement
{

public:
	typedef Object super;

private:
	static constexpr int32_t ANNOTATION { 8192 };
	static constexpr int32_t ENUM { 16384 };
	static constexpr int32_t SYNTHETIC { 4096 };
	static ProtectionDomain* allPermDomain;
	AnnotationType* annotationType {  };
	Map* annotations {  };
	std::atomic< Constructor* > cachedConstructor {  };
	std::atomic< int32_t > classRedefinedCount {  };
	Map* declaredAnnotations {  };
	std::atomic< SoftReference* > declaredConstructors {  };
	std::atomic< SoftReference* > declaredFields {  };
	std::atomic< SoftReference* > declaredMethods {  };
	std::atomic< SoftReference* > declaredPublicFields {  };
	std::atomic< SoftReference* > declaredPublicMethods {  };
	std::atomic< Map* > enumConstantDirectory_ {  };
	std::atomic< ObjectArray* > enumConstants {  };
	ClassRepository* genericInfo {  };
	static bool initted;
	std::atomic< int32_t > lastRedefinedCount {  };
	String* name {  };
	std::atomic< Class* > newInstanceCallerCache {  };
	std::atomic< SoftReference* > publicConstructors {  };
	std::atomic< SoftReference* > publicFields {  };
	std::atomic< SoftReference* > publicMethods {  };
	static ReflectionFactory* reflectionFactory;
	static ObjectStreamFieldArray* serialPersistentFields;
	static constexpr int64_t serialVersionUID { 3206093459760846163LL };
	static bool useCaches;

	/*void ctor(); (private) */
	/*static void addAll(Collection* arg0, FieldArray* arg1); (private) */
	/*static String* argumentTypesToString(ClassArray* arg0); (private) */
	/*static bool arrayContentsEq(ObjectArray* arg0, ObjectArray* arg1); (private) */

public:
	Class* asSubclass(Class* arg0);
	Object* cast(Object* arg0);
	/*static void checkInitted(); (private) */
	/*void checkMemberAccess(int32_t arg0, ClassLoader* arg1, bool arg2); (private) */
	/*void checkPackageAccess(ClassLoader* arg0, bool arg1); (private) */
	/*void clearCachesOnClassRedefinition(); (private) */
	/*static ConstructorArray* copyConstructors(ConstructorArray* arg0); (private) */
	/*static FieldArray* copyFields(FieldArray* arg0); (private) */
	/*static MethodArray* copyMethods(MethodArray* arg0); (private) */
	bool desiredAssertionStatus();
	/*static bool desiredAssertionStatus0(Class* arg0); (private) */

public: /* package */
	Map* enumConstantDirectory();

public:
	static Class* forName(String* arg0);
	static Class* forName(String* arg0, bool arg1, ClassLoader* arg2);
	/*static Class* forName0(String* arg0, bool arg1, ClassLoader* arg2); (private) */
	Annotation* getAnnotation(Class* arg0) override;

public: /* package */
	AnnotationType* getAnnotationType();

public:
	AnnotationArray* getAnnotations() override;
	String* getCanonicalName();
	ClassLoader* getClassLoader();

public: /* package */
	ClassLoader* getClassLoader0();

public:
	ClassArray* getClasses();
	Class* getComponentType();

public: /* package */
	ConstantPool* getConstantPool();

public:
	Constructor* getConstructor(ClassArray* arg0);
	/*Constructor* getConstructor0(ClassArray* arg0, int32_t arg1); (private) */
	ConstructorArray* getConstructors();
	AnnotationArray* getDeclaredAnnotations() override;
	ClassArray* getDeclaredClasses();
	/*ClassArray* getDeclaredClasses0(); (private) */
	Constructor* getDeclaredConstructor(ClassArray* arg0);
	ConstructorArray* getDeclaredConstructors();
	/*ConstructorArray* getDeclaredConstructors0(bool arg0); (private) */
	Field* getDeclaredField(String* arg0);
	FieldArray* getDeclaredFields();
	/*FieldArray* getDeclaredFields0(bool arg0); (private) */
	Method* getDeclaredMethod(String* arg0, ClassArray* arg1);
	MethodArray* getDeclaredMethods();
	/*MethodArray* getDeclaredMethods0(bool arg0); (private) */
	Class* getDeclaringClass();
	/*Class* getDeclaringClass0(); (private) */
	Class* getEnclosingClass();
	Constructor* getEnclosingConstructor();
	Method* getEnclosingMethod();
	/*ObjectArray* getEnclosingMethod0(); (private) */
	/*Class_EnclosingMethodInfo* getEnclosingMethodInfo(); (private) */
	ObjectArray* getEnumConstants();

public: /* package */
	ObjectArray* getEnumConstantsShared();
	/*GenericsFactory* getFactory(); (private) */

public:
	Field* getField(String* arg0);
	/*Field* getField0(String* arg0); (private) */
	FieldArray* getFields();
	/*ClassRepository* getGenericInfo(); (private) */
	TypeArray* getGenericInterfaces();
	/*String* getGenericSignature(); (private) */
	Type* getGenericSuperclass();
	ClassArray* getInterfaces();
	Method* getMethod(String* arg0, ClassArray* arg1);
	/*Method* getMethod0(String* arg0, ClassArray* arg1); (private) */
	MethodArray* getMethods();
	int32_t getModifiers();
	String* getName();
	/*String* getName0(); (private) */
	Package* getPackage();

public: /* package */
	static Class* getPrimitiveClass(String* arg0);

public:
	ProtectionDomain* getProtectionDomain();
	/*ProtectionDomain* getProtectionDomain0(); (private) */
	/*int8_tArray* getRawAnnotations(); (private) */
	/*static ReflectionFactory* getReflectionFactory(); (private) */
	URL* getResource(String* arg0);
	InputStream* getResourceAsStream(String* arg0);
	ObjectArray* getSigners();
	/*String* getSimpleBinaryName(); (private) */
	String* getSimpleName();
	Class* getSuperclass();
	TypeVariableArray* getTypeParameters() override;
	/*void initAnnotationsIfNecessary(); (private) */
	bool isAnnotation();
	bool isAnnotationPresent(Class* arg0) override;
	bool isAnonymousClass();
	bool isArray();
	/*static bool isAsciiDigit(char16_t arg0); (private) */
	bool isAssignableFrom(Class* arg0);
	bool isEnum();
	bool isInstance(Object* arg0);
	bool isInterface();
	bool isLocalClass();
	/*bool isLocalOrAnonymousClass(); (private) */
	bool isMemberClass();
	bool isPrimitive();
	bool isSynthetic();
	Object* newInstance();
	/*Object* newInstance0(); (private) */
	/*ConstructorArray* privateGetDeclaredConstructors(bool arg0); (private) */
	/*FieldArray* privateGetDeclaredFields(bool arg0); (private) */
	/*MethodArray* privateGetDeclaredMethods(bool arg0); (private) */
	/*FieldArray* privateGetPublicFields(Set* arg0); (private) */
	/*MethodArray* privateGetPublicMethods(); (private) */
	/*static void registerNatives(); (private) */
	/*String* resolveName(String* arg0); (private) */
	/*Field* searchFields(FieldArray* arg0, String* arg1); (private) */
	/*static Method* searchMethods(MethodArray* arg0, String* arg1, ClassArray* arg2); (private) */

public: /* package */
	void setAnnotationType(AnnotationType* arg0);
	void setProtectionDomain0(ProtectionDomain* arg0);
	void setSigners(ObjectArray* arg0);
	/*static Class* toClass(Type* arg0); (private) */

public:
	String* toString() override;

	// Generated
	Class();
protected:
	Class(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

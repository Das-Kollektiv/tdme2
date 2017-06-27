// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Class_MethodArray.h>

using java::lang::Class_MethodArray;
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

extern void unimplemented_(const char16_t* name);
java::lang::Class_MethodArray::Class_MethodArray(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Class_MethodArray::Class_MethodArray()
	: Class_MethodArray(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}


void Class_MethodArray::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Class_MethodArray::ctor()");
}

void Class_MethodArray::add(Method* arg0)
{ /* stub */
	unimplemented_(u"void Class_MethodArray::add(Method* arg0)");
}

void Class_MethodArray::addAll(MethodArray* arg0)
{ /* stub */
	unimplemented_(u"void Class_MethodArray::addAll(MethodArray* arg0)");
}

void Class_MethodArray::addAll(Class_MethodArray* arg0)
{ /* stub */
	unimplemented_(u"void Class_MethodArray::addAll(Class_MethodArray* arg0)");
}

void Class_MethodArray::addAllIfNotPresent(Class_MethodArray* arg0)
{ /* stub */
	unimplemented_(u"void Class_MethodArray::addAllIfNotPresent(Class_MethodArray* arg0)");
}

void Class_MethodArray::addIfNotPresent(Method* arg0)
{ /* stub */
	unimplemented_(u"void Class_MethodArray::addIfNotPresent(Method* arg0)");
}

void Class_MethodArray::compactAndTrim()
{ /* stub */
	unimplemented_(u"void Class_MethodArray::compactAndTrim()");
}

Method* Class_MethodArray::get(int32_t arg0)
{ /* stub */
	unimplemented_(u"Method* Class_MethodArray::get(int32_t arg0)");
	return 0;
}

MethodArray* Class_MethodArray::getArray()
{ /* stub */
	unimplemented_(u"MethodArray* Class_MethodArray::getArray()");
	return 0;
}

int32_t Class_MethodArray::length()
{ /* stub */
	unimplemented_(u"int32_t Class_MethodArray::length()");
	return 0;
}

void Class_MethodArray::removeByNameAndSignature(Method* arg0)
{ /* stub */
	unimplemented_(u"void Class_MethodArray::removeByNameAndSignature(Method* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Class_MethodArray::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Class.MethodArray", 27);
    return c;
}

java::lang::Class* Class_MethodArray::getClass0()
{
	return class_();
}


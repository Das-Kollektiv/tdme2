// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/ClassLoader.h>

using java::lang::ClassLoader;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;

namespace reflect {
typedef ::SubArray< ::java::lang::reflect::AnnotatedElement, ::java::lang::ObjectArray > AnnotatedElementArray;
}  // namespace reflect
typedef ::SubArray< ::java::lang::Package, ObjectArray, ::java::lang::reflect::AnnotatedElementArray > PackageArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang

namespace security {
namespace cert {
typedef ::SubArray< ::java::security::cert::Certificate, ::java::lang::ObjectArray, ::java::io::SerializableArray > CertificateArray;
}  // namespace cert
}  // namespace security
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::lang::ClassLoader::ClassLoader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::ClassLoader::ClassLoader()
	: ClassLoader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::ClassLoader::ClassLoader(ClassLoader* arg0)
	: ClassLoader(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

Vector* java::lang::ClassLoader::loadedLibraryNames;
Stack* java::lang::ClassLoader::nativeLibraryContext;
ClassLoader* java::lang::ClassLoader::scl;
bool java::lang::ClassLoader::sclSet;
StringArray* java::lang::ClassLoader::sys_paths;
Vector* java::lang::ClassLoader::systemNativeLibraries;
StringArray* java::lang::ClassLoader::usr_paths;

void ClassLoader::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ClassLoader::ctor()");
}

void ClassLoader::ctor(ClassLoader* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ClassLoader::ctor(ClassLoader* arg0)");
}

/* private: void ClassLoader::ctor(Void* arg0, ClassLoader* arg1) */
void ClassLoader::addClass(Class* arg0)
{ /* stub */
	unimplemented_(u"void ClassLoader::addClass(Class* arg0)");
}

/* private: void ClassLoader::checkCerts(String* arg0, CodeSource* arg1) */
/* private: Void* ClassLoader::checkCreateClassLoader() */
/* private: bool ClassLoader::checkName(String* arg0) */
/* private: void ClassLoader::checkPackageAccess(Class* arg0, ProtectionDomain* arg1) */
void ClassLoader::clearAssertionStatus()
{ /* stub */
	unimplemented_(u"void ClassLoader::clearAssertionStatus()");
}

/* private: bool ClassLoader::compareCerts(CertificateArray* arg0, CertificateArray* arg1) */
Class* ClassLoader::defineClass(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::defineClass(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

Class* ClassLoader::defineClass(String* arg0, ByteBuffer* arg1, ProtectionDomain* arg2)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::defineClass(String* arg0, ByteBuffer* arg1, ProtectionDomain* arg2)");
	return 0;
}

Class* ClassLoader::defineClass(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::defineClass(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3)");
	return 0;
}

Class* ClassLoader::defineClass(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::defineClass(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4)");
	return 0;
}

/* private: Class* ClassLoader::defineClass0(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4) */
/* private: Class* ClassLoader::defineClassCond(String* arg0, ByteBuffer* arg1, ProtectionDomain* arg2, bool arg3) */
/* private: Class* ClassLoader::defineClassCond(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4, bool arg5) */
/* private: String* ClassLoader::defineClassSourceLocation(ProtectionDomain* arg0) */
Package* ClassLoader::definePackage(String* arg0, String* arg1, String* arg2, String* arg3, String* arg4, String* arg5, String* arg6, URL* arg7)
{ /* stub */
	unimplemented_(u"Package* ClassLoader::definePackage(String* arg0, String* arg1, String* arg2, String* arg3, String* arg4, String* arg5, String* arg6, URL* arg7)");
	return 0;
}

/* private: Class* ClassLoader::defineTransformedClass(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4, ClassFormatError* arg5, String* arg6, bool arg7) */
bool ClassLoader::desiredAssertionStatus(String* arg0)
{ /* stub */
	unimplemented_(u"bool ClassLoader::desiredAssertionStatus(String* arg0)");
	return 0;
}

/* private: Class* ClassLoader::findBootstrapClassOrNull(String* arg0) */
Class* ClassLoader::findClass(String* arg0)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::findClass(String* arg0)");
	return 0;
}

String* ClassLoader::findLibrary(String* arg0)
{ /* stub */
	unimplemented_(u"String* ClassLoader::findLibrary(String* arg0)");
	return 0;
}

Class* ClassLoader::findLoadedClass(String* arg0)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::findLoadedClass(String* arg0)");
	return 0;
}

int64_t ClassLoader::findNative(ClassLoader* arg0, String* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"int64_t ClassLoader::findNative(ClassLoader* arg0, String* arg1)");
	return 0;
}

URL* ClassLoader::findResource(String* arg0)
{ /* stub */
	unimplemented_(u"URL* ClassLoader::findResource(String* arg0)");
	return 0;
}

Enumeration* ClassLoader::findResources(String* arg0)
{ /* stub */
	unimplemented_(u"Enumeration* ClassLoader::findResources(String* arg0)");
	return 0;
}

Class* ClassLoader::findSystemClass(String* arg0)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::findSystemClass(String* arg0)");
	return 0;
}

URLClassPath* ClassLoader::getBootstrapClassPath()
{ /* stub */
	clinit();
	unimplemented_(u"URLClassPath* ClassLoader::getBootstrapClassPath()");
	return 0;
}

/* private: URL* ClassLoader::getBootstrapResource(String* arg0) */
/* private: Enumeration* ClassLoader::getBootstrapResources(String* arg0) */
ClassLoader* ClassLoader::getCallerClassLoader()
{ /* stub */
	clinit();
	unimplemented_(u"ClassLoader* ClassLoader::getCallerClassLoader()");
	return 0;
}

/* private: ProtectionDomain* ClassLoader::getDefaultDomain() */
Package* ClassLoader::getPackage(String* arg0)
{ /* stub */
	unimplemented_(u"Package* ClassLoader::getPackage(String* arg0)");
	return 0;
}

PackageArray* ClassLoader::getPackages()
{ /* stub */
}

ClassLoader* ClassLoader::getParent()
{ /* stub */
return parent ; /* getter */
}

URL* ClassLoader::getResource(String* arg0)
{ /* stub */
	unimplemented_(u"URL* ClassLoader::getResource(String* arg0)");
	return 0;
}

InputStream* ClassLoader::getResourceAsStream(String* arg0)
{ /* stub */
	unimplemented_(u"InputStream* ClassLoader::getResourceAsStream(String* arg0)");
	return 0;
}

Enumeration* ClassLoader::getResources(String* arg0)
{ /* stub */
	unimplemented_(u"Enumeration* ClassLoader::getResources(String* arg0)");
	return 0;
}

ClassLoader* ClassLoader::getSystemClassLoader()
{ /* stub */
	clinit();
	unimplemented_(u"ClassLoader* ClassLoader::getSystemClassLoader()");
	return 0;
}

URL* ClassLoader::getSystemResource(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"URL* ClassLoader::getSystemResource(String* arg0)");
	return 0;
}

InputStream* ClassLoader::getSystemResourceAsStream(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"InputStream* ClassLoader::getSystemResourceAsStream(String* arg0)");
	return 0;
}

Enumeration* ClassLoader::getSystemResources(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Enumeration* ClassLoader::getSystemResources(String* arg0)");
	return 0;
}

/* private: void ClassLoader::initSystemClassLoader() */
/* private: void ClassLoader::initializeJavaAssertionMaps() */
/* private: StringArray* ClassLoader::initializePath(String* arg0) */
bool ClassLoader::isAncestor(ClassLoader* arg0)
{ /* stub */
	unimplemented_(u"bool ClassLoader::isAncestor(ClassLoader* arg0)");
	return 0;
}

Class* ClassLoader::loadClass(String* arg0)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::loadClass(String* arg0)");
	return 0;
}

Class* ClassLoader::loadClass(String* arg0, bool arg1)
{ /* stub */
	unimplemented_(u"Class* ClassLoader::loadClass(String* arg0, bool arg1)");
	return 0;
}

/* private: Class* ClassLoader::loadClassInternal(String* arg0) */
void ClassLoader::loadLibrary(Class* arg0, String* arg1, bool arg2)
{ /* stub */
	clinit();
	unimplemented_(u"void ClassLoader::loadLibrary(Class* arg0, String* arg1, bool arg2)");
}

/* private: bool ClassLoader::loadLibrary0(Class* arg0, File* arg1) */
/* private: void ClassLoader::postDefineClass(Class* arg0, ProtectionDomain* arg1) */
/* private: ProtectionDomain* ClassLoader::preDefineClass(String* arg0, ProtectionDomain* arg1) */
void ClassLoader::resolveClass(Class* arg0)
{ /* stub */
	unimplemented_(u"void ClassLoader::resolveClass(Class* arg0)");
}

void ClassLoader::setClassAssertionStatus(String* arg0, bool arg1)
{ /* stub */
}

void ClassLoader::setDefaultAssertionStatus(bool arg0)
{ /* stub */
	this->defaultAssertionStatus = arg0; /* setter */
}

void ClassLoader::setPackageAssertionStatus(String* arg0, bool arg1)
{ /* stub */
}

void ClassLoader::setSigners(Class* arg0, ObjectArray* arg1)
{ /* stub */
	unimplemented_(u"void ClassLoader::setSigners(Class* arg0, ObjectArray* arg1)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ClassLoader::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.ClassLoader", 21);
    return c;
}

java::lang::Class* ClassLoader::getClass0()
{
	return class_();
}


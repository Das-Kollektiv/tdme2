// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/reflect/fwd-tdme.h>
#include <java/net/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/security/fwd-tdme.h>
#include <java/security/cert/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <sun/misc/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::File;
using java::io::InputStream;
using java::io::Serializable;
using java::lang::AssertionStatusDirectives;
using java::lang::CharSequence;
using java::lang::Class;
using java::lang::ClassFormatError;
using java::lang::Comparable;
using java::lang::Package;
using java::lang::String;
using java::lang::Void;
using java::lang::reflect::AnnotatedElement;
using java::net::URL;
using java::nio::ByteBuffer;
using java::security::CodeSource;
using java::security::ProtectionDomain;
using java::security::cert::Certificate;
using java::util::Enumeration;
using java::util::HashMap;
using java::util::Hashtable;
using java::util::Map;
using java::util::Set;
using java::util::Stack;
using java::util::Vector;
using sun::misc::URLClassPath;

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

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::PackageArray;
using java::lang::StringArray;
using java::lang::reflect::AnnotatedElementArray;
using java::security::cert::CertificateArray;

struct default_init_tag;
class java::lang::ClassLoader
	: public virtual Object
{

public:
	typedef Object super;

public: /* package */
	Map* classAssertionStatus {  };

private:
	Vector* classes {  };
	bool defaultAssertionStatus {  };
	ProtectionDomain* defaultDomain {  };
	Set* domains {  };
	static Vector* loadedLibraryNames;
	Vector* nativeLibraries {  };
	static Stack* nativeLibraryContext;

public: /* package */
	CertificateArray* nocerts {  };

private:
	Hashtable* package2certs {  };
	Map* packageAssertionStatus {  };
	HashMap* packages {  };
	ClassLoader* parent {  };
	static ClassLoader* scl;
	static bool sclSet;
	static StringArray* sys_paths;
	static Vector* systemNativeLibraries;
	static StringArray* usr_paths;

protected:
	void ctor();
	void ctor(ClassLoader* arg0);
	/*void ctor(Void* arg0, ClassLoader* arg1); (private) */

public: /* package */
	virtual void addClass(Class* arg0);
	/*void checkCerts(String* arg0, CodeSource* arg1); (private) */
	/*static Void* checkCreateClassLoader(); (private) */
	/*bool checkName(String* arg0); (private) */
	/*void checkPackageAccess(Class* arg0, ProtectionDomain* arg1); (private) */

public:
	virtual void clearAssertionStatus();
	/*bool compareCerts(CertificateArray* arg0, CertificateArray* arg1); (private) */

public: /* protected */
	Class* defineClass(int8_tArray* arg0, int32_t arg1, int32_t arg2);
	Class* defineClass(String* arg0, ByteBuffer* arg1, ProtectionDomain* arg2);
	Class* defineClass(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3);
	Class* defineClass(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4);
	/*Class* defineClass0(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4); (private) */
	/*Class* defineClass0(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4, bool arg5); (private) */
	/*Class* defineClass1(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4, String* arg5, bool arg6); (private) */
	/*Class* defineClass2(String* arg0, ByteBuffer* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4, String* arg5, bool arg6); (private) */
	/*Class* defineClassCond(String* arg0, ByteBuffer* arg1, ProtectionDomain* arg2, bool arg3); (private) */
	/*Class* defineClassCond(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4, bool arg5); (private) */
	/*String* defineClassSourceLocation(ProtectionDomain* arg0); (private) */
	virtual Package* definePackage(String* arg0, String* arg1, String* arg2, String* arg3, String* arg4, String* arg5, String* arg6, URL* arg7);
	/*Class* defineTransformedClass(String* arg0, int8_tArray* arg1, int32_t arg2, int32_t arg3, ProtectionDomain* arg4, ClassFormatError* arg5, String* arg6, bool arg7); (private) */

public: /* package */
	virtual bool desiredAssertionStatus(String* arg0);
	/*Class* findBootstrapClass(String* arg0); (private) */
	/*Class* findBootstrapClassOrNull(String* arg0); (private) */

public: /* protected */
	virtual Class* findClass(String* arg0);
	virtual String* findLibrary(String* arg0);
	Class* findLoadedClass(String* arg0);
	/*Class* findLoadedClass0(String* arg0); (private) */

public: /* package */
	static int64_t findNative(ClassLoader* arg0, String* arg1);

public: /* protected */
	virtual URL* findResource(String* arg0);
	virtual Enumeration* findResources(String* arg0);
	Class* findSystemClass(String* arg0);

public: /* package */
	static URLClassPath* getBootstrapClassPath();
	/*static URL* getBootstrapResource(String* arg0); (private) */
	/*static Enumeration* getBootstrapResources(String* arg0); (private) */
	static ClassLoader* getCallerClassLoader();
	/*ProtectionDomain* getDefaultDomain(); (private) */

public: /* protected */
	virtual Package* getPackage(String* arg0);
	virtual PackageArray* getPackages();

public:
	ClassLoader* getParent();
	virtual URL* getResource(String* arg0);
	virtual InputStream* getResourceAsStream(String* arg0);
	virtual Enumeration* getResources(String* arg0);
	static ClassLoader* getSystemClassLoader();
	static URL* getSystemResource(String* arg0);
	static InputStream* getSystemResourceAsStream(String* arg0);
	static Enumeration* getSystemResources(String* arg0);
	/*static void initSystemClassLoader(); (private) */
	/*void initializeJavaAssertionMaps(); (private) */
	/*static StringArray* initializePath(String* arg0); (private) */

public: /* package */
	virtual bool isAncestor(ClassLoader* arg0);

public:
	virtual Class* loadClass(String* arg0);

public: /* protected */
	virtual Class* loadClass(String* arg0, bool arg1);
	/*Class* loadClassInternal(String* arg0); (private) */

public: /* package */
	static void loadLibrary(Class* arg0, String* arg1, bool arg2);
	/*static bool loadLibrary0(Class* arg0, File* arg1); (private) */
	/*void postDefineClass(Class* arg0, ProtectionDomain* arg1); (private) */
	/*ProtectionDomain* preDefineClass(String* arg0, ProtectionDomain* arg1); (private) */
	/*static void registerNatives(); (private) */

public: /* protected */
	void resolveClass(Class* arg0);
	/*void resolveClass0(Class* arg0); (private) */
	/*static AssertionStatusDirectives* retrieveDirectives(); (private) */

public:
	virtual void setClassAssertionStatus(String* arg0, bool arg1);
	virtual void setDefaultAssertionStatus(bool arg0);
	virtual void setPackageAssertionStatus(String* arg0, bool arg1);

public: /* protected */
	void setSigners(Class* arg0, ObjectArray* arg1);

	// Generated
	ClassLoader();
	ClassLoader(ClassLoader* arg0);
protected:
	ClassLoader(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

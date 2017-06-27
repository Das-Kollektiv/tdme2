// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/common/util/locks/fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/reflect/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <jogamp/opengl/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::common::util::locks::RecursiveThreadGroupLock;
using com::jogamp::nativewindow::AbstractGraphicsDevice;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Class;
using java::lang::ClassLoader;
using java::lang::Comparable;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::reflect::AnnotatedElement;
using java::lang::reflect::Constructor;
using java::lang::reflect::GenericDeclaration;
using java::lang::reflect::Type;
using java::util::HashMap;
using jogamp::opengl::GLDrawableFactoryImpl;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;

namespace reflect {
typedef ::SubArray< ::java::lang::reflect::GenericDeclaration, ::java::lang::ObjectArray > GenericDeclarationArray;
typedef ::SubArray< ::java::lang::reflect::Type, ::java::lang::ObjectArray > TypeArray;
typedef ::SubArray< ::java::lang::reflect::AnnotatedElement, ::java::lang::ObjectArray > AnnotatedElementArray;
}  // namespace reflect
typedef ::SubArray< ::java::lang::Class, ObjectArray, ::java::io::SerializableArray, ::java::lang::reflect::GenericDeclarationArray, ::java::lang::reflect::TypeArray, ::java::lang::reflect::AnnotatedElementArray > ClassArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ClassArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;
using java::lang::reflect::AnnotatedElementArray;
using java::lang::reflect::GenericDeclarationArray;
using java::lang::reflect::TypeArray;

struct default_init_tag;
class com::jogamp::opengl::GLProfile
	: public virtual Object
{

public:
	typedef Object super;
	static bool DEBUG;
	static String* GL2;
	static String* GL2ES1;
	static String* GL2ES2;
	static String* GL2GL3;
	static String* GL3;
	static String* GL3bc;
	static String* GL4;
	static String* GL4ES3;
	static String* GL4bc;

private:
	static String* GL4bcImplClassName;
	static String* GL4bcProcClassName;

public:
	static String* GLES1;

private:
	static String* GLES1ImplClassName;
	static String* GLES1ProcClassName;

public:
	static String* GLES2;
	static String* GLES3;

private:
	static String* GLES3ImplClassName;
	static String* GLES3ProcClassName;
	static String* GL_DEFAULT;
	static String* GL_GL;

public:
	static StringArray* GL_PROFILE_LIST_ALL;
	static StringArray* GL_PROFILE_LIST_MAX;
	static StringArray* GL_PROFILE_LIST_MAX_FIXEDFUNC;
	static StringArray* GL_PROFILE_LIST_MAX_PROGSHADER;
	static StringArray* GL_PROFILE_LIST_MAX_PROGSHADER_CORE;
	static StringArray* GL_PROFILE_LIST_MIN;
	static StringArray* GL_PROFILE_LIST_MIN_DESKTOP;

private:
	static Constructor* ctorGL234Impl;
	static Constructor* ctorGL234ProcAddr;
	static ClassArray* ctorGLArgs;
	static Constructor* ctorGLES1Impl;
	static Constructor* ctorGLES1ProcAddr;
	static Constructor* ctorGLES3Impl;
	static Constructor* ctorGLES3ProcAddr;
	static ClassArray* ctorProcArgs;
	static AbstractGraphicsDevice* defaultDevice;
	static GLDrawableFactoryImpl* desktopFactory;
	static HashMap* deviceConn2ProfileMap;

public:
	static bool disableOpenGLARBContext;
	static bool disableOpenGLCore;
	static bool disableOpenGLDesktop;
	static bool disableOpenGLES;
	static bool disableSurfacelessContext;

private:
	static GLDrawableFactoryImpl* eglFactory;

public:
	static bool enableANGLE;

private:
	static bool hasDesktopGLFactory;
	static bool hasEGLFactory;
	static bool hasGL234Impl;
	static bool hasGL234OnEGLImpl;
	static bool hasGLES1Impl;
	static bool hasGLES3Impl;
	static RecursiveThreadGroupLock* initLock;
	static bool initialized;
	static bool isAWTAvailable_;
	bool isCustom {  };
	bool isHardwareRasterizer_ {  };
	String* profile {  };
	GLProfile* profileImpl {  };

	/*void ctor(String* arg0, GLProfile* arg1, bool arg2, bool arg3); (private) */
	/*static String* array2String(StringArray* arg0); (private) */
	/*static String* computeProfileImpl(AbstractGraphicsDevice* arg0, String* arg1, bool arg2, bool arg3, boolArray* arg4); (private) */
	/*static HashMap* computeProfileMap(AbstractGraphicsDevice* arg0, bool arg1, bool arg2); (private) */

public:
	static GLProfile* createCustomGLProfile(String* arg0, GLProfile* arg1);
	/*static StringBuilder* doIndent(StringBuilder* arg0, String* arg1, int32_t arg2); (private) */
	/*static void dumpGLInfo(GLDrawableFactoryImpl* arg0, AbstractGraphicsDevice* arg1); (private) */
	bool equals(Object* arg0) override;
	static GLProfile* get(String* arg0);
	static GLProfile* get(AbstractGraphicsDevice* arg0, String* arg1);
	static GLProfile* get(StringArray* arg0, bool arg1);
	static GLProfile* get(AbstractGraphicsDevice* arg0, StringArray* arg1, bool arg2);
	/*static Constructor* getCtor(String* arg0, bool arg1, ClassLoader* arg2); (private) */
	static GLProfile* getDefault();
	static GLProfile* getDefault(AbstractGraphicsDevice* arg0);
	static AbstractGraphicsDevice* getDefaultDevice();
	static GLProfile* getGL2ES1();
	static GLProfile* getGL2ES1(AbstractGraphicsDevice* arg0);
	static GLProfile* getGL2ES2();
	static GLProfile* getGL2ES2(AbstractGraphicsDevice* arg0);
	static GLProfile* getGL2GL3();
	static GLProfile* getGL2GL3(AbstractGraphicsDevice* arg0);
	static GLProfile* getGL4ES3();
	static GLProfile* getGL4ES3(AbstractGraphicsDevice* arg0);
	static String* getGLArrayName(int32_t arg0);
	Constructor* getGLCtor(bool arg0);
	/*static Constructor* getGLCtor(String* arg0, bool arg1); (private) */
	String* getGLImplBaseClassName();
	/*static String* getGLImplBaseClassName(String* arg0); (private) */
	static String* getGLTypeName(int32_t arg0);
	GLProfile* getImpl();
	String* getImplName();
	static GLProfile* getMaxFixedFunc(bool arg0);
	static GLProfile* getMaxFixedFunc(AbstractGraphicsDevice* arg0, bool arg1);
	static GLProfile* getMaxProgrammable(bool arg0);
	static GLProfile* getMaxProgrammable(AbstractGraphicsDevice* arg0, bool arg1);
	static GLProfile* getMaxProgrammableCore(bool arg0);
	static GLProfile* getMaxProgrammableCore(AbstractGraphicsDevice* arg0, bool arg1);
	static GLProfile* getMaximum(bool arg0);
	static GLProfile* getMaximum(AbstractGraphicsDevice* arg0, bool arg1);
	static GLProfile* getMinimum(bool arg0);
	static GLProfile* getMinimum(AbstractGraphicsDevice* arg0, bool arg1);
	String* getName();
	/*static HashMap* getProfileMap(AbstractGraphicsDevice* arg0, bool arg1); (private) */
	static String* glAvailabilityToString();
	static String* glAvailabilityToString(AbstractGraphicsDevice* arg0);
	static StringBuilder* glAvailabilityToString(AbstractGraphicsDevice* arg0, StringBuilder* arg1);
	static StringBuilder* glAvailabilityToString(AbstractGraphicsDevice* arg0, StringBuilder* arg1, String* arg2, int32_t arg3);
	/*static void glAvailabilityToString(AbstractGraphicsDevice* arg0, StringBuilder* arg1, int32_t arg2, int32_t arg3); (private) */
	bool hasGLSL();
	int32_t hashCode() override;
	/*static void initGLCtorImpl(); (private) */
	static void initProfiles(AbstractGraphicsDevice* arg0);
	/*static void initProfilesForDefaultDevices(); (private) */
	/*static bool initProfilesForDevice(AbstractGraphicsDevice* arg0); (private) */
	/*static bool initProfilesForDeviceCritical(AbstractGraphicsDevice* arg0); (private) */
	static void initSingleton();
	static bool isAWTAvailable();
	static bool isAnyAvailable();
	static bool isAvailable(String* arg0);
	static bool isAvailable(AbstractGraphicsDevice* arg0, String* arg1);
	/*static bool isAvailableImpl(HashMap* arg0, String* arg1); (private) */
	bool isGL2();
	bool isGL2ES1();
	bool isGL2ES2();
	bool isGL2ES3();
	bool isGL2GL3();
	bool isGL3();
	bool isGL3ES3();
	bool isGL3bc();
	bool isGL4();
	bool isGL4ES3();
	bool isGL4bc();
	bool isGLES();
	bool isGLES1();
	bool isGLES2();
	bool isGLES3();
	bool isHardwareRasterizer();
	static bool isInitialized();
	virtual bool isValidArrayDataType(int32_t arg0, int32_t arg1, int32_t arg2, bool arg3, bool arg4);
	virtual bool isValidDataType(int32_t arg0, bool arg1);
	/*static void setProfileMap(AbstractGraphicsDevice* arg0, HashMap* arg1); (private) */
	static void shutdown();
	String* toString() override;
	bool usesNativeGLES();
	static bool usesNativeGLES(String* arg0);
	bool usesNativeGLES1();
	static bool usesNativeGLES1(String* arg0);
	bool usesNativeGLES2();
	static bool usesNativeGLES2(String* arg0);
	bool usesNativeGLES3();
	static bool usesNativeGLES3(String* arg0);
	void verifyEquality(GLProfile* arg0);

	// Generated
	GLProfile();
protected:
	GLProfile(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

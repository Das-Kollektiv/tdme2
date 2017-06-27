// Generated from /tdme/lib/jogl-all.jar
#include <com/jogamp/opengl/GLProfile.h>

using com::jogamp::opengl::GLProfile;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);
com::jogamp::opengl::GLProfile::GLProfile(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

bool com::jogamp::opengl::GLProfile::DEBUG;
String* com::jogamp::opengl::GLProfile::GL2;
String* com::jogamp::opengl::GLProfile::GL2ES1;
String* com::jogamp::opengl::GLProfile::GL2ES2;
String* com::jogamp::opengl::GLProfile::GL2GL3;
String* com::jogamp::opengl::GLProfile::GL3;
String* com::jogamp::opengl::GLProfile::GL3bc;
String* com::jogamp::opengl::GLProfile::GL4;
String* com::jogamp::opengl::GLProfile::GL4ES3;
String* com::jogamp::opengl::GLProfile::GL4bc;
String* com::jogamp::opengl::GLProfile::GL4bcImplClassName;
String* com::jogamp::opengl::GLProfile::GL4bcProcClassName;
String* com::jogamp::opengl::GLProfile::GLES1;
String* com::jogamp::opengl::GLProfile::GLES1ImplClassName;
String* com::jogamp::opengl::GLProfile::GLES1ProcClassName;
String* com::jogamp::opengl::GLProfile::GLES2;
String* com::jogamp::opengl::GLProfile::GLES3;
String* com::jogamp::opengl::GLProfile::GLES3ImplClassName;
String* com::jogamp::opengl::GLProfile::GLES3ProcClassName;
String* com::jogamp::opengl::GLProfile::GL_DEFAULT;
String* com::jogamp::opengl::GLProfile::GL_GL;
StringArray* com::jogamp::opengl::GLProfile::GL_PROFILE_LIST_ALL;
StringArray* com::jogamp::opengl::GLProfile::GL_PROFILE_LIST_MAX;
StringArray* com::jogamp::opengl::GLProfile::GL_PROFILE_LIST_MAX_FIXEDFUNC;
StringArray* com::jogamp::opengl::GLProfile::GL_PROFILE_LIST_MAX_PROGSHADER;
StringArray* com::jogamp::opengl::GLProfile::GL_PROFILE_LIST_MAX_PROGSHADER_CORE;
StringArray* com::jogamp::opengl::GLProfile::GL_PROFILE_LIST_MIN;
StringArray* com::jogamp::opengl::GLProfile::GL_PROFILE_LIST_MIN_DESKTOP;
Constructor* com::jogamp::opengl::GLProfile::ctorGL234Impl;
Constructor* com::jogamp::opengl::GLProfile::ctorGL234ProcAddr;
ClassArray* com::jogamp::opengl::GLProfile::ctorGLArgs;
Constructor* com::jogamp::opengl::GLProfile::ctorGLES1Impl;
Constructor* com::jogamp::opengl::GLProfile::ctorGLES1ProcAddr;
Constructor* com::jogamp::opengl::GLProfile::ctorGLES3Impl;
Constructor* com::jogamp::opengl::GLProfile::ctorGLES3ProcAddr;
ClassArray* com::jogamp::opengl::GLProfile::ctorProcArgs;
AbstractGraphicsDevice* com::jogamp::opengl::GLProfile::defaultDevice;
GLDrawableFactoryImpl* com::jogamp::opengl::GLProfile::desktopFactory;
HashMap* com::jogamp::opengl::GLProfile::deviceConn2ProfileMap;
bool com::jogamp::opengl::GLProfile::disableOpenGLARBContext;
bool com::jogamp::opengl::GLProfile::disableOpenGLCore;
bool com::jogamp::opengl::GLProfile::disableOpenGLDesktop;
bool com::jogamp::opengl::GLProfile::disableOpenGLES;
bool com::jogamp::opengl::GLProfile::disableSurfacelessContext;
GLDrawableFactoryImpl* com::jogamp::opengl::GLProfile::eglFactory;
bool com::jogamp::opengl::GLProfile::enableANGLE;
bool com::jogamp::opengl::GLProfile::hasDesktopGLFactory;
bool com::jogamp::opengl::GLProfile::hasEGLFactory;
bool com::jogamp::opengl::GLProfile::hasGL234Impl;
bool com::jogamp::opengl::GLProfile::hasGL234OnEGLImpl;
bool com::jogamp::opengl::GLProfile::hasGLES1Impl;
bool com::jogamp::opengl::GLProfile::hasGLES3Impl;
RecursiveThreadGroupLock* com::jogamp::opengl::GLProfile::initLock;
bool com::jogamp::opengl::GLProfile::initialized;
bool com::jogamp::opengl::GLProfile::isAWTAvailable_;

/* private: void GLProfile::ctor(String* arg0, GLProfile* arg1, bool arg2, bool arg3) */
/* private: String* GLProfile::array2String(StringArray* arg0) */
/* private: String* GLProfile::computeProfileImpl(AbstractGraphicsDevice* arg0, String* arg1, bool arg2, bool arg3, boolArray* arg4) */
/* private: HashMap* GLProfile::computeProfileMap(AbstractGraphicsDevice* arg0, bool arg1, bool arg2) */
GLProfile* GLProfile::createCustomGLProfile(String* arg0, GLProfile* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::createCustomGLProfile(String* arg0, GLProfile* arg1)");
	return 0;
}

/* private: StringBuilder* GLProfile::doIndent(StringBuilder* arg0, String* arg1, int32_t arg2) */
/* private: void GLProfile::dumpGLInfo(GLDrawableFactoryImpl* arg0, AbstractGraphicsDevice* arg1) */
bool GLProfile::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool GLProfile::equals(Object* arg0)");
	return 0;
}

GLProfile* GLProfile::get(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::get(String* arg0)");
	return 0;
}

GLProfile* GLProfile::get(AbstractGraphicsDevice* arg0, String* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::get(AbstractGraphicsDevice* arg0, String* arg1)");
	return 0;
}

GLProfile* GLProfile::get(StringArray* arg0, bool arg1)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::get(StringArray* arg0, bool arg1)");
	return 0;
}

GLProfile* GLProfile::get(AbstractGraphicsDevice* arg0, StringArray* arg1, bool arg2)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::get(AbstractGraphicsDevice* arg0, StringArray* arg1, bool arg2)");
	return 0;
}

/* private: Constructor* GLProfile::getCtor(String* arg0, bool arg1, ClassLoader* arg2) */
GLProfile* GLProfile::getDefault()
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getDefault()");
	return 0;
}

GLProfile* GLProfile::getDefault(AbstractGraphicsDevice* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getDefault(AbstractGraphicsDevice* arg0)");
	return 0;
}

AbstractGraphicsDevice* GLProfile::getDefaultDevice()
{ /* stub */
	clinit();
return defaultDevice ; /* getter */
}

GLProfile* GLProfile::getGL2ES1()
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getGL2ES1()");
	return 0;
}

GLProfile* GLProfile::getGL2ES1(AbstractGraphicsDevice* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getGL2ES1(AbstractGraphicsDevice* arg0)");
	return 0;
}

GLProfile* GLProfile::getGL2ES2()
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getGL2ES2()");
	return 0;
}

GLProfile* GLProfile::getGL2ES2(AbstractGraphicsDevice* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getGL2ES2(AbstractGraphicsDevice* arg0)");
	return 0;
}

GLProfile* GLProfile::getGL2GL3()
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getGL2GL3()");
	return 0;
}

GLProfile* GLProfile::getGL2GL3(AbstractGraphicsDevice* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getGL2GL3(AbstractGraphicsDevice* arg0)");
	return 0;
}

GLProfile* GLProfile::getGL4ES3()
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getGL4ES3()");
	return 0;
}

GLProfile* GLProfile::getGL4ES3(AbstractGraphicsDevice* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getGL4ES3(AbstractGraphicsDevice* arg0)");
	return 0;
}

String* GLProfile::getGLArrayName(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* GLProfile::getGLArrayName(int32_t arg0)");
	return 0;
}

Constructor* GLProfile::getGLCtor(bool arg0)
{ /* stub */
	unimplemented_(u"Constructor* GLProfile::getGLCtor(bool arg0)");
	return 0;
}

/* private: Constructor* GLProfile::getGLCtor(String* arg0, bool arg1) */
String* GLProfile::getGLImplBaseClassName()
{ /* stub */
	unimplemented_(u"String* GLProfile::getGLImplBaseClassName()");
	return 0;
}

/* private: String* GLProfile::getGLImplBaseClassName(String* arg0) */
String* GLProfile::getGLTypeName(int32_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* GLProfile::getGLTypeName(int32_t arg0)");
	return 0;
}

GLProfile* GLProfile::getImpl()
{ /* stub */
	unimplemented_(u"GLProfile* GLProfile::getImpl()");
	return 0;
}

String* GLProfile::getImplName()
{ /* stub */
	unimplemented_(u"String* GLProfile::getImplName()");
	return 0;
}

GLProfile* GLProfile::getMaxFixedFunc(bool arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMaxFixedFunc(bool arg0)");
	return 0;
}

GLProfile* GLProfile::getMaxFixedFunc(AbstractGraphicsDevice* arg0, bool arg1)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMaxFixedFunc(AbstractGraphicsDevice* arg0, bool arg1)");
	return 0;
}

GLProfile* GLProfile::getMaxProgrammable(bool arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMaxProgrammable(bool arg0)");
	return 0;
}

GLProfile* GLProfile::getMaxProgrammable(AbstractGraphicsDevice* arg0, bool arg1)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMaxProgrammable(AbstractGraphicsDevice* arg0, bool arg1)");
	return 0;
}

GLProfile* GLProfile::getMaxProgrammableCore(bool arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMaxProgrammableCore(bool arg0)");
	return 0;
}

GLProfile* GLProfile::getMaxProgrammableCore(AbstractGraphicsDevice* arg0, bool arg1)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMaxProgrammableCore(AbstractGraphicsDevice* arg0, bool arg1)");
	return 0;
}

GLProfile* GLProfile::getMaximum(bool arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMaximum(bool arg0)");
	return 0;
}

GLProfile* GLProfile::getMaximum(AbstractGraphicsDevice* arg0, bool arg1)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMaximum(AbstractGraphicsDevice* arg0, bool arg1)");
	return 0;
}

GLProfile* GLProfile::getMinimum(bool arg0)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMinimum(bool arg0)");
	return 0;
}

GLProfile* GLProfile::getMinimum(AbstractGraphicsDevice* arg0, bool arg1)
{ /* stub */
	clinit();
	unimplemented_(u"GLProfile* GLProfile::getMinimum(AbstractGraphicsDevice* arg0, bool arg1)");
	return 0;
}

String* GLProfile::getName()
{ /* stub */
	unimplemented_(u"String* GLProfile::getName()");
	return 0;
}

/* private: HashMap* GLProfile::getProfileMap(AbstractGraphicsDevice* arg0, bool arg1) */
String* GLProfile::glAvailabilityToString()
{ /* stub */
	clinit();
	unimplemented_(u"String* GLProfile::glAvailabilityToString()");
	return 0;
}

String* GLProfile::glAvailabilityToString(AbstractGraphicsDevice* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* GLProfile::glAvailabilityToString(AbstractGraphicsDevice* arg0)");
	return 0;
}

StringBuilder* GLProfile::glAvailabilityToString(AbstractGraphicsDevice* arg0, StringBuilder* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"StringBuilder* GLProfile::glAvailabilityToString(AbstractGraphicsDevice* arg0, StringBuilder* arg1)");
	return 0;
}

StringBuilder* GLProfile::glAvailabilityToString(AbstractGraphicsDevice* arg0, StringBuilder* arg1, String* arg2, int32_t arg3)
{ /* stub */
	clinit();
	unimplemented_(u"StringBuilder* GLProfile::glAvailabilityToString(AbstractGraphicsDevice* arg0, StringBuilder* arg1, String* arg2, int32_t arg3)");
	return 0;
}

/* private: void GLProfile::glAvailabilityToString(AbstractGraphicsDevice* arg0, StringBuilder* arg1, int32_t arg2, int32_t arg3) */
bool GLProfile::hasGLSL()
{ /* stub */
	unimplemented_(u"bool GLProfile::hasGLSL()");
	return 0;
}

int32_t GLProfile::hashCode()
{ /* stub */
	unimplemented_(u"int32_t GLProfile::hashCode()");
	return 0;
}

/* private: void GLProfile::initGLCtorImpl() */
void GLProfile::initProfiles(AbstractGraphicsDevice* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void GLProfile::initProfiles(AbstractGraphicsDevice* arg0)");
}

/* private: void GLProfile::initProfilesForDefaultDevices() */
/* private: bool GLProfile::initProfilesForDevice(AbstractGraphicsDevice* arg0) */
/* private: bool GLProfile::initProfilesForDeviceCritical(AbstractGraphicsDevice* arg0) */
void GLProfile::initSingleton()
{ /* stub */
	clinit();
	unimplemented_(u"void GLProfile::initSingleton()");
}

bool GLProfile::isAWTAvailable()
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::isAWTAvailable()");
	return 0;
}

bool GLProfile::isAnyAvailable()
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::isAnyAvailable()");
	return 0;
}

bool GLProfile::isAvailable(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::isAvailable(String* arg0)");
	return 0;
}

bool GLProfile::isAvailable(AbstractGraphicsDevice* arg0, String* arg1)
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::isAvailable(AbstractGraphicsDevice* arg0, String* arg1)");
	return 0;
}

/* private: bool GLProfile::isAvailableImpl(HashMap* arg0, String* arg1) */
bool GLProfile::isGL2()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL2()");
	return 0;
}

bool GLProfile::isGL2ES1()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL2ES1()");
	return 0;
}

bool GLProfile::isGL2ES2()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL2ES2()");
	return 0;
}

bool GLProfile::isGL2ES3()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL2ES3()");
	return 0;
}

bool GLProfile::isGL2GL3()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL2GL3()");
	return 0;
}

bool GLProfile::isGL3()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL3()");
	return 0;
}

bool GLProfile::isGL3ES3()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL3ES3()");
	return 0;
}

bool GLProfile::isGL3bc()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL3bc()");
	return 0;
}

bool GLProfile::isGL4()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL4()");
	return 0;
}

bool GLProfile::isGL4ES3()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL4ES3()");
	return 0;
}

bool GLProfile::isGL4bc()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGL4bc()");
	return 0;
}

bool GLProfile::isGLES()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGLES()");
	return 0;
}

bool GLProfile::isGLES1()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGLES1()");
	return 0;
}

bool GLProfile::isGLES2()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGLES2()");
	return 0;
}

bool GLProfile::isGLES3()
{ /* stub */
	unimplemented_(u"bool GLProfile::isGLES3()");
	return 0;
}

bool GLProfile::isHardwareRasterizer()
{ /* stub */
	unimplemented_(u"bool GLProfile::isHardwareRasterizer()");
	return 0;
}

bool GLProfile::isInitialized()
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::isInitialized()");
	return 0;
}

bool GLProfile::isValidArrayDataType(int32_t arg0, int32_t arg1, int32_t arg2, bool arg3, bool arg4)
{ /* stub */
	unimplemented_(u"bool GLProfile::isValidArrayDataType(int32_t arg0, int32_t arg1, int32_t arg2, bool arg3, bool arg4)");
	return 0;
}

bool GLProfile::isValidDataType(int32_t arg0, bool arg1)
{ /* stub */
	unimplemented_(u"bool GLProfile::isValidDataType(int32_t arg0, bool arg1)");
	return 0;
}

/* private: void GLProfile::setProfileMap(AbstractGraphicsDevice* arg0, HashMap* arg1) */
void GLProfile::shutdown()
{ /* stub */
	clinit();
	unimplemented_(u"void GLProfile::shutdown()");
}

String* GLProfile::toString()
{ /* stub */
	unimplemented_(u"String* GLProfile::toString()");
	return 0;
}

bool GLProfile::usesNativeGLES()
{ /* stub */
	unimplemented_(u"bool GLProfile::usesNativeGLES()");
	return 0;
}

bool GLProfile::usesNativeGLES(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::usesNativeGLES(String* arg0)");
	return 0;
}

bool GLProfile::usesNativeGLES1()
{ /* stub */
	unimplemented_(u"bool GLProfile::usesNativeGLES1()");
	return 0;
}

bool GLProfile::usesNativeGLES1(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::usesNativeGLES1(String* arg0)");
	return 0;
}

bool GLProfile::usesNativeGLES2()
{ /* stub */
	unimplemented_(u"bool GLProfile::usesNativeGLES2()");
	return 0;
}

bool GLProfile::usesNativeGLES2(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::usesNativeGLES2(String* arg0)");
	return 0;
}

bool GLProfile::usesNativeGLES3()
{ /* stub */
	unimplemented_(u"bool GLProfile::usesNativeGLES3()");
	return 0;
}

bool GLProfile::usesNativeGLES3(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"bool GLProfile::usesNativeGLES3(String* arg0)");
	return 0;
}

void GLProfile::verifyEquality(GLProfile* arg0)
{ /* stub */
	unimplemented_(u"void GLProfile::verifyEquality(GLProfile* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GLProfile::class_()
{
    static ::java::lang::Class* c = ::class_(u"com.jogamp.opengl.GLProfile", 27);
    return c;
}

java::lang::Class* GLProfile::getClass0()
{
	return class_();
}


// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <com/jogamp/common/util/fwd-tdme.h>
#include <com/jogamp/common/util/locks/fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::common::util::VersionNumber;
using com::jogamp::common::util::VersionNumberString;
using com::jogamp::common::util::locks::RecursiveLock;
using com::jogamp::nativewindow::AbstractGraphicsDevice;
using com::jogamp::opengl::GL;
using com::jogamp::opengl::GLDebugListener;
using com::jogamp::opengl::GLDrawable;
using com::jogamp::opengl::GLProfile;
using com::jogamp::opengl::GLRendererQuirks;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::Integer;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::ThreadLocal;
using java::nio::IntBuffer;
using java::util::HashMap;
using java::util::IdentityHashMap;
using java::util::List;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
}  // namespace lang
}  // namespace java

namespace  {
typedef ::SubArray< ::int32_tArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > int32_tArrayArray;
}  // namespace 

using java::io::SerializableArray;
using java::lang::ObjectArray;

struct default_init_tag;
class com::jogamp::opengl::GLContext
	: public virtual Object
{

public:
	typedef Object super;
	static constexpr int32_t CONTEXT_CURRENT { 1 };
	static constexpr int32_t CONTEXT_CURRENT_NEW { 2 };
	static constexpr int32_t CONTEXT_NOT_CURRENT { 0 };

public: /* protected */
	static constexpr int32_t CTX_IMPL_ACCEL_SOFT { 64 };
	static constexpr int32_t CTX_IMPL_CACHE_MASK { 1023 };
	static constexpr int32_t CTX_IMPL_ES2_COMPAT { 1024 };
	static constexpr int32_t CTX_IMPL_ES31_COMPAT { 4096 };
	static constexpr int32_t CTX_IMPL_ES32_COMPAT { 8192 };
	static constexpr int32_t CTX_IMPL_ES3_COMPAT { 2048 };
	static constexpr int32_t CTX_IMPL_FBO { 16384 };
	static constexpr int32_t CTX_IMPL_FP32_COMPAT_API { 32768 };
	static constexpr int32_t CTX_IMPL_FULL_MASK { 65535 };
	static constexpr int32_t CTX_IS_ARB_CREATED { 1 };

public:
	static constexpr int32_t CTX_OPTION_DEBUG { 32 };

public: /* protected */
	static constexpr int32_t CTX_OPTION_FORWARD { 16 };
	static constexpr int32_t CTX_PROFILE_COMPAT { 2 };
	static constexpr int32_t CTX_PROFILE_CORE { 4 };
	static constexpr int32_t CTX_PROFILE_ES { 8 };

public:
	static bool DEBUG;
	static bool DEBUG_GL;
	static bool DEBUG_TRACE_SWITCH;
	static int32_tArrayArray* ES_VERSIONS;

public: /* protected */
	static bool FORCE_MIN_FBO_SUPPORT;
	static bool FORCE_NO_COLOR_RENDERBUFFER;
	static bool FORCE_NO_FBO_SUPPORT;

public:
	static int32_tArrayArray* GL_VERSIONS;
	static bool PROFILE_ALIASING;

private:
	static String* S_EMPTY;

public:
	static bool TRACE_GL;
	static bool TRACE_SWITCH;
	static VersionNumber* Version1_0;
	static VersionNumber* Version1_1;
	static VersionNumber* Version1_10;
	static VersionNumber* Version1_2;
	static VersionNumber* Version1_20;
	static VersionNumber* Version1_30;
	static VersionNumber* Version1_4;
	static VersionNumber* Version1_40;
	static VersionNumber* Version1_5;
	static VersionNumber* Version1_50;
	static VersionNumber* Version3_0;
	static VersionNumber* Version3_1;
	static VersionNumber* Version3_2;
	static VersionNumber* Version4_3;

public: /* protected */
	static VersionNumber* Version8_0;

private:
	HashMap* attachedObjects {  };

public: /* protected */
	std::atomic< int64_t > contextHandle {  };
	VersionNumber* ctxGLSLVersion {  };
	int32_t ctxOptions {  };
	VersionNumberString* ctxVendorVersion {  };
	VersionNumber* ctxVersion {  };
	String* ctxVersionString {  };

private:
	static ThreadLocal* currentContext;

public: /* protected */
	int32_t currentSwapGroup {  };
	static IdentityHashMap* deviceVersionAvailable;

private:
	static IdentityHashMap* deviceVersionsAvailableSet;

public: /* protected */
	bool drawableRetargeted {  };
	GLRendererQuirks* glRendererQuirks {  };
	RecursiveLock* lock {  };

protected:
	void ctor();

public:
	virtual void addGLDebugListener(GLDebugListener* arg0) = 0;
	StringBuilder* append(StringBuilder* arg0);
	/*static bool appendString(StringBuilder* arg0, String* arg1, bool arg2, bool arg3); (private) */
	Object* attachObject(String* arg0, Object* arg1);
	bool bindSwapBarrier(int32_t arg0, int32_t arg1);

public: /* protected */
	virtual bool bindSwapBarrierImpl(int32_t arg0, int32_t arg1);

public:
	static bool clipGLVersion(int32_t arg0, int32_tArray* arg1, int32_tArray* arg2);

public: /* protected */
	static int32_t composeBits(int32_t arg0, int32_t arg1, int32_t arg2);

public:
	virtual void copy(GLContext* arg0, int32_t arg1) = 0;

public: /* protected */
	static VersionNumber* decomposeBits(int32_t arg0, int32_tArray* arg1);

public:
	static bool decrementGLVersion(int32_t arg0, int32_tArray* arg1, int32_tArray* arg2);
	virtual void destroy() = 0;
	Object* detachObject(String* arg0);

public: /* protected */
	static StringBuilder* dumpAvailableGLVersions(StringBuilder* arg0);

public:
	virtual void enableGLDebugMessage(bool arg0) = 0;
	Object* getAttachedObject(String* arg0);

public: /* protected */
	static int32_t getAvailableContextProperties(AbstractGraphicsDevice* arg0, GLProfile* arg1);
	static GLProfile* getAvailableGLProfile(AbstractGraphicsDevice* arg0, int32_t arg1, int32_t arg2);

public: /* package */
	static String* getAvailableGLProfileName(AbstractGraphicsDevice* arg0, int32_t arg1, int32_t arg2);

public: /* protected */
	static Integer* getAvailableGLVersion(AbstractGraphicsDevice* arg0, int32_t arg1, int32_t arg2);
	static bool getAvailableGLVersion(AbstractGraphicsDevice* arg0, int32_t arg1, int32_t arg2, int32_tArray* arg3, int32_tArray* arg4, int32_tArray* arg5);
	static String* getAvailableGLVersionAsString(AbstractGraphicsDevice* arg0, int32_t arg1, int32_t arg2);
	static bool getAvailableGLVersionsSet(AbstractGraphicsDevice* arg0);

public:
	virtual int32_t getBoundFramebuffer(int32_t arg0) = 0;
	virtual int32_t getContextCreationFlags() = 0;
	List* getCreatedShares();
	static GLContext* getCurrent();
	static GL* getCurrentGL();
	virtual int32_t getDefaultDrawFramebuffer() = 0;
	virtual int32_t getDefaultPixelDataFormat() = 0;
	virtual int32_t getDefaultPixelDataType() = 0;
	virtual int32_t getDefaultReadBuffer() = 0;
	virtual int32_t getDefaultReadFramebuffer() = 0;
	virtual int32_t getDefaultVAO() = 0;
	List* getDestroyedShares();

public: /* protected */
	static String* getDeviceVersionAvailableKey(AbstractGraphicsDevice* arg0, int32_t arg1, int32_t arg2);

public:
	virtual GL* getGL() = 0;
	/*static int32_t getGL3ctp(AbstractGraphicsDevice* arg0); (private) */
	virtual String* getGLDebugMessageExtension() = 0;
	virtual GLDrawable* getGLDrawable() = 0;
	virtual int32_t getGLExtensionCount() = 0;
	virtual String* getGLExtensionsString() = 0;

public: /* protected */
	static StringBuilder* getGLProfile(StringBuilder* arg0, int32_t arg1);
	static String* getGLProfile(int32_t arg0, int32_t arg1, int32_t arg2);

public:
	virtual GLDrawable* getGLReadDrawable() = 0;
	VersionNumber* getGLSLVersionNumber();
	String* getGLSLVersionString();
	VersionNumberString* getGLVendorVersionNumber();
	String* getGLVersion();

public: /* protected */
	static StringBuilder* getGLVersion(StringBuilder* arg0, VersionNumber* arg1, int32_t arg2, String* arg3);
	static String* getGLVersion(int32_t arg0, int32_t arg1, int32_t arg2, String* arg3);
	static StringBuilder* getGLVersion(StringBuilder* arg0, int32_t arg1, int32_t arg2, int32_t arg3, String* arg4);

public:
	VersionNumber* getGLVersionNumber();
	int64_t getHandle();
	static int32_t getMaxMajor(int32_t arg0);
	static int32_t getMaxMinor(int32_t arg0, int32_t arg1);
	int32_t getMaxRenderbufferSamples();
	virtual int32_t getPlatformExtensionCount() = 0;
	virtual String* getPlatformExtensionsString() = 0;
	GLRendererQuirks* getRendererQuirks();

public: /* protected */
	static void getRequestMajorAndCompat(GLProfile* arg0, int32_tArray* arg1);

public:
	virtual GL* getRootGL() = 0;
	GLContext* getSharedMaster();

public: /* protected */
	static VersionNumber* getStaticGLSLVersionNumber(int32_t arg0, int32_t arg1, int32_t arg2);

public:
	virtual int32_t getSwapGroup();
	virtual int32_t getSwapInterval();

public: /* protected */
	static String* getThreadName();

public:
	virtual void glDebugMessageControl(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, IntBuffer* arg4, bool arg5) = 0;
	virtual void glDebugMessageControl(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_tArray* arg4, int32_t arg5, bool arg6) = 0;
	virtual void glDebugMessageInsert(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, String* arg4) = 0;
	bool hasBasicFBOSupport();
	bool hasFP32CompatAPI();
	bool hasFullFBOSupport();
	bool hasGLSL();
	bool hasNoDefaultVAO();
	bool hasRendererQuirk(int32_t arg0);
	bool isCPUDataSourcingAvail();
	bool isCreated();
	bool isCreatedWithARBMethod();
	bool isCurrent();
	virtual bool isExtensionAvailable(String* arg0) = 0;
	static bool isFBOAvailable(AbstractGraphicsDevice* arg0, GLProfile* arg1);
	virtual bool isFunctionAvailable(String* arg0) = 0;
	bool isGL2();
	static bool isGL2Available(AbstractGraphicsDevice* arg0, boolArray* arg1);
	bool isGL2ES1();
	bool isGL2ES2();
	bool isGL2ES3();
	bool isGL2GL3();
	bool isGL3();
	static bool isGL3Available(AbstractGraphicsDevice* arg0, boolArray* arg1);
	bool isGL3ES3();
	bool isGL3bc();
	static bool isGL3bcAvailable(AbstractGraphicsDevice* arg0, boolArray* arg1);
	bool isGL3core();
	bool isGL4();
	static bool isGL4Available(AbstractGraphicsDevice* arg0, boolArray* arg1);
	bool isGL4ES3();
	bool isGL4bc();
	static bool isGL4bcAvailable(AbstractGraphicsDevice* arg0, boolArray* arg1);
	bool isGL4core();
	bool isGLCompatibilityProfile();
	bool isGLCoreProfile();
	bool isGLDebugEnabled();
	virtual bool isGLDebugMessageEnabled() = 0;
	virtual bool isGLDebugSynchronous() = 0;
	bool isGLES();
	bool isGLES1();
	static bool isGLES1Available(AbstractGraphicsDevice* arg0, boolArray* arg1);
	bool isGLES2();
	static bool isGLES2Available(AbstractGraphicsDevice* arg0, boolArray* arg1);
	bool isGLES2Compatible();
	bool isGLES3();
	bool isGLES31Compatible();
	static bool isGLES31CompatibleAvailable(AbstractGraphicsDevice* arg0);
	bool isGLES32Compatible();
	static bool isGLES32CompatibleAvailable(AbstractGraphicsDevice* arg0);
	static bool isGLES3Available(AbstractGraphicsDevice* arg0, boolArray* arg1);
	bool isGLES3Compatible();
	static bool isGLES3CompatibleAvailable(AbstractGraphicsDevice* arg0);
	bool isGLESProfile();
	bool isGLForwardCompatible();
	virtual bool isGLReadDrawableAvailable() = 0;

public: /* protected */
	static bool isGLVersionAvailable(AbstractGraphicsDevice* arg0, int32_t arg1, int32_t arg2, boolArray* arg3);

public:
	bool isGLcore();
	bool isHardwareRasterizer();
	static int32_t isHardwareRasterizer(AbstractGraphicsDevice* arg0, GLProfile* arg1);
	virtual bool isNPOTTextureAvailable();
	bool isShared();
	virtual bool isTextureFormatBGRA8888Available();
	static bool isValidGLVersion(int32_t arg0, int32_t arg1, int32_t arg2);
	bool joinSwapGroup(int32_t arg0);

public: /* protected */
	virtual bool joinSwapGroupImpl(int32_t arg0);

public:
	virtual int32_t makeCurrent() = 0;
	static String* makeCurrentResultToString(int32_t arg0);

public: /* protected */
	static Integer* mapAvailableGLVersion(AbstractGraphicsDevice* arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5);

public:
	bool queryMaxSwapGroups(int32_tArray* arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3);

public: /* protected */
	virtual bool queryMaxSwapGroupsImpl(int32_tArray* arg0, int32_t arg1, int32_tArray* arg2, int32_t arg3);

public:
	virtual void release() = 0;
	virtual void removeGLDebugListener(GLDebugListener* arg0) = 0;

public: /* protected */
	virtual void resetStates(bool arg0);
	static void setAvailableGLVersionsSet(AbstractGraphicsDevice* arg0, bool arg1);

public:
	virtual void setContextCreationFlags(int32_t arg0) = 0;

public: /* protected */
	static void setCurrent(GLContext* arg0);
	virtual void setDefaultSwapInterval();

public:
	virtual GL* setGL(GL* arg0) = 0;
	virtual void setGLDebugSynchronous(bool arg0) = 0;
	virtual GLDrawable* setGLDrawable(GLDrawable* arg0, bool arg1) = 0;
	virtual GLDrawable* setGLReadDrawable(GLDrawable* arg0) = 0;
	virtual bool setSwapInterval(int32_t arg0);

public: /* protected */
	virtual bool setSwapIntervalImpl(int32_t arg0);
	static void shutdown();
	static String* toHexString(int32_t arg0);
	static String* toHexString(int64_t arg0);

public:
	String* toString() override;
	void validateCurrent();
	/*static void validateProfileBits(int32_t arg0, String* arg1); (private) */

	// Generated

public: /* protected */
	GLContext();
protected:
	GLContext(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

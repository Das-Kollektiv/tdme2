// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <Array.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/channels/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Console;
using java::io::InputStream;
using java::io::PrintStream;
using java::lang::Class;
using java::lang::SecurityManager;
using java::lang::String;
using java::nio::channels::Channel;
using java::util::Map;
using java::util::Properties;


struct default_init_tag;
class java::lang::System final
	: public Object
{

public:
	typedef Object super;

private:
	static std::atomic< Console* > cons;

public:
	static PrintStream* err;
	static InputStream* in;
	static PrintStream* out;

private:
	static Properties* props;
	static std::atomic< SecurityManager* > security;

	/*void ctor(); (private) */
	/*static void adjustPropertiesForBackwardCompatibility(Properties* arg0); (private) */

public:
	static void arraycopy(char16_tArray* arg0, int32_t arg1, char16_tArray* arg2, int32_t arg3, int32_t arg4);
	static void arraycopy(floatArray* arg0, int32_t arg1, floatArray* arg2, int32_t arg3, int32_t arg4);
	static void arraycopy(ObjectArray* arg0, int32_t arg1, ObjectArray* arg2, int32_t arg3, int32_t arg4);
	/*static void checkIO(); (private) */
	/*static void checkKey(String* arg0); (private) */
	static String* clearProperty(String* arg0);
	static Console* console();
	static int64_t currentTimeMillis();
	static void exit(int32_t arg0);
	static void gc();

public: /* package */
	static Class* getCallerClass();

public:
	static Properties* getProperties();
	static String* getProperty(String* arg0);
	static String* getProperty(String* arg0, String* arg1);
	static SecurityManager* getSecurityManager();
	static Map* getenv();
	static String* getenv(String* arg0);
	static int32_t identityHashCode(Object* arg0);
	static Channel* inheritedChannel();
	/*static Properties* initProperties(Properties* arg0); (private) */
	/*static void initializeSystemClass(); (private) */
	static void load(String* arg0);
	static void loadLibrary(String* arg0);
	static String* mapLibraryName(String* arg0);
	static int64_t nanoTime();
	/*static InputStream* nullInputStream(); (private) */
	/*static PrintStream* nullPrintStream(); (private) */
	/*static void registerNatives(); (private) */
	static void runFinalization();
	static void runFinalizersOnExit(bool arg0);
	static void setErr(PrintStream* arg0);
	/*static void setErr0(PrintStream* arg0); (private) */
	static void setIn(InputStream* arg0);
	/*static void setIn0(InputStream* arg0); (private) */
	/*static void setJavaLangAccess(); (private) */
	static void setOut(PrintStream* arg0);
	/*static void setOut0(PrintStream* arg0); (private) */
	static void setProperties(Properties* arg0);
	static String* setProperty(String* arg0, String* arg1);
	static void setSecurityManager(SecurityManager* arg0);
	/*static void setSecurityManager0(SecurityManager* arg0); (private) */

	// Generated
	System();
protected:
	System(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

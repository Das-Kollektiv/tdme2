// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/security/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <sun/misc/fwd-tdme.h>
#include <sun/nio/ch/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/lang/Runnable.h>

using java::lang::Object;
using java::lang::Runnable;
using java::io::Serializable;
using java::lang::Class;
using java::lang::ClassLoader;
using java::lang::Cloneable;
using java::lang::RuntimePermission;
using java::lang::StackTraceElement;
using java::lang::String;
using java::lang::Thread_State;
using java::lang::Thread_UncaughtExceptionHandler;
using java::lang::ThreadGroup;
using java::lang::ThreadLocal_ThreadLocalMap;
using java::lang::Throwable;
using java::security::AccessControlContext;
using java::util::Map;
using sun::misc::SoftCache;
using sun::nio::ch::Interruptible;
using java::lang::Thread;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
typedef ::SubArray< ::java::lang::Runnable, ObjectArray > RunnableArray;
typedef ::SubArray< ::java::lang::StackTraceElement, ObjectArray, ::java::io::SerializableArray > StackTraceElementArray;
typedef ::SubArray< ::java::lang::Thread, ObjectArray, RunnableArray > ThreadArray;
typedef ::SubArray< ::java::lang::StackTraceElementArray, CloneableArray, ::java::io::SerializableArray > StackTraceElementArrayArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CloneableArray;
using java::lang::ObjectArray;
using java::lang::RunnableArray;
using java::lang::StackTraceElementArray;
using java::lang::StackTraceElementArrayArray;
using java::lang::ThreadArray;

struct default_init_tag;
class java::lang::Thread
	: public virtual Object
	, public virtual Runnable
{

public:
	typedef Object super;

private:
	static StackTraceElementArray* EMPTY_STACK_TRACE;

public:
	static constexpr int32_t MAX_PRIORITY { 10 };
	static constexpr int32_t MIN_PRIORITY { 1 };
	static constexpr int32_t NORM_PRIORITY { 5 };

private:
	static RuntimePermission* SUBCLASS_IMPLEMENTATION_PERMISSION;
	std::atomic< Interruptible* > blocker {  };
	Object* blockerLock {  };
	ClassLoader* contextClassLoader {  };
	bool daemon {  };
	static std::atomic< Thread_UncaughtExceptionHandler* > defaultUncaughtExceptionHandler;
	int64_t eetop {  };
	ThreadGroup* group {  };

public: /* package */
	ThreadLocal_ThreadLocalMap* inheritableThreadLocals {  };

private:
	AccessControlContext* inheritedAccessControlContext {  };
	std::atomic< Thread* > me {  };
	char16_tArray* name {  };
	int64_t nativeParkEventPointer {  };

public: /* package */
	std::atomic< Object* > parkBlocker {  };

private:
	int32_t priority {  };
	bool single_step {  };
	int64_t stackSize {  };
	bool stillborn {  };
	bool stopBeforeStart {  };
	static SoftCache* subclassAudits;
	Runnable* target {  };
	static int32_t threadInitNumber;

public: /* package */
	ThreadLocal_ThreadLocalMap* threadLocals {  };

private:
	Thread* threadQ {  };
	static int64_t threadSeqNumber;
	int32_t threadStatus {  };
	Throwable* throwableFromStop {  };
	int64_t tid {  };
	std::atomic< Thread_UncaughtExceptionHandler* > uncaughtExceptionHandler {  };

protected:
	void ctor();
	void ctor(Runnable* arg0);
	void ctor(String* arg0);
	void ctor(Runnable* arg0, AccessControlContext* arg1);
	void ctor(ThreadGroup* arg0, Runnable* arg1);
	void ctor(ThreadGroup* arg0, String* arg1);
	void ctor(Runnable* arg0, String* arg1);
	/*void ctor(ThreadGroup* arg0, Runnable* arg1, bool arg2); (private) */
	/*void ctor(ThreadGroup* arg0, String* arg1, bool arg2); (private) */
	void ctor(ThreadGroup* arg0, Runnable* arg1, String* arg2);
	void ctor(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3);

public:
	static int32_t activeCount();
	/*static bool auditSubclass(Class* arg0); (private) */

public: /* package */
	virtual void blockedOn(Interruptible* arg0);

public:
	void checkAccess();

public: /* protected */
	Object* clone() override;

public:
	virtual int32_t countStackFrames();
	static Thread* currentThread();
	virtual void destroy();
	/*void dispatchUncaughtException(Throwable* arg0); (private) */
	static void dumpStack();
	/*static StackTraceElementArrayArray* dumpThreads(ThreadArray* arg0); (private) */
	static int32_t enumerate(ThreadArray* arg0);
	/*void exit(); (private) */
	static Map* getAllStackTraces();
	virtual ClassLoader* getContextClassLoader();
	static Thread_UncaughtExceptionHandler* getDefaultUncaughtExceptionHandler();
	virtual int64_t getId();
	String* getName();
	int32_t getPriority();
	virtual StackTraceElementArray* getStackTrace();
	virtual Thread_State* getState();
	ThreadGroup* getThreadGroup();
	/*static ThreadArray* getThreads(); (private) */
	virtual Thread_UncaughtExceptionHandler* getUncaughtExceptionHandler();
	static bool holdsLock(Object* arg0);
	/*void init_(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3); (private) */
	/*void init_(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3, AccessControlContext* arg4); (private) */
	virtual void interrupt();
	/*void interrupt0(); (private) */
	static bool interrupted();
	bool isAlive();
	/*static bool isCCLOverridden(Class* arg0); (private) */
	bool isDaemon();
	virtual bool isInterrupted();
	/*bool isInterrupted(bool arg0); (private) */
	void join();
	void join(int64_t arg0);
	void join(int64_t arg0, int32_t arg1);
	/*static int64_t nextThreadID(); (private) */
	/*static int32_t nextThreadNum(); (private) */
	/*static void registerNatives(); (private) */
	void resume();
	/*void resume0(); (private) */
	void run() override;
	virtual void setContextClassLoader(ClassLoader* arg0);
	void setDaemon(bool arg0);
	static void setDefaultUncaughtExceptionHandler(Thread_UncaughtExceptionHandler* arg0);
	void setName(String* arg0);
	/*void setNativeName(String* arg0); (private) */
	void setPriority(int32_t arg0);
	/*void setPriority0(int32_t arg0); (private) */
	virtual void setUncaughtExceptionHandler(Thread_UncaughtExceptionHandler* arg0);
	static void sleep(int64_t arg0);
	static void sleep(int64_t arg0, int32_t arg1);
	virtual void start();
	/*void start0(); (private) */
	void stop();
	void stop(Throwable* arg0);
	/*void stop0(Object* arg0); (private) */
	/*void stop1(Throwable* arg0); (private) */
	void suspend();
	/*void suspend0(); (private) */
	String* toString() override;
	static void yield();

	// Generated
	Thread();
	Thread(Runnable* arg0);
	Thread(String* arg0);

public: /* package */
	Thread(Runnable* arg0, AccessControlContext* arg1);

public:
	Thread(ThreadGroup* arg0, Runnable* arg1);
	Thread(ThreadGroup* arg0, String* arg1);
	Thread(Runnable* arg0, String* arg1);
	Thread(ThreadGroup* arg0, Runnable* arg1, String* arg2);
	Thread(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3);
protected:
	Thread(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};

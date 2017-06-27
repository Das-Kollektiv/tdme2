// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Thread.h>

using java::lang::Thread;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Runnable, ObjectArray > RunnableArray;
typedef ::SubArray< ::java::lang::StackTraceElement, ObjectArray, ::java::io::SerializableArray > StackTraceElementArray;
typedef ::SubArray< ::java::lang::Thread, ObjectArray, RunnableArray > ThreadArray;
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::lang::Thread::Thread(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Thread::Thread()
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::Thread::Thread(Runnable* arg0)
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Thread::Thread(String* arg0)
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Thread::Thread(Runnable* arg0, AccessControlContext* arg1)
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::lang::Thread::Thread(ThreadGroup* arg0, Runnable* arg1)
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::lang::Thread::Thread(ThreadGroup* arg0, String* arg1)
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::lang::Thread::Thread(Runnable* arg0, String* arg1)
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::lang::Thread::Thread(ThreadGroup* arg0, Runnable* arg1, String* arg2)
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}

java::lang::Thread::Thread(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3)
	: Thread(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2, arg3);
}

StackTraceElementArray* java::lang::Thread::EMPTY_STACK_TRACE;
constexpr int32_t java::lang::Thread::MAX_PRIORITY;
constexpr int32_t java::lang::Thread::MIN_PRIORITY;
constexpr int32_t java::lang::Thread::NORM_PRIORITY;
RuntimePermission* java::lang::Thread::SUBCLASS_IMPLEMENTATION_PERMISSION;
std::atomic< Thread_UncaughtExceptionHandler* > java::lang::Thread::defaultUncaughtExceptionHandler;
SoftCache* java::lang::Thread::subclassAudits;
int32_t java::lang::Thread::threadInitNumber;
int64_t java::lang::Thread::threadSeqNumber;

void Thread::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor()");
}

void Thread::ctor(Runnable* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor(Runnable* arg0)");
}

void Thread::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor(String* arg0)");
}

void Thread::ctor(Runnable* arg0, AccessControlContext* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor(Runnable* arg0, AccessControlContext* arg1)");
}

void Thread::ctor(ThreadGroup* arg0, Runnable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor(ThreadGroup* arg0, Runnable* arg1)");
}

void Thread::ctor(ThreadGroup* arg0, String* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor(ThreadGroup* arg0, String* arg1)");
}

void Thread::ctor(Runnable* arg0, String* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor(Runnable* arg0, String* arg1)");
}

/* private: void Thread::ctor(ThreadGroup* arg0, Runnable* arg1, bool arg2) */
/* private: void Thread::ctor(ThreadGroup* arg0, String* arg1, bool arg2) */
void Thread::ctor(ThreadGroup* arg0, Runnable* arg1, String* arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor(ThreadGroup* arg0, Runnable* arg1, String* arg2)");
}

void Thread::ctor(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Thread::ctor(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3)");
}

int32_t Thread::activeCount()
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Thread::activeCount()");
	return 0;
}

/* private: bool Thread::auditSubclass(Class* arg0) */
void Thread::blockedOn(Interruptible* arg0)
{ /* stub */
	unimplemented_(u"void Thread::blockedOn(Interruptible* arg0)");
}

void Thread::checkAccess()
{ /* stub */
	unimplemented_(u"void Thread::checkAccess()");
}

Object* Thread::clone()
{ /* stub */
	unimplemented_(u"Object* Thread::clone()");
	return 0;
}

void Thread::destroy()
{ /* stub */
	unimplemented_(u"void Thread::destroy()");
}

/* private: void Thread::dispatchUncaughtException(Throwable* arg0) */
void Thread::dumpStack()
{ /* stub */
	clinit();
	unimplemented_(u"void Thread::dumpStack()");
}

int32_t Thread::enumerate(ThreadArray* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Thread::enumerate(ThreadArray* arg0)");
	return 0;
}

/* private: void Thread::exit() */
Map* Thread::getAllStackTraces()
{ /* stub */
	clinit();
	unimplemented_(u"Map* Thread::getAllStackTraces()");
	return 0;
}

ClassLoader* Thread::getContextClassLoader()
{ /* stub */
return contextClassLoader ; /* getter */
}

Thread_UncaughtExceptionHandler* Thread::getDefaultUncaughtExceptionHandler()
{ /* stub */
	clinit();
return defaultUncaughtExceptionHandler ; /* getter */
}

int64_t Thread::getId()
{ /* stub */
	unimplemented_(u"int64_t Thread::getId()");
	return 0;
}

String* Thread::getName()
{ /* stub */
}

int32_t Thread::getPriority()
{ /* stub */
return priority ; /* getter */
}

StackTraceElementArray* Thread::getStackTrace()
{ /* stub */
	unimplemented_(u"StackTraceElementArray* Thread::getStackTrace()");
	return 0;
}

Thread_State* Thread::getState()
{ /* stub */
	unimplemented_(u"Thread_State* Thread::getState()");
	return 0;
}

ThreadGroup* Thread::getThreadGroup()
{ /* stub */
	unimplemented_(u"ThreadGroup* Thread::getThreadGroup()");
	return 0;
}

Thread_UncaughtExceptionHandler* Thread::getUncaughtExceptionHandler()
{ /* stub */
return uncaughtExceptionHandler ; /* getter */
}

/* private: void Thread::init_(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3) */
/* private: void Thread::init_(ThreadGroup* arg0, Runnable* arg1, String* arg2, int64_t arg3, AccessControlContext* arg4) */
void Thread::interrupt()
{ /* stub */
	unimplemented_(u"void Thread::interrupt()");
}

bool Thread::interrupted()
{ /* stub */
	clinit();
	unimplemented_(u"bool Thread::interrupted()");
	return 0;
}

/* private: bool Thread::isCCLOverridden(Class* arg0) */
bool Thread::isDaemon()
{ /* stub */
	unimplemented_(u"bool Thread::isDaemon()");
	return 0;
}

bool Thread::isInterrupted()
{ /* stub */
	unimplemented_(u"bool Thread::isInterrupted()");
	return 0;
}

void Thread::join()
{ /* stub */
	unimplemented_(u"void Thread::join()");
}

void Thread::join(int64_t arg0)
{ /* stub */
	unimplemented_(u"void Thread::join(int64_t arg0)");
}

void Thread::join(int64_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"void Thread::join(int64_t arg0, int32_t arg1)");
}

/* private: int64_t Thread::nextThreadID() */
/* private: int32_t Thread::nextThreadNum() */
void Thread::resume()
{ /* stub */
	unimplemented_(u"void Thread::resume()");
}

void Thread::run()
{ /* stub */
	unimplemented_(u"void Thread::run()");
}

void Thread::setContextClassLoader(ClassLoader* arg0)
{ /* stub */
	this->contextClassLoader = arg0; /* setter */
}

void Thread::setDaemon(bool arg0)
{ /* stub */
	this->daemon = arg0; /* setter */
}

void Thread::setDefaultUncaughtExceptionHandler(Thread_UncaughtExceptionHandler* arg0)
{ /* stub */
	clinit();
	Thread::defaultUncaughtExceptionHandler = arg0; /* setter */
}

void Thread::setName(String* arg0)
{ /* stub */
}

void Thread::setPriority(int32_t arg0)
{ /* stub */
	this->priority = arg0; /* setter */
}

void Thread::setUncaughtExceptionHandler(Thread_UncaughtExceptionHandler* arg0)
{ /* stub */
	this->uncaughtExceptionHandler = arg0; /* setter */
}

void Thread::sleep(int64_t arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"void Thread::sleep(int64_t arg0, int32_t arg1)");
}

void Thread::start()
{ /* stub */
	unimplemented_(u"void Thread::start()");
}

void Thread::stop()
{ /* stub */
	unimplemented_(u"void Thread::stop()");
}

void Thread::stop(Throwable* arg0)
{ /* stub */
	unimplemented_(u"void Thread::stop(Throwable* arg0)");
}

/* private: void Thread::stop1(Throwable* arg0) */
void Thread::suspend()
{ /* stub */
	unimplemented_(u"void Thread::suspend()");
}

String* Thread::toString()
{ /* stub */
	unimplemented_(u"String* Thread::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Thread::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Thread", 16);
    return c;
}

java::lang::Class* Thread::getClass0()
{
	return class_();
}


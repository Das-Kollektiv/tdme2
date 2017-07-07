// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Thread.h>

#include <unistd.h>

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

extern void unimplemented_(const char16_t* name);

int32_t Thread::countStackFrames()
{ /* native */
	unimplemented_(u"int32_t Thread::countStackFrames()");
	return 0;
}

Thread* Thread::currentThread()
{ /* native */
	clinit();
	unimplemented_(u"Thread* Thread::currentThread()");
	return 0;
}

/* private: StackTraceElementArrayArray* Thread::dumpThreads(ThreadArray* arg0) */
/* private: ThreadArray* Thread::getThreads() */
bool Thread::holdsLock(Object* arg0)
{ /* native */
	clinit();
	unimplemented_(u"bool Thread::holdsLock(Object* arg0)");
	return 0;
}

/* private: void Thread::interrupt0() */
bool Thread::isAlive()
{ /* native */
	unimplemented_(u"bool Thread::isAlive()");
	return 0;
}

/* private: bool Thread::isInterrupted(bool arg0) */
/* private: void Thread::registerNatives() */
/* private: void Thread::resume0() */
/* private: void Thread::setNativeName(String* arg0) */
/* private: void Thread::setPriority0(int32_t arg0) */
void Thread::sleep(int64_t arg0)
{ /* native */
	clinit();
	uint64_t secondsWaited = 0L;
	while (arg0 - (secondsWaited * 1000L) >= 1000L) {
		::sleep(1);
		secondsWaited++;
	}
	usleep((arg0 - (secondsWaited * 1000L)) * 1000L);
}

/* private: void Thread::start0() */
/* private: void Thread::stop0(Object* arg0) */
/* private: void Thread::suspend0() */
void Thread::yield()
{ /* native */
	clinit();
	unimplemented_(u"void Thread::yield()");
}


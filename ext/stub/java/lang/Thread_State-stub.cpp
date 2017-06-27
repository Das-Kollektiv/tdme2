// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Thread_State.h>

using java::lang::Thread_State;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
typedef ::SubArray< ::java::lang::Thread_State, EnumArray > Thread_StateArray;
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::lang::Thread_State::Thread_State(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Thread_StateArray* java::lang::Thread_State::$VALUES;
Thread_State* java::lang::Thread_State::BLOCKED;
Thread_State* java::lang::Thread_State::NEW;
Thread_State* java::lang::Thread_State::RUNNABLE;
Thread_State* java::lang::Thread_State::TERMINATED;
Thread_State* java::lang::Thread_State::TIMED_WAITING;
Thread_State* java::lang::Thread_State::WAITING;

/* private: void Thread_State::ctor(::java::lang::String* name, int ordinal) */
Thread_State* Thread_State::valueOf(String* name)
{ /* stub */
	clinit();
	unimplemented_(u"Thread_State* Thread_State::valueOf(String* name)");
	return 0;
}

Thread_StateArray* Thread_State::values()
{ /* stub */
	clinit();
	unimplemented_(u"Thread_StateArray* Thread_State::values()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Thread_State::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Thread.State", 22);
    return c;
}

Enum* Thread_State::valueOf(Class* enumType, String* name)
{
	return super::valueOf(enumType, name);
}

java::lang::Class* Thread_State::getClass0()
{
	return class_();
}


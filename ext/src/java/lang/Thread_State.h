// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Class;
using java::lang::Comparable;
using java::lang::String;
using java::lang::Object;
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

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using java::lang::Thread_StateArray;

struct default_init_tag;
class java::lang::Thread_State final
	: public Enum
{

public:
	typedef Enum super;

private:
	static Thread_StateArray* $VALUES;

public:
	static Thread_State* BLOCKED;
	static Thread_State* NEW;
	static Thread_State* RUNNABLE;
	static Thread_State* TERMINATED;
	static Thread_State* TIMED_WAITING;
	static Thread_State* WAITING;

	/*void ctor(::java::lang::String* name, int ordinal); (private) */
	static Thread_State* valueOf(String* arg0);
	static Thread_StateArray* values();

	// Generated
	Thread_State(::java::lang::String* name, int ordinal);
protected:
	Thread_State(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static Enum* valueOf(Class* enumType, String* name);

private:
	virtual ::java::lang::Class* getClass0();
};

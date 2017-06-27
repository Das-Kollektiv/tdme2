// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/newt/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Class;
using java::lang::Comparable;
using java::lang::String;
using com::jogamp::newt::Window_ReparentOperation;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
}  // namespace lang

namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
}  // namespace lang
}  // namespace java

namespace com {
namespace jogamp {
namespace newt {
typedef ::SubArray< ::com::jogamp::newt::Window_ReparentOperation, ::java::lang::EnumArray > Window_ReparentOperationArray;
}  // namespace newt
}  // namespace jogamp
}  // namespace com

using com::jogamp::newt::Window_ReparentOperationArray;
using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;

struct default_init_tag;
class com::jogamp::newt::Window_ReparentOperation final
	: public Enum
{

public:
	typedef Enum super;

private:
	static Window_ReparentOperationArray* $VALUES;

public:
	static Window_ReparentOperation* ACTION_INVALID;
	static Window_ReparentOperation* ACTION_NATIVE_CREATION;
	static Window_ReparentOperation* ACTION_NATIVE_CREATION_PENDING;
	static Window_ReparentOperation* ACTION_NATIVE_REPARENTING;
	static Window_ReparentOperation* ACTION_NOP;

	/*void ctor(::java::lang::String* name, int ordinal); (private) */
	static Window_ReparentOperation* valueOf(String* arg0);
	static Window_ReparentOperationArray* values();

	// Generated
	Window_ReparentOperation(::java::lang::String* name, int ordinal);
protected:
	Window_ReparentOperation(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static Enum* valueOf(Class* enumType, String* name);

private:
	virtual ::java::lang::Class* getClass0();
};

// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Enum.h>
#include <com/jogamp/newt/event/InputEvent_InputClass.h>

using java::lang::Enum;
using com::jogamp::newt::event::InputEvent_InputClass;
using java::io::Serializable;
using java::lang::Class;
using java::lang::Comparable;
using java::lang::String;
using com::jogamp::newt::event::MouseEvent_PointerClass;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::InputEvent_InputClass, ::java::lang::ObjectArray > InputEvent_InputClassArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

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
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::MouseEvent_PointerClass, ::java::lang::EnumArray, InputEvent_InputClassArray > MouseEvent_PointerClassArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

using com::jogamp::newt::event::InputEvent_InputClassArray;
using com::jogamp::newt::event::MouseEvent_PointerClassArray;
using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;

struct default_init_tag;
class com::jogamp::newt::event::MouseEvent_PointerClass final
	: public Enum
	, public InputEvent_InputClass
{

public:
	typedef Enum super;

private:
	static MouseEvent_PointerClassArray* $VALUES;

public:
	static MouseEvent_PointerClass* Offscreen;
	static MouseEvent_PointerClass* Onscreen;
	static MouseEvent_PointerClass* Undefined;

	/*void ctor(::java::lang::String* name, int ordinal); (private) */
	static MouseEvent_PointerClass* valueOf(String* arg0);
	static MouseEvent_PointerClassArray* values();

	// Generated
	MouseEvent_PointerClass(::java::lang::String* name, int ordinal);
protected:
	MouseEvent_PointerClass(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static Enum* valueOf(Class* arg0, String* arg1);

private:
	virtual ::java::lang::Class* getClass0();
};

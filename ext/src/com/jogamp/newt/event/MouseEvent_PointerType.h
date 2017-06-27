// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Enum.h>
#include <com/jogamp/newt/event/InputEvent_InputType.h>

using java::lang::Enum;
using com::jogamp::newt::event::InputEvent_InputType;
using com::jogamp::newt::event::MouseEvent_PointerClass;
using java::io::Serializable;
using java::lang::Class;
using java::lang::Comparable;
using java::lang::String;
using com::jogamp::newt::event::MouseEvent_PointerType;
using java::lang::Object;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace com {
namespace jogamp {
namespace newt {
namespace event {
typedef ::SubArray< ::com::jogamp::newt::event::InputEvent_InputType, ::java::lang::ObjectArray > InputEvent_InputTypeArray;
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
typedef ::SubArray< ::com::jogamp::newt::event::MouseEvent_PointerType, ::java::lang::EnumArray, InputEvent_InputTypeArray > MouseEvent_PointerTypeArray;
}  // namespace event
}  // namespace newt
}  // namespace jogamp
}  // namespace com

using com::jogamp::newt::event::InputEvent_InputTypeArray;
using com::jogamp::newt::event::MouseEvent_PointerTypeArray;
using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;

struct default_init_tag;
class com::jogamp::newt::event::MouseEvent_PointerType final
	: public Enum
	, public InputEvent_InputType
{

public:
	typedef Enum super;

private:
	static MouseEvent_PointerTypeArray* $VALUES;

public:
	static MouseEvent_PointerType* Mouse;
	static MouseEvent_PointerType* Pen;
	static MouseEvent_PointerType* TouchPad;
	static MouseEvent_PointerType* TouchScreen;
	static MouseEvent_PointerType* Undefined;

public: /* package */
	MouseEvent_PointerClass* pc {  };

	/*void ctor(::java::lang::String* name, int ordinal, MouseEvent_PointerClass* arg0); (private) */

public:
	MouseEvent_PointerClass* getPointerClass();
	static MouseEvent_PointerType* valueOf(String* arg0);
	static MouseEvent_PointerType* valueOf(int32_t arg0);
	static MouseEvent_PointerTypeArray* values();
	static MouseEvent_PointerTypeArray* valuesOf(int32_tArray* arg0);

	// Generated
	MouseEvent_PointerType(::java::lang::String* name, int ordinal);
protected:
	MouseEvent_PointerType(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static Enum* valueOf(Class* arg0, String* arg1);

private:
	virtual ::java::lang::Class* getClass0();
};

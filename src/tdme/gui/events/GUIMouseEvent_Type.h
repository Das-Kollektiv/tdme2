// Generated from /tdme/src/tdme/gui/events/GUIMouseEvent.java

#pragma once

#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <java/lang/Enum.h>

using java::lang::Enum;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::String;
using tdme::gui::events::GUIMouseEvent;
using java::lang::Object;
using tdme::gui::events::GUIMouseEvent_Type;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace gui {
namespace events {
typedef ::SubArray< ::tdme::gui::events::GUIMouseEvent_Type, ::java::lang::EnumArray > GUIMouseEvent_TypeArray;
}  // namespace events
}  // namespace gui
}  // namespace tdme

using java::io::SerializableArray;
using java::lang::ComparableArray;
using java::lang::EnumArray;
using java::lang::ObjectArray;
using tdme::gui::events::GUIMouseEvent_TypeArray;

struct default_init_tag;
class tdme::gui::events::GUIMouseEvent_Type final
	: public Enum
{

public:
	typedef Enum super;

public: /* package */
	static GUIMouseEvent_Type *NONE;
	static GUIMouseEvent_Type *MOUSE_WHEEL_MOVED;
	static GUIMouseEvent_Type *MOUSE_PRESSED;
	static GUIMouseEvent_Type *MOUSE_RELEASED;
	static GUIMouseEvent_Type *MOUSE_MOVED;
	static GUIMouseEvent_Type *MOUSE_DRAGGED;

	// Generated

public:
	GUIMouseEvent_Type(::java::lang::String* name, int ordinal);
protected:
	GUIMouseEvent_Type(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	static GUIMouseEvent_Type* valueOf(String* a0);
	static GUIMouseEvent_TypeArray* values();

private:
	virtual ::java::lang::Class* getClass0();
	friend class GUIMouseEvent;
};
